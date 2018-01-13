#include "tkalman_smoothing.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
using namespace tkalman;

void tkalman :: compute_x_s(	gsl_vector * x_s,
								const gsl_vector * x_f,
								const gsl_vector * x_p_,
								const gsl_vector * x_s_,
								const gsl_matrix * gain)
{
	gsl_vector_memcpy(x_s,
					  x_f);

	gsl_blas_dgemv (CblasNoTrans,
					1.0,
					gain,
					x_s_,
					1.0,
					x_s);

	gsl_blas_dgemv (CblasNoTrans,
					-1.0,
					gain,
					x_p_,
					1.0,
					x_s);
}

void tkalman :: compute_smoothing_gain_0(	gsl_matrix * s_gain,
											const gsl_matrix * sqrt_q_f,
											const gsl_matrix * sqrt_p_p_,
											const gsl_matrix * f2_xt,
											smoothing_workspace * w )
{
	//Q F2_x_^T
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_q_f, //tt
  				   f2_xt,   //tx
				   0.0,
				   w->mat_2xpt_xpt_view_10() );
	gsl_blas_dgemm(CblasTrans,
				   CblasNoTrans,
				   1.0,
				   sqrt_q_f, //tt
  				   w->mat_2xpt_xpt_view_10(),   //tx
				   0.0,
				   s_gain);     
	//P_p - 1
	gsl_pseudo_inverse( w->mat_2xpt_xpt_view_00(), sqrt_p_p_, w->psi_workspace() );
	//~ gsl_permutation_init(w->perm_x());
	//~ gsl_linalg_LU_invert(sqrt_p_p_,
					     //~ w->perm_x(),
						 //~ w->mat_2xpt_xpt_view_00());
	
	
	
	gsl_blas_dgemm(CblasNoTrans,
				   CblasNoTrans,
				   1.0,
				   s_gain, //tt
  				   w->mat_2xpt_xpt_view_00(),   //tx
				   0.0,
				   w->mat_2xpt_xpt_view_10());
	
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   w->mat_2xpt_xpt_view_10(), //tt
  				   w->mat_2xpt_xpt_view_00(),   //tx
				   0.0,
				   s_gain);
}

void tkalman :: compute_smoothing_gain(	gsl_matrix * s_gain,
										const gsl_matrix * sqrt_p_f,
										const gsl_matrix * sqrt_p_p_,
										const gsl_matrix * f2_xx,
										smoothing_workspace * w  )
{
	//Q F2_x_^T
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_p_f, //tt
  				   f2_xx,   //tx
				   0.0,
				   w->mat_3x2x_view_00() );
	gsl_blas_dgemm(CblasTrans,
				   CblasNoTrans,
				   1.0,
				   sqrt_p_f, //tt
  				   w->mat_3x2x_view_00(),   //tx
				   0.0,
				   s_gain);     
	//P_p - 1
	gsl_pseudo_inverse( w->mat_3x2x_view_21(), sqrt_p_p_, w->psi_workspace() );
	//~ gsl_permutation_init(w->perm_x());
	//~ gsl_linalg_LU_invert(sqrt_p_p_,
					     //~ w->perm_x(),
						 //~ w->mat_3x2x_view_21());
	
	
	
	gsl_blas_dgemm(CblasNoTrans,
				   CblasNoTrans,
				   1.0,
				   s_gain, //tt
  				   w->mat_3x2x_view_21(),   //tx
				   0.0,
				   w->mat_3x2x_view_00() );
	
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   w->mat_3x2x_view_00(), //tt
  				   w->mat_3x2x_view_21(),   //tx
				   0.0,
				   s_gain);
}

