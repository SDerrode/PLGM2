#include "tkalman_filtering.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
using namespace tkalman;
void tkalman :: compute_innovation (	gsl_vector * innovation,
										const gsl_vector * x_p,
										const gsl_vector * _y,
										const gsl_vector * y,
										const gsl_matrix * f_yx,
										const gsl_matrix * f_yy)
{
	gsl_vector_memcpy(innovation,
					  y);

	gsl_blas_dgemv (CblasNoTrans,
					-1.0,
					f_yx,
					x_p,
					1.0,
					innovation);

	gsl_blas_dgemv (CblasNoTrans,
					-1.0,
					f_yy,
					_y,
					1.0,
					innovation);
}

void tkalman :: compute_x_f(	gsl_vector * x_f,
								const gsl_vector * x_p,
								const gsl_vector * innovation,
								const gsl_matrix * gain)
{
	gsl_vector_memcpy(x_f, x_p);

	gsl_blas_dgemv (CblasNoTrans,
					1.0,
					gain,
					innovation,
					1.0,
					x_f);
}

void tkalman :: compute_sqrt_pf_sqrt_s_and_gain(	gsl_matrix * sqrt_p_f,
													gsl_matrix * sqrt_s,
													gsl_matrix * gain,
													const gsl_matrix * sqrt_p_p,
													const gsl_matrix * f_yx,
													const gsl_matrix * sqrt_q_yy,
													filtering_workspace * w )
{
	//Construction de la matrice
	//      +---------------------------+
	//      |sqrt_q_yy      0           |
	// M =  |                           |
	//      |sqrt_pp.Fyx^T  sqrt_p_p    |
	//      +---------------------------+
	gsl_matrix_memcpy(	w->mat_tt_view_00(), 
						sqrt_q_yy);
	gsl_matrix_memcpy(	w->mat_tt_view_11(), 
						sqrt_p_p);
	gsl_matrix_set_zero(w->mat_tt_view_01());
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_p_p,
				   f_yx,
				   0.0,
				   w->mat_tt_view_10());
	//Décomposition QR
	gsl_linalg_QR_decomp(w->mat_tt(),
						 w->vect_t());
	gsl_triangle_matrix(w->mat_tt());
	
	
	//Recopie des résultats.
	gsl_matrix_memcpy(sqrt_p_f,
					  w->mat_tt_view_11());
	gsl_matrix_memcpy(sqrt_s,
					  w->mat_tt_view_00());

	//Calcul du gain
		//Inversion de sqrt_s
		gsl_pseudo_inverse( w->mat_tt_view_00(), sqrt_s, w->psi_workspace());

		//Produit matriciel
		gsl_blas_dgemm(CblasTrans,
					   CblasTrans,
					   1.0,
					   w->mat_tt_view_01(),
					   w->mat_tt_view_00(),
					   0.0,
					   gain);
}

void tkalman :: compute_sqrt_pf_sqrt_s_and_gain_0(	gsl_matrix * sqrt_q_f_0,
													gsl_matrix * sqrt_s_0,
													gsl_matrix * gain_0,
													const gsl_matrix * sqrt_q_0,
													const gsl_matrix * f_yt,
													const gsl_matrix * sqrt_q_yy,
													filtering_workspace * w )
{
	//Construction de la matrice
	//      +---------------------------+
	//      |sqrt_q_yy      0           |
	// M =  |                           |
	//      |sqrt_pp.Fyx^T  sqrt_p_p    |
	//      +---------------------------+
	gsl_matrix_memcpy(	w->mat_tpy_tpy_view_00(), 
						sqrt_q_yy);
	gsl_matrix_memcpy(	w->mat_tpy_tpy_view_11(), 
						sqrt_q_0);
	gsl_matrix_set_zero(w->mat_tpy_tpy_view_01());
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_q_0,
				   f_yt,
				   0.0,
				   w->mat_tpy_tpy_view_10());
	//Décomposition QR
	gsl_linalg_QR_decomp(w->mat_tpy_tpy(),
						 w->vect_tpy());
	gsl_triangle_matrix(w->mat_tpy_tpy());
	
	
	//Recopie des résultats.
	gsl_matrix_memcpy(sqrt_q_f_0,
					  w->mat_tpy_tpy_view_11());
	gsl_matrix_memcpy(sqrt_s_0,
					  w->mat_tpy_tpy_view_00());

	//Calcul du gain
		//Inversion de sqrt_s
		gsl_pseudo_inverse( w->mat_tpy_tpy_view_00(), sqrt_s_0, w->psi_workspace());
		
		//Produit matriciel
		gsl_blas_dgemm(CblasTrans,
					   CblasTrans,
					   1.0,
					   w->mat_tpy_tpy_view_01(),
					   w->mat_tpy_tpy_view_00(),
					   0.0,
					   gain_0);
}

