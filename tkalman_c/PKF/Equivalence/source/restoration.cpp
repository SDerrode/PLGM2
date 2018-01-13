#include "restoration.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
#include <iostream>
using namespace std;
using namespace equivalence;

restoration :: restoration( void )
{
	initialize();	
}

restoration :: restoration( 	const gsl_matrix * f_yx, 
								const gsl_matrix * f_yy )
{
	initialize();
	if ( setup(  f_yx, f_yy ) )
		throw ( invalid_argument("Bad argument in restoration :: restoration...") );
}

void restoration :: reset()
{
	free();
	initialize();
}

int restoration :: setup( 	const gsl_matrix * f_yx, 
							const gsl_matrix * f_yy )
{
	reset();
	unsigned int size_x, size_y;
	if ( ! f_yx || ! f_yy )
		return 1;
		
	size_x = f_yx->size2;
	size_y = f_yx->size1;
	
	if ( 	size_y != f_yy->size1	||
			size_y != f_yy->size2 )
		return 2;
	if ( size_x < size_y ) // Pas de solution dans ce cas!
		return 3;
	_f_yx = f_yx;
	_f_yy = f_yy;	
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_x + size_y;
	alloc();
	return 0;
}

restoration :: ~restoration()
{
	reset();
}

void restoration :: initialize()
{
	_f_yx = 0;
	_f_yy = 0;
	w = 0;
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
}

void restoration :: free()
{
	if ( w )
		delete w;
}

void restoration :: alloc()
{
	w = new restoration_workspace( _size_x, _size_y );
}

void restoration :: compute_m ( 	gsl_matrix * m,
									const gsl_matrix * f ) const
{
	//M = I
	gsl_matrix_set_identity(m);
	//Construction des deux vues sur F
	gsl_matrix 	f_yx = gsl_matrix_const_submatrix( f, _size_x, 0, _size_y, _size_x ).matrix,
				f_yy = gsl_matrix_const_submatrix( f, _size_x, _size_x, _size_y, _size_y ).matrix;
	
	//Initialisation des mat_xx
	gsl_matrix_set_identity( w->mat_xx_1() );
	gsl_matrix_set_identity( w->mat_xx_2() );

	//Transposition de Fyx et FyxM
	gsl_matrix_transpose_memcpy( 	w->mat_xx_1_xy(), 
									&f_yx );
									
	gsl_matrix_transpose_memcpy( 	w->mat_xx_2_xy(), 
									_f_yx);

		
	//Décompositions QR
		gsl_linalg_QR_decomp(	w->mat_xx_1_xy(),
								w->vect_y_1() );

		gsl_linalg_QR_unpack (w->mat_xx_1_xy(), w->vect_y_1(), w->mat_xx_3(), w->mat_xy_1());
		gsl_triangle_matrix(w->mat_xx_1_xy());
		
	
	
	
	
	
		gsl_linalg_QR_decomp(	w->mat_xx_2_xy(),
								w->vect_y_1() );
		gsl_linalg_QR_unpack (w->mat_xx_2_xy(), w->vect_y_1(), w->mat_xx_4(), w->mat_xy_1());
		gsl_triangle_matrix(w->mat_xx_2_xy());
										
	//Calcul des matrix Qtrucs
		gsl_blas_dgemm(	CblasNoTrans,
						CblasNoTrans,
						1.0,
						w->mat_xx_3(),
						w->mat_xx_1(),
						0.0,
						w->mat_xx_5() );
	
		gsl_permutation_init(	w->perm_x() );
		gsl_linalg_LU_invert(	w->mat_xx_2(),
								w->perm_x(),
								w->mat_xx_6());
								
		
		gsl_blas_dgemm(	CblasNoTrans,
						CblasTrans,
						1.0,
						w->mat_xx_4(),
						w->mat_xx_6(),
						0.0,
						w->mat_xx_7() );

	//Vues sur m
	gsl_matrix 	m_xx = gsl_matrix_submatrix( m, 0, 0, _size_x, _size_x ).matrix,
				m_xy = gsl_matrix_submatrix( m, 0, _size_x, _size_x, _size_y ).matrix;
				
	gsl_blas_dgemm( CblasNoTrans,
					CblasTrans,
					1.0,
					w->mat_xx_7(),
					w->mat_xx_5(),
					0.0,
					&m_xx );
					
	gsl_matrix_memcpy( 	w->mat_yy_1(),
						&f_yy );
	gsl_matrix_sub( w->mat_yy_1(),
					_f_yy );
	gsl_blas_dgemm( CblasNoTrans,
					CblasNoTrans,
					1.0,
					w->mat_xx_7(),
					w->mat_xy_1(),
					0.0,
					&m_xy );
					
}

