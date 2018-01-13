#include "tkalman_sum.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
namespace tkalman
{
/**@fn void tkalman :: compute_sqrt_cov(	const gsl_matrix * sqrt_p_f,
											const gsl_matrix * sqrt_p_s_,
											const gsl_matrix * c_s,
											const gsl_matrix * f2_xx,
											const gsl_matrix * sqrt_q2_xx,
											sum_workspace * w );
								 
 * @param[in] sqrt_p_f : 
  \f$[P_{n|n}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix if n > 0
 * @param[in]  sqrt_p_s_ : 
  \f$ [P_{n + 1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @param[in] c_s : 
  \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 * @param[in] f2_xx :
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$ if n > 0
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param w : workspace
 * @brief
 * This function computes the square root of the covariance matric of the random vector \f$ (z_{n|N}; x_{n + 1 |N} ) \f$, where \f$( z = x or t )\f$. 
 * - 1. Building the matrix 
 * \f$
 * M= \begin{pmatrix}
 * \left[Q_2^{x,x}\right]^{\frac{1}{2}}							&	0_{n_x, n_t}	&	0_{n_x, n_x}	\\
 * \left[Z_{n|n}\right]^{\frac{1}{2}} \left[F_2^{x} \right]^T	&	\left[Z_{n|n}\right]^{\frac{1}{2}}	&	0_{n_t, n_x}	\\
 * 0_{n_x, n_x}													&	\left[P_{n + 1 |N} K_{n|N}^T\right]^{\frac{1}{2}}	&	\left[P_{n + 1 |N} K_{n|N}^T\right]^{\frac{1}{2}}
 * \end{pmatrix}
 * \f$
 * - 2. QR decomposition which can be written:
 * \f$ 
   \begin{pmatrix}
 * 	M_{0,0}	&	M_{0,1}	&	M_{0,2} \\
 * 	O	    	&		M_{1,1}	&	M_{1,2} \\ 
 * 	O   	 	&		O	       &	M_{2,2}
 * \end{pmatrix}
 * \f$ 
 * -3. Cov. matrix is 
 * \f$ 
 * \begin{pmatrix}
 * 	M_{1,1}	&	M_{1,2} \\ 
 * 	0    	&	M_{2,2}
 * \end{pmatrix}
 * \f$ 
 * @warning
 * If you want to get the result, you have to build a view on the matrix \f$M\f$,  
 * - starting at \f$(0,0)\f$, ending at \f$(2 n_x - 1, 2 n_x - 1)\f$ if n > 0 
 * - or starting at \f$(0,0)\f$, ending at \f$(n_x + n_t - 1, n_x + n_t - 1)\f$ if n = 0
 *
**/
void compute_sqrt_cov(	const gsl_matrix * sqrt_p_f,
						const gsl_matrix * sqrt_p_s_,
						const gsl_matrix * c_s,
						const gsl_matrix * f2_xx,
						const gsl_matrix * sqrt_q2_xx,
						sum_workspace * w )
{
	//Mise à zéro de la matrice M
	gsl_matrix_set_zero(w->mat_3x3x());
	
	//Construction de la matrice
	//M00
	gsl_matrix_memcpy(w->mat_3x3x_view_00(), 
					  sqrt_q2_xx);
	//M10
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_p_f,
				   f2_xx,
				   0.0,
				   w->mat_3x3x_view_10());
	//M11
	gsl_matrix_memcpy(	w->mat_3x3x_view_11(), 
						sqrt_p_f);
	
	//M21
	gsl_matrix_memcpy(	w->mat_3x3x_view_21(), 
						c_s);
	
	//M22
	gsl_matrix_memcpy(	w->mat_3x3x_view_22(), 
						sqrt_p_s_);
	