void tkalman :: compute_sqrt_p_s_and_c_s(	gsl_matrix * sqrt_p_s,
											gsl_matrix * c_s,
											const gsl_matrix * sqrt_p_f,
											const gsl_matrix * sqrt_p_s_,
											const gsl_matrix * f2_xx,
											const gsl_matrix * sqrt_q2_xx,
											const gsl_matrix * s_gain,
											smoothing_workspace * w )
{
	//Création de la matrice (2 matrices possibles)
	// sqrt_Q2xx		0
	// sqrt_p_f F2xx^T	sqrt_p_f
	// 0				sqrt(P_s_) K^T
		gsl_matrix_memcpy(w->mat_3x2x_view_00(),
						  sqrt_q2_xx);
		gsl_matrix_set_zero(w->mat_3x2x_view_01());
		gsl_blas_dgemm(CblasNoTrans,
					   CblasTrans,
					   1.0,
					   sqrt_p_f,
					   f2_xx,
					   0.0,
					   w->mat_3x2x_view_10() );
		gsl_matrix_memcpy(w->mat_3x2x_view_11(),
						  sqrt_p_f);
		gsl_matrix_set_zero(w->mat_3x2x_view_20());
		//Calcul de la covariance entre les états lissés courant et suivant
		gsl_blas_dgemm(CblasNoTrans,
					   CblasTrans,
					   1.0,
					   sqrt_p_s_,
					   s_gain,
					   0.0,
					   w->mat_3x2x_view_21());
		//Sauvegarde du résultat
		if (c_s != NULL)
			gsl_matrix_memcpy(c_s,
							  w->mat_3x2x_view_21());

	//Décomposition QR
		gsl_linalg_QR_decomp(w->mat_3x2x(),
							 w->vect_2x());
		gsl_triangle_matrix(w->mat_3x2x());

	//Recopie
		gsl_matrix_memcpy(sqrt_p_s,
						  w->mat_3x2x_view_11());
}

void tkalman :: compute_sqrt_p_s_and_c_s_0(	gsl_matrix * sqrt_q_s_0,
											gsl_matrix * c_s_0,
											const gsl_matrix * sqrt_q_f_0,
											const gsl_matrix * sqrt_p_s_1,
											const gsl_matrix * f2_xt,
											const gsl_matrix * sqrt_q2_xx,
											const gsl_matrix * s_gain,
											smoothing_workspace * w )
{
	//Création de la matrice (2 matrices possibles)
	// sqrt_Q2xx		0
	// sqrt_q_f F2xt^T	sqrt_q_f
	// 0				sqrt(P_s_) K^T
		gsl_matrix_memcpy(w->mat_2xpt_xpt_view_00(),
						  sqrt_q2_xx);
		gsl_matrix_set_zero(w->mat_2xpt_xpt_view_01());
		gsl_blas_dgemm(CblasNoTrans,
					   CblasTrans,
					   1.0,
					   sqrt_q_f_0,
					   f2_xt,
					   0.0,
					   w->mat_2xpt_xpt_view_10() );
					   
		gsl_matrix_memcpy(w->mat_2xpt_xpt_view_11(),
						  sqrt_q_f_0);
						  
		gsl_matrix_set_zero(w->mat_2xpt_xpt_view_20());
		//Calcul de la covariance entre les états lissés courant et suivant
		gsl_blas_dgemm(CblasNoTrans,
					   CblasTrans,
					   1.0,
					   sqrt_p_s_1,
					   s_gain,
					   0.0,
					   w->mat_2xpt_xpt_view_21());
		//Sauvegarde du résultat
		if (c_s_0 != NULL)
			gsl_matrix_memcpy(c_s_0,
							  w->mat_2xpt_xpt_view_21());

	//Décomposition QR
		gsl_linalg_QR_decomp(w->mat_2xpt_xpt(),
							 w->vect_xpt());
		gsl_triangle_matrix(w->mat_2xpt_xpt());

	//Recopie
		gsl_matrix_memcpy(sqrt_q_s_0,
						  w->mat_2xpt_xpt_view_11());
}

void tkalman :: compute_smoothing(	gsl_vector * x_s,
									gsl_matrix * sqrt_p_s,
									gsl_matrix * c_s,
									const gsl_vector * x_f,
									const gsl_matrix * sqrt_p_f,
									const gsl_vector * x_p_,
									const gsl_matrix * sqrt_p_p_,
									const gsl_vector * x_s_,
									const gsl_matrix * sqrt_p_s_,
									const gsl_matrix * f2_xx,
									const gsl_matrix * sqrt_q2_xx,
									smoothing_workspace * w )
{
	//Gain
	compute_smoothing_gain(	w->mat_xx(),
							sqrt_p_f,
							sqrt_p_p_,
							f2_xx,
							w  );
							
	//sqrt
	compute_sqrt_p_s_and_c_s(	sqrt_p_s,
								c_s,
								sqrt_p_f,
								sqrt_p_s_,
								f2_xx,
								sqrt_q2_xx,
								w->mat_xx(),
								w );
	//Exp
	compute_x_s(	x_s,
					x_f,
					x_p_,
					x_s_,
					w->mat_xx() );
	
}

