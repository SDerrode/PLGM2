#include "tkalman_constants.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "lib_PKF_gsl.hpp"

using namespace tkalman;

void tkalman :: compute_f2_xt(	gsl_matrix * f2_x_,
								const gsl_matrix * f_x_,
								const gsl_matrix * f_y_,
								const gsl_matrix * q2_xy)
{
	//Copie de Qxx
	gsl_matrix_memcpy(f2_x_, f_x_);

	//Qxx - Qxy . Qyy¯¹ . Qyx
	gsl_blas_dgemm (CblasNoTrans,
					CblasNoTrans,
					-1.0,
					q2_xy,
					f_y_,
					1.0,
					f2_x_);
}

void tkalman :: compute_sqrt_constants(	gsl_matrix * sqrt_q2_xx,
										gsl_matrix * q2_xy,
										gsl_matrix * sqrt_q_yy,
										const gsl_matrix * sqrt_q_view_xx,
										const gsl_matrix * sqrt_q_view_xy,
										const gsl_matrix * sqrt_q_view_yy,
										constants_workspace * w )
{
	//Construction de la matrice Q'
	// sqrt(Q)yy		0
	// sqrt(Q)xy		sqrt(Qxx) = sqrt(Q)xx
	gsl_matrix_memcpy(	w->mat_tt_yy(), 
						sqrt_q_view_yy);
	gsl_matrix_set_zero( w->mat_tt_yx() );
	gsl_matrix_memcpy(	w->mat_tt_xy(), 
						sqrt_q_view_xy);
	gsl_matrix_memcpy(	w->mat_tt_xx(), 
						sqrt_q_view_xx);
	//Décomposition QR
	gsl_linalg_QR_decomp(	w->mat_tt(),
							w->vect_t());
	gsl_triangle_matrix(	w->mat_tt() );

	//Récupération de sqrt(Qyy) et de sqrt(Q2xx)
	gsl_matrix_memcpy(	sqrt_q2_xx, 
						w->mat_tt_xx());
	gsl_matrix_memcpy(	sqrt_q_yy, 
						w->mat_tt_yy());

	//Calcul de Q2xy = Qxy.Qyy^-1 (On tient compte du cas où Qyy est singulière)
	//Construction de proj. tel que 
	// -P_1 sq_Qyy P_1 Soit de rang plein
	// -(P_2 sq_Qyy P_2)^2 = 0							
	// 
	gsl_pseudo_inverse( w->mat_tt_yy(), sqrt_q_yy, w->psi_workspace() );
	//~ gsl_matrix_fprintf_( stdout, API_DEFAULT_MATRIX_FORMAT, w->mat_tt_yy() );
	//~ cout << endl;
	
	//~ gsl_permutation_init(	w->perm_y() );
    //~ gsl_linalg_LU_invert(	sqrt_q_yy, 
							//~ w->perm_y(), 
							//~ w->mat_tt_yy());
	//~ gsl_matrix_fprintf_( stdout, API_DEFAULT_MATRIX_FORMAT, w->mat_tt_yy() );
	//~ cout << endl;
	
	
	

	gsl_blas_dgemm(CblasTrans,
				   CblasTrans,
				   1.0,
				   w->mat_tt_yx(),
				   w->mat_tt_yy(),
				   0.0,
				   q2_xy);
}



void tkalman :: compute_constants(	gsl_matrix * f2_x_,
									gsl_matrix * sqrt_q2_xx,
									gsl_matrix * q2_xy,
									gsl_matrix * sqrt_q_yy,
									const gsl_matrix * f_x_,
									const gsl_matrix * f_y_,
									const gsl_matrix * sqrt_q_view_xx,
									const gsl_matrix * sqrt_q_view_xy,
									const gsl_matrix * sqrt_q_view_yy,
									constants_workspace * w )
{
	compute_sqrt_constants(	sqrt_q2_xx,
							q2_xy,
							sqrt_q_yy,
							sqrt_q_view_xx,
							sqrt_q_view_xy,
							sqrt_q_view_yy,
							w );
	compute_f2_xt(	f2_x_,
					f_x_,
					f_y_,
					q2_xy);
}

constants :: constants( void )
{
	initialize();
}

constants :: constants(	const gsl_matrix * f_xt,
						const gsl_matrix * f_yt,
						const gsl_matrix * sqrt_q_xx,
						const gsl_matrix * sqrt_q_xy,
						const gsl_matrix * sqrt_q_yy) throw (exception &)
{
	initialize();
	if ( setup ( f_xt, f_yt, sqrt_q_xx, sqrt_q_xy, sqrt_q_yy ) )
		throw ( invalid_argument("constants :: constants") ); 
}

void constants :: reset ( )
{
	free();
	initialize();
}

int constants :: setup (	const gsl_matrix * f_xt,
							const gsl_matrix * f_yt,
							const gsl_matrix * sqrt_q_xx,
							const gsl_matrix * sqrt_q_xy,
							const gsl_matrix * sqrt_q_yy)
{
	reset();
	if ( 	f_xt == 0 		|| 
			f_yt == 0 		|| 
			sqrt_q_xx == 0 	|| 
			!sqrt_q_yy 		|| 
			!sqrt_q_yy 		)
		return 1;
	
	unsigned int size_x = f_xt->size1,
				 size_t = f_xt->size2,
				 size_y = size_t - size_x;
	
	if ( size_t <= size_x )
		return 2;
	
	if ( 	f_yt->size1 != size_y 		||
			f_yt->size2 != size_t		||
			sqrt_q_xx->size1 != size_x	||
			sqrt_q_xx->size2 != size_x 	||
			sqrt_q_xy->size1 != size_x	||
			sqrt_q_xy->size2 != size_y	||
			sqrt_q_yy->size1 != size_y	||
			sqrt_q_yy->size2 != size_y )
		return 3;
	
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_t;
	
	_f_xt = f_xt;
	_f_yt = f_yt;
	_sqrt_q_xx = sqrt_q_xx;
	_sqrt_q_xy = sqrt_q_xy;
	_sqrt_q_yy = sqrt_q_yy;
	
	alloc();
	
	return 0;
}

constants :: ~constants()
{
	reset();
}

void constants :: free()
{
	if ( w )
		delete w;
}

void constants :: alloc()
{
	w = new constants_workspace( _size_x, _size_y );
}

void constants :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_f_xt = 0;
	_f_yt = 0;
	_sqrt_q_xx = 0;
	_sqrt_q_xy = 0;
	_sqrt_q_yy = 0;
	w = 0;
}