	//Décomposition QR
	gsl_linalg_QR_decomp(	w->mat_3x3x(),
							w->vect_3x());
	gsl_triangle_matrix(w->mat_3x3x());
}
	
			
/**@fn void tkalman_get_sqrt_cov_0(	const gsl_matrix * sqrt_p_f,
									const gsl_matrix * sqrt_p_s_,
									const gsl_matrix * c_s,
									const gsl_matrix * f2_x_,
									const gsl_matrix * sqrt_q2_xx,
									sum_workspace * w );
								 
 * @param[in] sqrt_q_f_0 : 
  \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix
 * @param[in]  sqrt_p_s_1 : 
  \f$ [P_{1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @param[in] c_s_0 : 
  \f$ [P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T \f$
 * @param[in] f2_xt :
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param w : workspace
 * @brief
 * This function computes the square root of the covariance matric of the random vector \f$ (z_{n|N}; x_{n + 1 |N} ) \f$, where \f$( z = x or t )\f$. 
 * - 1. Building the matrix 
 * \f$
 * M= \begin{pmatrix}
 * \left[Q_2^{x,x}\right]^{\frac{1}{2}}							&	0_{n_x, n_t}	&	0_{n_x, n_x}	\\
 * \left[Z_{n|n}\right]^{\frac{1}{2}} \left[F_2^{x} \right]^T	&	\left[Z_{n|n}\right]^{\frac{1}{2}}	&	0_{n_t, n_x}	\\
 * 0_{n_x, n_x}													&	\left[P_{n + 1 |N} K_{n|N}^T\right]^{\frac{1}{2}}	&	\left[P_{n + 1 |N} K_{n|N}^T\right]^{\frac{1}{2}}
 * \end{pmatrix}
 * \f$
 * - 2. QR decomposition which can be written:
 * \f$ 
   \begin{pmatrix}
 * 	M_{0,0}	&	M_{0,1}	&	M_{0,2} \\
 * 	O	    	&		M_{1,1}	&	M_{1,2} \\ 
 * 	O   	 	&		O	       &	M_{2,2}
 * \end{pmatrix}
 * \f$ 
 * -3. Cov. matrix is 
 * \f$ 
 * \begin{pmatrix}
 * 	M_{1,1}	&	M_{1,2} \\ 
 * 	0    	&	M_{2,2}
 * \end{pmatrix}
 * \f$ 
 * @warning
 * If you want to get the result, you have to build a view on the matrix \f$M\f$,  
 * - starting at \f$(0,0)\f$, ending at \f$(2 n_x - 1, 2 n_x - 1)\f$ if n > 0 
 * - or starting at \f$(0,0)\f$, ending at \f$(n_x + n_t - 1, n_x + n_t - 1)\f$ if n = 0
 *
**/
void compute_sqrt_cov_0(	const gsl_matrix * sqrt_q_f_0,
							const gsl_matrix * sqrt_p_s_1,
							const gsl_matrix * c_s_0,
							const gsl_matrix * f2_xt,
							const gsl_matrix * sqrt_q2_xx,
							sum_workspace * w )
{
	//Mise à zéro de la matrice M
	gsl_matrix_set_zero(w->mat_2xpt_2xpt());
	
	//Construction de la matrice
	//M00
	gsl_matrix_memcpy(w->mat_2xpt_2xpt_view_00(), 
					  sqrt_q2_xx);
	//M10
	gsl_blas_dgemm(CblasNoTrans,
				   CblasTrans,
				   1.0,
				   sqrt_q_f_0,
				   f2_xt,
				   0.0,
				   w->mat_2xpt_2xpt_view_10());
	//M11
	gsl_matrix_memcpy(	w->mat_2xpt_2xpt_view_11(), 
						sqrt_q_f_0);
	
	//M21
	gsl_matrix_memcpy(	w->mat_2xpt_2xpt_view_21(), 
						c_s_0);
	//M22
	gsl_matrix_memcpy(	w->mat_2xpt_2xpt_view_22(), 
						sqrt_p_s_1);
	//Décomposition QR
	gsl_linalg_QR_decomp(	w->mat_2xpt_2xpt(),
							w->vect_2xpt());
	gsl_triangle_matrix(w->mat_2xpt_2xpt());
}
	