void tkalman :: compute_smoothing_0(	gsl_vector * t_s_0,
										gsl_matrix * sqrt_q_s_0,
										gsl_matrix * c_s_0,
										const gsl_vector * t_f_0,
										const gsl_matrix * sqrt_q_f_0,
										const gsl_vector * x_p_1,
										const gsl_matrix * sqrt_p_p_1,
										const gsl_vector * x_s_1,
										const gsl_matrix * sqrt_p_s_1,
										const gsl_matrix * f2_xt,
										const gsl_matrix * sqrt_q2_xx,
										smoothing_workspace * w )
{
	//Gain
	compute_smoothing_gain_0(	w->mat_tx(),
								sqrt_q_f_0,
								sqrt_p_p_1,
								f2_xt,
								w  );
							
	//sqrt
	compute_sqrt_p_s_and_c_s_0(	sqrt_q_s_0,
								c_s_0,
								sqrt_q_f_0,
								sqrt_p_s_1,
								f2_xt,
								sqrt_q2_xx,
								w->mat_tx(),
								w );
	//Exp
	compute_x_s(	t_s_0,
					t_f_0,
					x_p_1,
					x_s_1,
					w->mat_tx() );
	
}

smoothing :: smoothing()
{
	initialize();
}

smoothing :: smoothing (	const gsl_matrix * f2_xt, 
							const gsl_matrix * sqrt_q2_xx ) throw (exception & )
{
	initialize();
	if ( setup( f2_xt, sqrt_q2_xx ) )
		throw ( invalid_argument("Invalid arguments in smoothing :: smoothing") );
}

void smoothing :: reset ( )
{
	free();
	initialize();
}

int smoothing :: setup(	const gsl_matrix * f2_xt, 
						const gsl_matrix * sqrt_q2_xx )
{
	reset();
	if ( ! f2_xt || ! sqrt_q2_xx )
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
			sqrt_q2_xx->size2 != size_x									)
		return 2;
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_t;
	_f2_xt = f2_xt;
	_sqrt_q2_xx = sqrt_q2_xx;
	
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

smoothing :: ~smoothing()
{
	reset();
}

void smoothing :: compute(	gsl_vector * x_s,
							gsl_matrix * sqrt_p_s,
							gsl_matrix * c_s,
							const gsl_vector * x_f,
							const gsl_matrix * sqrt_p_f,
							const gsl_vector * x_p_,
							const gsl_matrix * sqrt_p_p_,
							const gsl_vector * x_s_,
							const gsl_matrix * sqrt_p_s_ ) const
{
	compute_smoothing(	x_s,
						sqrt_p_s,
						c_s,
						x_f,
						sqrt_p_f,
						x_p_,
						sqrt_p_p_,
						x_s_,
						sqrt_p_s_,
						&_f2_xx,
						_sqrt_q2_xx,
						w );
}

void  smoothing :: compute_0(	gsl_vector * t_s_0,
								gsl_matrix * sqrt_q_s_0,
								gsl_matrix * c_s_0,
								const gsl_vector * t_f_0,
								const gsl_matrix * sqrt_q_f_0,
								const gsl_vector * x_p_1,
								const gsl_matrix * sqrt_p_p_1,
								const gsl_vector * x_s_1,
								const gsl_matrix * sqrt_p_s_1 ) const
{
	compute_smoothing_0(	t_s_0,
							sqrt_q_s_0,
							c_s_0,
							t_f_0,
							sqrt_q_f_0,
							x_p_1,
							sqrt_p_p_1,
							x_s_1,
							sqrt_p_s_1,
							_f2_xt,
							_sqrt_q2_xx,
							w );
}

void smoothing :: free()
{
	if ( w )
		delete w;
}


void smoothing :: alloc()
{
	w = new smoothing_workspace( _size_x, _size_y );
}

void smoothing :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_f2_xt = 0;
	_sqrt_q2_xx = 0;
	w = 0;
}

