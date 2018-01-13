#include "tkalman_prediction.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
using namespace tkalman;
void tkalman :: compute_x_p(	gsl_vector * x_p,
								const gsl_vector * _x_f,
								const gsl_vector * __y,
								const gsl_vector * _y,
								const gsl_matrix * f2_xx,
								const gsl_matrix * f2_xy,
								const gsl_matrix * q2_xy)
{
	//F2xx . x_f
	gsl_blas_dgemv (CblasNoTrans, 
					1.0, 
					f2_xx, 
					_x_f, 
					0, 
					x_p);
	//F2xx . x_f + Q2xy . _y 
	gsl_blas_dgemv (CblasNoTrans, 
					1.0, 
					q2_xy, 
					_y, 
					1.0, 
					x_p);
					
	//F2xx . x_f + Q2xy . _y  + F2xy . __y
	gsl_blas_dgemv (CblasNoTrans, 
					1.0, 
					f2_xy, 
					__y, 
					1.0, 
					x_p);	
}

void tkalman :: compute_sqrt_p_p_1(	gsl_matrix * sqrt_p_p_1,
									const gsl_matrix * sqrt_q_f_0,
									const gsl_matrix * f2_xt,
									const gsl_matrix * sqrt_q2_xx,
									prediction_workspace * w )
{
	//Construction de la matrice
	// Q2xx
	//
	// sqrt_q_f . F2_x^T
	
	gsl_matrix_memcpy(	w->mat_xpt_x_view_00(), 
						sqrt_q2_xx);
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_q_f_0,
				   f2_xt,
				   0.0,
				   w->mat_xpt_x_view_10() );
				   
	//Décomposition QR
	gsl_linalg_QR_decomp(w->mat_xpt_x(),
						 w->vect_x() );
	gsl_triangle_matrix(w->mat_xpt_x());
	
	//Recopie du résultat
	gsl_matrix_memcpy(	sqrt_p_p_1, 
						w->mat_xpt_x_view_00());
}

void tkalman :: compute_sqrt_p_p(	gsl_matrix * sqrt_p_p,
									const gsl_matrix * _sqrt_p_f,
									const gsl_matrix * f2_xx,
									const gsl_matrix * sqrt_q2_xx,
									prediction_workspace * w )
{
	//Construction de la matrice
	// Q2xx
	//
	// sqrt_p_f . F2_xx^T
	
	gsl_matrix_memcpy(	w->mat_2xx_view_00(), 
						sqrt_q2_xx);
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   _sqrt_p_f,
				   f2_xx,
				   0.0,
				   w->mat_2xx_view_10() );
				   
	//Décomposition QR
	gsl_linalg_QR_decomp(w->mat_2xx(),
						 w->vect_x());
	gsl_triangle_matrix(w->mat_2xx());
	
	//Recopie du résultat
	gsl_matrix_memcpy(	sqrt_p_p, 
						w->mat_2xx_view_00());
}

void tkalman :: compute_prediction (	gsl_vector * x_p,
										gsl_matrix * sqrt_p_p,
										const gsl_vector * _x_f,
										const gsl_matrix * _sqrt_p_f,
										const gsl_vector * __y,
										const gsl_vector * _y,
										const gsl_matrix * f2_xx,
										const gsl_matrix * f2_xy,
										const gsl_matrix * sqrt_q2_xx,
										const gsl_matrix * q2_xy,
										prediction_workspace * w )
{
	compute_x_p ( 	x_p,
					_x_f,
					__y,
					_y,
					f2_xx,
					f2_xy,
					q2_xy );
					
	compute_sqrt_p_p( 	sqrt_p_p,
						_sqrt_p_f,
						f2_xx,
						sqrt_q2_xx,
						w ) ;
}