/**@fn void tkalman::compute_sqrt_corr(	const gsl_vector * x_s,
										const gsl_vector * x_s_,
										const gsl_vector * _y,
										const gsl_vector * y,
										sum_workspace * w );
 * @param[in] x_s : 
 - \f$ \hat{x}_{n|N} \f$, smoothing state expectation
 * @param[in] x_s_ : 
 \f$ \hat{x}_{n + 1|N} \f$, following smoothing state expectation
 * @param[in] _y :
 \f$y_{n-1}\f$, previous observation
 * @param[in] y : 
 \f$y_n\f$, current observation
 * @param w : workspace
 * @brief
 * This function performs the computation of the square root of the correlation matrix of the vector \f$(t_{n|N}; t_{n + 1|N})\f$:
 * - A. Building the matrix :
 * \f$
 * \begin{pmatrix}
 * [[cov]^{\frac{1}{2}}]_{0,0}					&	[[cov]^{\frac{1}{2}}]_{0,1}			&	0	\\
 * 0											&	[[cov]^{\frac{1}{2}}]_{1,1}			&	0	\\
 * 0											&	0									&	0	\\
 * (\hat{x}_{n|N}^T, \hat{y}_{n - 1|N}^T)		&	\hat{x}_{n + 1|N}					&	y_{n}
 * \end{pmatrix}
 * \f$
 * - B. QR decompostion : Result can be written :
 * \f$
 * M = 
 * \begin{pmatrix}
 * M_{0,0}	&	M_{0,1}	&	M_{0,2}	&	M_{0,3}	\\
 * 0		&	M_{1,1}	&	M_{1,2}	&	M_{1,3}	\\
 * 0		&	0		&	M_{2,2}	&	M_{2,3}	\\
 * 0		&	0		&	0		&	M_{3,3}	\\
 * 0		&	0		&	0		&	0		
 * \end{pmatrix}
 * \f$
 * - C. Square root of the correlation matrix is given by:
 * \f$
 * \begin{pmatrix}
 * M_{0,0}	&	M_{0,1}	&	M_{0,2}	&	M_{0,3}	\\
 * 0		&	M_{1,1}	&	M_{1,2}	&	M_{1,3}	\\
 * 0		&	0		&	M_{2,2}	&	M_{2,3}	\\
 * 0		&	0		&	0		&	M_{3,3}
 * \end{pmatrix}
 * \f$
 * 
 * @warning
 * If you want to get the result, you have to build a view on the matrix \f$M\f$,  
 * - starting at \f$(0,0)\f$, ending at \f$(2 n_t - 1, 2 n_t - 1)\f$ 
 */
void compute_sqrt_corr(	const gsl_vector * x_s,
						const gsl_vector * x_s_,
						const gsl_vector * _y,
						const gsl_vector * y,
						sum_workspace * w )
{
	//Mise à zéro de M
	gsl_matrix_set_zero( w->mat_2tp1_2t() );
	
	//Construction de la matrice M
	gsl_matrix_memcpy(	w->mat_2tp1_2t_view_00(), 
						w->mat_3x3x_view_11());
	gsl_matrix_memcpy(	w->mat_2tp1_2t_view_02(), 
						w->mat_3x3x_view_12());
	gsl_matrix_memcpy(	w->mat_2tp1_2t_view_22(), 
						w->mat_3x3x_view_22());
	gsl_vector_memcpy(	w->mat_2tp1_2t_view_30(), 
						x_s);
	gsl_vector_memcpy(	w->mat_2tp1_2t_view_31(), 
						_y);
	gsl_vector_memcpy(	w->mat_2tp1_2t_view_32(), 
						x_s_);
	gsl_vector_memcpy(	w->mat_2tp1_2t_view_33(), 
						y);
	//Décomposition QR
	gsl_linalg_QR_decomp(	w->mat_2tp1_2t(),
							w->vect_2t());
	gsl_triangle_matrix(	w->mat_2tp1_2t());
	
	
}
	
	
/**@fn void tkalman::compute_sqrt_corr_0(	const gsl_vector * x_s,
										const gsl_vector * x_s_,
										const gsl_vector * _y,
										const gsl_vector * y,
										sum_workspace * w );
 * @param[in] x_s : 
 - \f$ \hat{x}_{n|N} \f$, smoothing state expectation
 * @param[in] x_s_ : 
 \f$ \hat{x}_{n + 1|N} \f$, following smoothing state expectation
 * @param[in] _y :
 \f$y_{n-1}\f$, previous observation
 * @param[in] y : 
 \f$y_n\f$, current observation
 * @param w : workspace
 * @brief
 * This function performs the computation of the square root of the correlation matrix of the vector \f$(t_{n|N}; t_{n + 1|N})\f$:
 * - A. Building the matrix :
 * \f$
 * \begin{pmatrix}
 * [[cov]^{\frac{1}{2}}]_{0,0}					&	[[cov]^{\frac{1}{2}}]_{0,1}			&	0	\\
 * 0											&	[[cov]^{\frac{1}{2}}]_{1,1}			&	0	\\
 * 0											&	0									&	0	\\
 * (\hat{x}_{n|N}^T, \hat{y}_{n - 1|N}^T)		&	\hat{x}_{n + 1|N}					&	y_{n}
 * \end{pmatrix}
 * \f$
 * - B. QR decompostion : Result can be written :
 * \f$
 * M = 
 * \begin{pmatrix}
 * M_{0,0}	&	M_{0,1}	&	M_{0,2}	&	M_{0,3}	\\
 * 0		&	M_{1,1}	&	M_{1,2}	&	M_{1,3}	\\
 * 0		&	0		&	M_{2,2}	&	M_{2,3}	\\
 * 0		&	0		&	0		&	M_{3,3}	\\
 * 0		&	0		&	0		&	0		
 * \end{pmatrix}
 * \f$
 * - C. Square root of the correlation matrix is given by:
 * \f$
 * \begin{pmatrix}
 * M_{0,0}	&	M_{0,1}	&	M_{0,2}	&	M_{0,3}	\\
 * 0		&	M_{1,1}	&	M_{1,2}	&	M_{1,3}	\\
 * 0		&	0		&	M_{2,2}	&	M_{2,3}	\\
 * 0		&	0		&	0		&	M_{3,3}
 * \end{pmatrix}
 * \f$
 * 
 * @warning
 * If you want to get the result, you have to build a view on the matrix \f$M\f$,  
 * - starting at \f$(0,0)\f$, ending at \f$(2 n_t - 1, 2 n_t - 1)\f$ 
 */
