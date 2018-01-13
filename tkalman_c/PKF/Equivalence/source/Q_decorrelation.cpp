#include "Q_decorrelation.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
#include <iostream>
using namespace std;

using namespace equivalence;
Q_decorrelation :: Q_decorrelation()
{
	initialize();
}

Q_decorrelation :: Q_decorrelation( 	const gsl_matrix * sqrt_q_xx,
					const gsl_matrix * rho )
{
	initialize();
	if ( setup ( sqrt_q_xx, rho ) )
		throw ( invalid_argument("Bad argument in Q_decorrelation") );
	
	
}

void Q_decorrelation :: reset()
{
	free();
	initialize();
}

int Q_decorrelation :: setup( 	const gsl_matrix * sqrt_q_xx,
								const gsl_matrix * rho  )
{
	reset();
	unsigned int size_x, size_y;
	if ( ! sqrt_q_xx || ! rho )	
		return 1;
	size_x = sqrt_q_xx->size1;
	size_y = rho->size2;
	if ( 	size_x != sqrt_q_xx->size2	||
			size_x != rho->size1		)
		return 2;
		
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_x + size_y;
	_rho = rho;
	_sqrt_q_xx = sqrt_q_xx;
	
	alloc();
	
	return 0;
}

void Q_decorrelation :: compute_m ( 	gsl_matrix * m,
										const gsl_matrix * sqrt_q,
										const gsl_matrix * q2_xy ) const
{
	//Calcul de sq(Q*)
		//Construction
		gsl_matrix_set_identity(w->mat_tt_1());
		gsl_matrix_memcpy( w->mat_tt_1_xy(), _rho );
		gsl_matrix_sub( w->mat_tt_1_xy(), q2_xy );
		gsl_blas_dgemm( CblasNoTrans,
						CblasTrans,
						1.0,
						sqrt_q,
						w->mat_tt_1(),
						0.0,
						w->mat_tt_2() );
		

		
		//Decompo QR
		gsl_linalg_QR_decomp(	w->mat_tt_2(),
								w->vect_t_1() );
		gsl_triangle_matrix(w->mat_tt_2());
		
		//Inversion de sq(Q*)
		gsl_permutation_init(	w->perm_x() );
		gsl_linalg_LU_invert(	w->mat_tt_2_xx(),
								w->perm_x(), 
								w->mat_xx_1());
	//Calcul de M
		//Ini
		gsl_matrix_set_identity(m);
		gsl_matrix 	m_xx = gsl_matrix_submatrix(m, 0, 0, _size_x, _size_x).matrix,
					m_xy = gsl_matrix_submatrix(m, 0, _size_x, _size_x, _size_y).matrix;
		
		gsl_blas_dgemm( CblasTrans,
						CblasTrans,
						1.0,
						_sqrt_q_xx,
						w->mat_xx_1(),
						0.0, 
						&m_xx );
		gsl_blas_dgemm( CblasNoTrans,
						CblasNoTrans,
						1.0,
						&m_xx,
						w->mat_tt_1_xy(),
						0.0, 
						&m_xy );
}

Q_decorrelation :: ~Q_decorrelation()
{
	reset();
}

void Q_decorrelation :: initialize()
{
	_rho = 0;
	_sqrt_q_xx = 0;
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	w = 0;
}

void Q_decorrelation :: free()
{
	if ( w )
		delete w;
}

void Q_decorrelation :: alloc()
{
	w = new Q_decorrelation_workspace ( _size_x, _size_y );
}
