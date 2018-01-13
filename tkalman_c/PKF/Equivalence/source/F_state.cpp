#include "F_state.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
#include "gsl_Kronecker_product.hpp"
#include "gsl_matrix2vector.hpp"
#include "gsl_vector2matrix.hpp"
#include <iostream>
using namespace std;
using namespace equivalence;

f_state :: f_state( void )
{
	initialize();
}

f_state :: f_state( 	const gsl_matrix * f_xx, 
						const gsl_matrix * f_xy )
{
	initialize();
	if ( setup ( f_xx, f_xy ) )
		throw ( invalid_argument( "Bad argument in f_state :: f_state"));
		
}
				
void f_state :: reset()
{
	free();
	initialize();
}			

int f_state :: setup( 	const gsl_matrix * f_xx, 
						const gsl_matrix * f_xy )
{
	reset();
	if ( ! f_xx || ! f_xy )
		return 1;
	unsigned int 	size_x = f_xx->size1, 
					size_y = f_xy->size2;
	
	if ( 	f_xx->size2 != size_x ||
			f_xy->size1 != size_x )
		return 2;

	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_x + size_y;
	
	_f_xx = f_xx;
	_f_xy = f_xy;
	
	alloc();
	return 0;
}

f_state :: ~f_state()
{
	reset();
}

void f_state :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_f_xx = 0;
	_f_xy = 0;
	w = 0;
}

void f_state :: free()
{
	if ( w )
		delete w;
}
				
void f_state :: alloc()
{
	w = new f_state_workspace( _size_x, _size_y );
}
				
int f_state :: compute_m ( 	gsl_matrix * m,
								const gsl_matrix * f ) const
{
	//Calcul de K
	
	gsl_matrix_transpose_memcpy( w->mat_tt_1(), f );
	gsl_matrix_set_identity( w->mat_xx_1() );
	
	gsl_Kronecker_product( 	w->mat_tx_tx_1(), 
							w->mat_tt_1(), 
							w->mat_xx_1() );
	
	
	
	gsl_matrix_set_identity( w->mat_tt_1() );
	
	gsl_Kronecker_product( 	w->mat_tx_tx_2(), 
							w->mat_tt_1(), 
							_f_xx );
							
		
							
	gsl_matrix_sub( w->mat_tx_tx_1(), 	w->mat_tx_tx_2() );
	
	
	
	//Inversion de K
	int sign;
	gsl_linalg_LU_decomp (w->mat_tx_tx_1(), w->perm_xt(), &sign);




	double det = gsl_linalg_LU_det (w->mat_tx_tx_1(), sign);
	if ( det == 0 ) // Pas de chance là
		return 1;
	gsl_linalg_LU_invert (	w->mat_tx_tx_1(), 
							w->perm_xt(), 
							w->mat_tx_tx_2() );
		
		
	//Calcul du vec( 0 .. FMxy)
	gsl_matrix_set_zero( w->mat_xt_1() );
	gsl_matrix_memcpy( w->mat_xt_1_xy(), _f_xy );
	
	gsl_matrix2vector( w->vect_xt_1(), w->mat_xt_1() );
	//Caclul de vec(Mxt)
	gsl_blas_dgemv( CblasNoTrans,
					1.0,
					w->mat_tx_tx_2(),
					w->vect_xt_1(),
					0.0,
					w->vect_xt_2() );
	
	//Vu sur Mxt
	gsl_matrix_set_identity(m);
	gsl_matrix m_xt = gsl_matrix_submatrix( m, 0, 0, _size_x, _size_t ).matrix;
	
	
	gsl_vector2matrix( &m_xt, w->vect_xt_2() );
	
	return 0;
}