void compute_sqrt_corr_0(	const gsl_vector * t_s_0,
							const gsl_vector * x_s_1,
							const gsl_vector * y,
							sum_workspace * w )
{
	//Mise à zéro de M
	gsl_matrix_set_zero( w->mat_2tp1_2t() );
	
	//Construction de la matrice M
	gsl_matrix_memcpy(	w->mat_2tp1_2t_view_00_bis(), 
						w->mat_2xpt_2xpt_view_11());
						
	gsl_matrix_memcpy(	w->mat_2tp1_2t_view_02_bis(), 
						w->mat_2xpt_2xpt_view_12());
						
	gsl_matrix_memcpy(	w->mat_2tp1_2t_view_22(), 
						w->mat_2xpt_2xpt_view_22());
	gsl_vector_memcpy(	w->mat_2tp1_2t_view_30_bis(), 
						t_s_0);


	gsl_vector_memcpy(	w->mat_2tp1_2t_view_32(), 
						x_s_1);
	gsl_vector_memcpy(	w->mat_2tp1_2t_view_33(), 
						y);
	//Décomposition QR
	gsl_linalg_QR_decomp(	w->mat_2tp1_2t(),
							w->vect_2t());
	gsl_triangle_matrix(	w->mat_2tp1_2t());
	
}


};
using namespace tkalman;

sum :: sum ( void )
{
	initialize();
}

sum :: sum (	const gsl_matrix * f2_xt,
				const gsl_matrix * sqrt_q2_xx) throw ( exception & )
{
	initialize();
	if ( setup( f2_xt, sqrt_q2_xx ) )
		throw ( invalid_argument("invalid argument in sum :: sum") );
}

void sum :: reset()
{
	free();
	initialize();
}

int sum :: setup (	const gsl_matrix * f2_xt,
					const gsl_matrix * sqrt_q2_xx)
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

sum :: ~sum()
{
	reset();
}

void sum :: compute(	gsl_matrix * tilde_c,
						const gsl_matrix * const * sqrt_p_f,
						const gsl_vector * const * x_s,
						const gsl_matrix * const * sqrt_p_s,
						const gsl_matrix * const * c_s,
						const gsl_vector * const * y,
						unsigned int nb_observations ) const
{
	//Mise à zéro
	gsl_matrix_set_zero( w->mat_4t2t() );

	for( unsigned i = nb_observations; i > 1; --i )
	{

		compute_sqrt_cov(	sqrt_p_f[i - 1],
							sqrt_p_s[i],
							c_s[i - 1],
							&_f2_xx,
							_sqrt_q2_xx,
							w );

		compute_sqrt_corr(	x_s[i - 1],
							x_s[i],
							y[i - 2],
							y[i - 1],
							w );
		
		//Décomposition QR
		gsl_linalg_QR_decomp( 	w->mat_4t2t(),
								w->vect_2t() );
		gsl_triangle_matrix( w->mat_4t2t() );
	}

	//Cas 0
	compute_sqrt_cov_0(	sqrt_p_f[0],
						sqrt_p_s[1],
						c_s[0],
						_f2_xt,
						_sqrt_q2_xx,
						w );
						
	compute_sqrt_corr_0(	x_s[0],
							x_s[1],
							y[0],
							w );

	//Décomposition QR
	gsl_linalg_QR_decomp(w->mat_4t2t(),
						 w->vect_2t());
	gsl_triangle_matrix(w->mat_4t2t());	

	//Recopie du résultat
	gsl_matrix_memcpy(	tilde_c,
						w->mat_4t2t_view_sum() );
	
}

void sum :: free()
{
	if ( w )
		delete w;
}

void sum ::  alloc()
{
	w = new sum_workspace( _size_x, _size_y );
}

void sum :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_f2_xt = 0;
	_sqrt_q2_xx = 0;
	w = 0;
}