void tkalman :: compute_prediction_1 (	gsl_vector * x_p_1,
										gsl_matrix * sqrt_p_p_1,
										const gsl_vector * x_f_0,
										const gsl_vector * y_f_m1,
										const gsl_matrix * sqrt_q_f_0,
										const gsl_vector * y_0,
										const gsl_matrix * f2_xt,
										const gsl_matrix * f2_xx,
										const gsl_matrix * f2_xy,
										const gsl_matrix * sqrt_q2_xx,
										const gsl_matrix * q2_xy,
										prediction_workspace * w 
									  )
{
	compute_x_p(	x_p_1,
					x_f_0,
					y_f_m1,
					y_0,
					f2_xx,
					f2_xy,
					q2_xy);
					
	compute_sqrt_p_p_1(	sqrt_p_p_1,
						sqrt_q_f_0,
						f2_xt,
						sqrt_q2_xx,
						w );
	
}

prediction :: prediction ( )
{
	initialize();
}

prediction :: prediction (	const gsl_matrix * f2_xt,
							const gsl_matrix * sqrt_q2_xx,
							const gsl_matrix * q2_xy ) throw (exception &)
{
	initialize();
	if ( setup ( f2_xt, sqrt_q2_xx, q2_xy ) )
		throw ( invalid_argument( "Invalid argument in  prediction :: prediction" ) );

}

void prediction :: reset()
{
	free();
	initialize();
}

int prediction :: setup (	const gsl_matrix * f2_xt,
							const gsl_matrix * sqrt_q2_xx,
							const gsl_matrix * q2_xy )
{
	reset();
	if ( ! f2_xt || ! sqrt_q2_xx || ! q2_xy )
		return 1;
	unsigned int 	size_x, 
					size_y, 
					size_t;
	size_x = f2_xt->size1;
	size_t = f2_xt->size2;
	size_y = size_t - size_x;
	if ( size_t <= size_x )
		return 1;
	if (	sqrt_q2_xx->size1 != size_x									||
			sqrt_q2_xx->size2 != size_x									||
			q2_xy->size1 != size_x										||
			q2_xy->size2 != size_y										)
		return 2;
	
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_t;
	_f2_xt = f2_xt;
	_sqrt_q2_xx = sqrt_q2_xx;
	_q2_xy = q2_xy;
	
	alloc();
	//Vues
	{
		gsl_matrix_const_view view = gsl_matrix_const_submatrix (_f2_xt, 0, 0, _size_x, _size_x);
		_f2_xx = view.matrix;
	}
	{
		gsl_matrix_const_view view = gsl_matrix_const_submatrix (_f2_xt, 0, _size_x, _size_x, _size_y);
		_f2_xy = view.matrix;
	}
	
	return 0;
}

void prediction :: compute_1 ( 	gsl_vector * x_p_1,
								gsl_matrix * sqrt_p_p_1,
								const gsl_vector * t_f_0,
								const gsl_matrix * sqrt_q_f_0,
								const gsl_vector * y_0 ) const
{
	gsl_vector_const_view x_f_0 = gsl_vector_const_subvector( t_f_0, 0, _size_x ),
						  y_f_m1 = gsl_vector_const_subvector( t_f_0, _size_x, _size_y );
						  
	compute_prediction_1 (	x_p_1,
							sqrt_p_p_1,
							&(x_f_0.vector),
							&(y_f_m1.vector),
							sqrt_q_f_0,
							y_0,
							_f2_xt,
							&_f2_xx,
							&_f2_xy,
							_sqrt_q2_xx,
							_q2_xy,
							w );
}

void prediction :: compute (	gsl_vector * x_p,
								gsl_matrix * sqrt_p_p,
								const gsl_vector * _x_f,
								const gsl_matrix * _sqrt_p_f,
								const gsl_vector * __y,
								const gsl_vector * _y) const
{
	compute_prediction (	x_p,
							sqrt_p_p,
							_x_f,
							_sqrt_p_f,
							__y,
							_y,
							&_f2_xx,
							&_f2_xy,
							_sqrt_q2_xx,
							_q2_xy,
							w );
}

prediction :: ~prediction()
{
	reset();
}

void prediction :: free()
{
	if ( w )
		delete w;
}

void prediction :: alloc()
{
	w = new prediction_workspace( _size_x, _size_y );
}

void prediction :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_f2_xt = 0;
	_sqrt_q2_xx = 0;
	_q2_xy = 0;
	w = 0;
}