void tkalman :: compute_filtering(	gsl_vector * x_f,
									gsl_matrix * sqrt_p_f,
									gsl_vector * innovation,
									gsl_matrix * sqrt_s,
									const gsl_vector * x_p,
									const gsl_matrix * sqrt_p_p,
									const gsl_vector * y,
									const gsl_vector * _y,
									const gsl_matrix * f_yx,
									const gsl_matrix * f_yy,
									const gsl_matrix * sqrt_q_yy,
									filtering_workspace * w )
{
	compute_innovation (	innovation,
							x_p,
							_y,
							y,
							f_yx,
							f_yy);
							
	compute_sqrt_pf_sqrt_s_and_gain(	sqrt_p_f,
										sqrt_s,
										w->mat_xy(),
										sqrt_p_p,
										f_yx,
										sqrt_q_yy,
										w );
	compute_x_f(	x_f,
					x_p,
					innovation,
					w->mat_xy() );
	
}
	

void tkalman :: compute_filtering_0(	gsl_vector * t_f_0,
										gsl_matrix * sqrt_q_f_0,
										gsl_vector * innovation,
										gsl_matrix * sqrt_s_0,
										const gsl_vector * t_0,
										const gsl_vector * x_0,
										const gsl_matrix * sqrt_q_0,
										const gsl_vector * y_0,
										const gsl_vector * y_m1,
										const gsl_matrix * f_yt,
										const gsl_matrix * f_yx,
										const gsl_matrix * f_yy,
										const gsl_matrix * sqrt_q_yy,
										filtering_workspace * w )
{
	compute_innovation (	innovation,
							x_0,
							y_m1,
							y_0,
							f_yx,
							f_yy);
							
	compute_sqrt_pf_sqrt_s_and_gain_0(	sqrt_q_f_0,
										sqrt_s_0,
										w->mat_ty(),
										sqrt_q_0,
										f_yt,
										sqrt_q_yy,
										w );
	compute_x_f(	t_f_0,
					t_0,
					innovation,
					w->mat_ty() );
}


filtering :: filtering ()
{
	initialize();
}

filtering :: filtering(	const gsl_matrix * f_yt,
						const gsl_matrix * sqrt_q_yy) throw(exception & )
{
	initialize();
	if ( setup ( f_yt, sqrt_q_yy ) )
		throw( invalid_argument("Invalid arguments in filtering :: filtering") );
}

void filtering :: reset()
{
	free();
	initialize();
}

int filtering :: setup (	const gsl_matrix * f_yt,
							const gsl_matrix * sqrt_q_yy)
{
	if ( ! f_yt || ! sqrt_q_yy )
		return 1;
	unsigned int size_x, size_y, size_t;
	size_y = f_yt->size1;
	size_t = f_yt->size2;
	if ( size_t <= size_y )
		return 1;
	size_x = size_t - size_y;
	if (	sqrt_q_yy->size1 != size_y ||
			sqrt_q_yy->size2 != size_y )
		return 2;
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_t;
	_f_yt = f_yt;
	_sqrt_q_yy = sqrt_q_yy;
	
	
	
	alloc();
	
	{
		gsl_matrix_const_view view = gsl_matrix_const_submatrix (_f_yt, 0, 0, _size_y, _size_x);
		_f_yx = view.matrix;
	}
	{
		gsl_matrix_const_view view = gsl_matrix_const_submatrix (_f_yt, 0, _size_x, _size_y, _size_y);
		_f_yy = view.matrix;
	}
	
	
	return 0;
}

filtering :: ~filtering()
{
	reset();
}

void filtering :: compute(	gsl_vector * x_f,
							gsl_matrix * sqrt_p_f,
							gsl_vector * innovation,
							gsl_matrix * sqrt_s,
							const gsl_vector * x_p,
							const gsl_matrix * sqrt_p_p,
							const gsl_vector * y,
							const gsl_vector * _y) const
{
	compute_filtering(	x_f,
						sqrt_p_f,
						innovation,
						sqrt_s,
						x_p,
						sqrt_p_p,
						y,
						_y,
						&_f_yx,
						&_f_yy,
						_sqrt_q_yy,
						w );
}

void filtering :: compute_0(	gsl_vector * t_f_0,
								gsl_matrix * sqrt_q_f_0,
								gsl_vector * innovation,
								gsl_matrix * sqrt_s_0,
								const gsl_vector * t_0,
								const gsl_matrix * sqrt_q_0,
								const gsl_vector * y_0 ) const
{
	gsl_vector_const_view x_0 = gsl_vector_const_subvector( t_0, 0, _size_x ),
						  y_m1 = gsl_vector_const_subvector( t_0, _size_x, _size_y );
	
	compute_filtering_0(	t_f_0,
							sqrt_q_f_0,
							innovation,
							sqrt_s_0,
							t_0,
							&(x_0.vector),
							sqrt_q_0,
							y_0,
							&(y_m1.vector),
							_f_yt,
							&_f_yx,
							&_f_yy,
							_sqrt_q_yy,
							w );
}

void filtering :: free()
{
	if ( w )
		delete w;
}

void filtering :: alloc()
{
	w = new filtering_workspace( _size_x, _size_y );	
}

void filtering :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_f_yt = 0;
	_sqrt_q_yy = 0;
	w = 0;
}

