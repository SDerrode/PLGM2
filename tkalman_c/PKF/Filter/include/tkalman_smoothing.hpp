#ifndef _TKALMAN_SMOOTHING_HPP_
#define _TKALMAN_SMOOTHING_HPP_
#include "tkalman_smoothing_workspace.hpp"
namespace tkalman
{
/**@fn void tkalman :: compute_x_s(	gsl_vector * x_s,
									const gsl_vector * x_f,
									const gsl_vector * x_p_,
									const gsl_vector * x_s_,
									const gsl_matrix * gain)
 * @param[out] x_s : 
 if n > 0
 \f$ \hat{x}_{n|N} \f$, smoothing state expectation
 else
 \f$ \hat{t}_{0|N} \f$, smoothing state expectation
 * @param[in] x_f : 
 if n > 0
 \f$ \hat{x}_{n|n} \f$, filtering state expectation
 else
 \f$ \hat{t}_{0|0} \f$, filtering state expectation
 * @param[in] x_p_ : 
 \f$ \hat{x}_{n + 1|n} \f$, following predicting state expectation
 * @param[in] x_s_ : 
 \f$ \hat{x}_{n + 1|N} \f$, following smoothing state expectation
 @param[in] gain : 
 \f$ K_{n|N} \f$, smoothing gain
 * @brief
 This function is intended to compute the smoothing state expectation:
 \f$  \hat{x}_{n|N} = \hat{x}_{n|n} + K_{n|N} \: (\hat{x}_{n + 1|N} - \hat{x}_{n+1|n} \f$ 
 */
void compute_x_s(	gsl_vector * x_s,
					const gsl_vector * x_f,
					const gsl_vector * x_p_,
					const gsl_vector * x_s_,
					const gsl_matrix * gain);

/**@fn void tkalman :: compute_smoothing_gain_0(	gsl_matrix * s_gain,
													const gsl_matrix * sqrt_q_f,
													const gsl_matrix * sqrt_p_p_,
													const gsl_matrix * f2_xt,
													smoothing_workspace * w )
 * @param[out] s_gain : 
 * \f$ K_{0|N} \f$, smoothing gain
 * @param[in] sqrt_q_f : 
 \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of filtering state 0 covariance matrix
 * @param[in] sqrt_p_p_ : 
 \f$[P_{1|0}]^{\frac{1}{2}}\f$, square root of predicting state 1 covariance matrix
 * @param[in] f2_xt :
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{t,x} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param w : workspace
 * @brief
 * This function computes Pairwise Kalman smoothing gain:
 * \f$K_{0|N} = Q_{0|0} [F_2^{x,t}]' [P_{1|0}]^{-1}\f$
 */
void compute_smoothing_gain_0(	gsl_matrix * s_gain,
								const gsl_matrix * sqrt_q_f,
								const gsl_matrix * sqrt_p_p_,
								const gsl_matrix * f2_xt,
								smoothing_workspace * w );

/**@fn void tkalman :: compute_smoothing_gain(	gsl_matrix * s_gain,
										const gsl_matrix * sqrt_p_f,
										const gsl_matrix * sqrt_p_p_,
										const gsl_matrix * f2_xx,
										smoothing_workspace * w)
 * @param[out] s_gain : 
 * \f$ K_{n|N} \f$, smoothing gain
 * @param[in] sqrt_p_f : 
 \f$[P_{n|n}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix
 * @param[in] sqrt_p_p_ : 
 \f$[P_{n+1|n}]^{\frac{1}{2}}\f$, square root of the following predicting state covariance matrix
 * @param[in] f2_xx :
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$
 * @param w : workspace
 * @brief
 * This function computes Pairwise Kalman smoothing gain:
 * \f$K_{n|N} = P_{n|n} [F_2^{x,x}]' [P_{n+1|n}]^{-1}\f$
 */
void compute_smoothing_gain(	gsl_matrix * s_gain,
								const gsl_matrix * sqrt_p_f,
								const gsl_matrix * sqrt_p_p_,
								const gsl_matrix * f2_xx,
								smoothing_workspace * w  );


/**@fn void tkalman :: compute_sqrt_p_s_and_c_s(	gsl_matrix * sqrt_p_s,
											gsl_matrix * c_s,
											const gsl_matrix * sqrt_p_f,
											const gsl_matrix * sqrt_p_s_,
											const gsl_matrix * f2_xx,
											const gsl_matrix * sqrt_q2_xx,
											const gsl_matrix * s_gain,
											smoothing_workspace * w )
 * @param[out] sqrt_p_s :
 \f$ [P_{n|N}]^{\frac{1}{2}}\f$, square root of the current smoothing state covariance if n > 0
 \f$ [Q_{0|N}]^{\frac{1}{2}}\f$ else
 * @param[out] c_s : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 * @param[in] sqrt_p_f : 
 \f$[P_{n|n}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix if n > 0
 \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix else
 * @param[in]  sqrt_p_s_ : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @param[in] f2_xx :
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$ if n > 0
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ else
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[in] s_gain : 
 * \f$ K_{n|N} \f$, smoothing gain 
 * @param w : workspace
 * @brief
 This function computes the square root of the current smoothing state covariance and \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 - 1. Building the matrix
 if n > 0
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[P_{n|n}]^{\frac{1}{2}} [F_2^{x,x}]' 	&	[P_{n|n}]^{\frac{1}{2}} \\
		0										&	[P_{n+1|N}]^{\frac{1}{2}} K_{n|N}' 
	\end{pmatrix}
\f$ 
else
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[Q_{0|0}]^{\frac{1}{2}} [F_2^{x,t}]' 	&	[Q_{0|0}]^{\frac{1}{2}} \\
		0										&	[P_{n+1|N}]^{\frac{1}{2}} K_{n|N}'
	\end{pmatrix}
\f$ 
 - 2.QR decomposition of the previous matrix which gives
 if n > 0
\f$
	\begin{pmatrix}
		*	&	[P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T		\\
		0 	&	[P_{n|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
else
\f$
	\begin{pmatrix}
		*	&	[P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T		\\
		0 	&	[Q_{0|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
 * 
 * 
**/
void compute_sqrt_p_s_and_c_s(	gsl_matrix * sqrt_p_s,
								gsl_matrix * c_s,
								const gsl_matrix * sqrt_p_f,
								const gsl_matrix * sqrt_p_s_,
								const gsl_matrix * f2_xx,
								const gsl_matrix * sqrt_q2_xx,
								const gsl_matrix * s_gain,
								smoothing_workspace * w );

/**@fn void tkalman :: compute_sqrt_p_s_and_c_s_0(	gsl_matrix * sqrt_p_s,
											gsl_matrix * c_s,
											const gsl_matrix * sqrt_p_f,
											const gsl_matrix * sqrt_p_s_,
											const gsl_matrix * f2_xx,
											const gsl_matrix * sqrt_q2_xx,
											const gsl_matrix * s_gain,
											smoothing_workspace * w )
 * @param[out] sqrt_p_s :
 \f$ [P_{n|N}]^{\frac{1}{2}}\f$, square root of the current smoothing state covariance if n > 0
 \f$ [Q_{0|N}]^{\frac{1}{2}}\f$ else
 * @param[out] c_s : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 * @param[in] sqrt_p_f : 
 \f$[P_{n|n}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix if n > 0
 \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix else
 * @param[in]  sqrt_p_s_ : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @param[in] f2_xx :
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$ if n > 0
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ else
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[in] s_gain : 
 * \f$ K_{n|N} \f$, smoothing gain 
 * @param w : workspace
 * @brief
 This function computes the square root of the current smoothing state covariance and \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 - 1. Building the matrix
 if n > 0
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[P_{n|n}]^{\frac{1}{2}} [F_2^{x,x}]' 	&	[P_{n|n}]^{\frac{1}{2}} \\
		0										&	[P_{n+1|N}]^{\frac{1}{2}} K_{n|N}' 
	\end{pmatrix}
\f$ 
else
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[Q_{0|0}]^{\frac{1}{2}} [F_2^{x,t}]' 	&	[Q_{0|0}]^{\frac{1}{2}} \\
		0										&	[P_{n+1|N}]^{\frac{1}{2}} K_{n|N}'
	\end{pmatrix}
\f$ 
 - 2.QR decomposition of the previous matrix which gives
 if n > 0
\f$
	\begin{pmatrix}
		*	&	[P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T		\\
		0 	&	[P_{n|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
else
\f$
	\begin{pmatrix}
		*	&	[P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T		\\
		0 	&	[Q_{0|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
 * 
 * 
**/
void compute_sqrt_p_s_and_c_s_0(	gsl_matrix * sqrt_q_s_0,
									gsl_matrix * c_s_0,
									const gsl_matrix * sqrt_q_f,
									const gsl_matrix * sqrt_p_s_1,
									const gsl_matrix * f2_xt,
									const gsl_matrix * sqrt_q2_xx,
									const gsl_matrix * s_gain,
									smoothing_workspace * w );

/**@fn void tkalman :: compute_smoothing(	gsl_vector * x_s,
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
 * @param[out] x_s : 
 \f$ \hat{x}_{n|N} \f$, smoothing state expectation
 * @param[out] sqrt_p_s :
 \f$ [P_{n|N}]^{\frac{1}{2}}\f$, square root of the current smoothing state covariance
 * @param[out] c_s : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 * @param[in] x_f : 
 \f$ \hat{x}_{n|n} \f$, filtering state expectation
 * @param[in] sqrt_p_f : 
 \f$[P_{n|n}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix
 * @param[in] x_p_ : 
 \f$ \hat{x}_{n + 1|n} \f$, following predicting state expectation
 * @param[in] sqrt_p_p_ : 
 \f$[P_{n+1|n}]^{\frac{1}{2}}\f$, square root of the following predicting state covariance matrix
 * @param[in] x_s_ : 
 \f$ \hat{x}_{n + 1|N} \f$, following smoothing state expectation
 * @param[in]  sqrt_p_s_ : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @param[in] f2_xx :
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param w : workspace
 * @brief
 This function does the smoothing step of Pairwise Kalman filter.
 - 1.This function computes Pairwise Kalman smoothing gain:
  \f$K_{n|N} = P_{n|n} [F_2^{x,x}]' [P_{n+1|n}]^{-1}\f$
 - 2. Computing the smoothing state expectation:
  \f$  \hat{x}_{n|N} = \hat{x}_{n|n} + K_{n|N} \: (\hat{x}_{n + 1|N} - \hat{x}_{n+1|n} \f$ 
 - 3. Computing the square root of the current smoothing state covariance and \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 - A. Building the matrix
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[P_{n|n}]^{\frac{1}{2}} [F_2^{x,x}]' 	&	[P_{n|n}]^{\frac{1}{2}} \\
		0										&	[P_{n+1|N}]^{\frac{1}{2}} K_{n|N}' 
	\end{pmatrix}
\f$
 - B.QR decomposition of the previous matrix which gives
\f$
	\begin{pmatrix}
		*	&	[P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T		\\
		0 	&	[P_{n|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
 *  
**/
void compute_smoothing(	gsl_vector * x_s,
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
						smoothing_workspace * w );

/**@fn void tkalman :: compute_smoothing_0(	gsl_vector * t_s_0,
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
											smoothing_workspace * w );
 * @param[out] t_s_0 : 
 \f$ \hat{t}_{0|N} \f$, smoothing state expectation
 * @param[out] sqrt_q_s_0 :
 \f$ [Q_{0|N}]^{\frac{1}{2}}\f$
 * @param[out] c_s_0 : 
 \f$ [P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T \f$
 * @param[in] t_f_0 : 
 \f$ \hat{t}_{0|0} \f$, filtering state expectation
 * @param[in] sqrt_q_f_0 : 
 \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix 
 * @param[in] x_p_1 : 
 \f$ \hat{x}_{1|0} \f$, following predicting state expectation
 * @param[in] sqrt_p_p_1 : 
 \f$[P_{1|0}]^{\frac{1}{2}}\f$, square root of the following predicting state covariance matrix
 * @param[in] x_s_1 : 
 \f$ \hat{x}_{1|N} \f$, following smoothing state expectation
 * @param[in]  sqrt_p_s_1 : 
 \f$ [P_{1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @param[in] f2_xt :
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ 
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param w : workspace
 * @brief
  This function does the smoothing step of Pairwise Kalman filter.
 - 1.This function computes Pairwise Kalman smoothing gain:
  \f$K_{0|N} = Q_{0|0} [F_2^{x,t}]' [P_{1|0}]^{-1}\f$
 - 2. Computing the smoothing state expectation:
  \f$  \hat{t}_{0|N} = \hat{x}_{0|0} + K_{0|N} \: (\hat{x}_{1|N} - \hat{x}_{1|0} \f$ 
 - 3. Computing the square root of the current smoothing state covariance and \f$ [P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T \f$
 - A. Building the matrix
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[Q_{0|0}]^{\frac{1}{2}} [F_2^{x,t}]' 	&	[Q_{0|0}]^{\frac{1}{2}} \\
		0										&	[P_{1|N}]^{\frac{1}{2}} K_{0|N}'
	\end{pmatrix}
\f$
 - B.QR decomposition of the previous matrix which gives
\f$
	\begin{pmatrix}
		*	&	[P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T		\\
		0 	&	[P_{0|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
**/
void compute_smoothing_0(	gsl_vector * t_s_0,
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
							smoothing_workspace * w );
							

/**@class tkalman :: smoothing
 * @brief
 * PK smoothing
 * 
 **/
class smoothing
{
public:
/**@fn tkalman :: smoothing :: smoothing()
 * @brief
 * Default constructor
 **/
smoothing();

/**@fn tkalman :: smoothing :: smoothing (	const gsl_matrix * f2_xt, 
											const gsl_matrix * sqrt_q2_xx )
 * @param f2_xt : \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ 
 * @param sqrt_q2_xx : \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance
 * @brief
 * Constructor
 **/
smoothing (	const gsl_matrix * f2_xt, 
			const gsl_matrix * sqrt_q2_xx ) throw (exception & );

/**@fn void tkalman :: smoothing :: reset ( );
 * @brief
 * Reset
 **/
void reset ( ); 

/**@fn int tkalman :: smoothing :: setup(	const gsl_matrix * f2_xt, 
											const gsl_matrix * sqrt_q2_xx );  
 * @param f2_xt : \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ 
 * @param sqrt_q2_xx : \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance
 * @brief
 * Setup.
 **/
int setup(	const gsl_matrix * f2_xt, 
			const gsl_matrix * sqrt_q2_xx );  

/**@fn tkalman :: smoothing :: ~smoothing();
 **/
virtual ~smoothing();

//Calcul
/**@fn void tkalman :: smoothing :: compute(	gsl_vector * x_s,
												gsl_matrix * sqrt_p_s,
												gsl_matrix * c_s,
												const gsl_vector * x_f,
												const gsl_matrix * sqrt_p_f,
												const gsl_vector * x_p_,
												const gsl_matrix * sqrt_p_p_,
												const gsl_vector * x_s_,
												const gsl_matrix * sqrt_p_s_ );
 * @param[out] x_s : 
 \f$ \hat{x}_{n|N} \f$, smoothing state expectation
 * @param[out] sqrt_p_s :
 \f$ [P_{n|N}]^{\frac{1}{2}}\f$, square root of the current smoothing state covariance
 * @param[out] c_s : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 * @param[in] x_f : 
 \f$ \hat{x}_{n|n} \f$, filtering state expectation
 * @param[in] sqrt_p_f : 
 \f$[P_{n|n}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix
 * @param[in] x_p_ : 
 \f$ \hat{x}_{n + 1|n} \f$, following predicting state expectation
 * @param[in] sqrt_p_p_ : 
 \f$[P_{n+1|n}]^{\frac{1}{2}}\f$, square root of the following predicting state covariance matrix
 * @param[in] x_s_ : 
 \f$ \hat{x}_{n + 1|N} \f$, following smoothing state expectation
 * @param[in]  sqrt_p_s_ : 
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
 * @brief
 This function does the smoothing step of Pairwise Kalman filter.
 - 1.This function computes Pairwise Kalman smoothing gain:
  \f$K_{n|N} = P_{n|n} [F_2^{x,x}]' [P_{n+1|n}]^{-1}\f$
 - 2. Computing the smoothing state expectation:
  \f$  \hat{x}_{n|N} = \hat{x}_{n|n} + K_{n|N} \: (\hat{x}_{n + 1|N} - \hat{x}_{n+1|n} \f$ 
 - 3. Computing the square root of the current smoothing state covariance and \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 - A. Building the matrix
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[P_{n|n}]^{\frac{1}{2}} [F_2^{x,x}]' 	&	[P_{n|n}]^{\frac{1}{2}} \\
		0										&	[P_{n+1|N}]^{\frac{1}{2}} K_{n|N}' 
	\end{pmatrix}
\f$
 - B.QR decomposition of the previous matrix which gives
\f$
	\begin{pmatrix}
		*	&	[P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T		\\
		0 	&	[P_{n|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
 **/
void compute(	gsl_vector * x_s,
				gsl_matrix * sqrt_p_s,
				gsl_matrix * c_s,
				const gsl_vector * x_f,
				const gsl_matrix * sqrt_p_f,
				const gsl_vector * x_p_,
				const gsl_matrix * sqrt_p_p_,
				const gsl_vector * x_s_,
				const gsl_matrix * sqrt_p_s_ ) const;
				
/**@fn void tkalman :: smoothing :: compute_0( 	gsl_vector * t_s_0,
												gsl_matrix * sqrt_q_s_0,
												gsl_matrix * c_s_0,
												const gsl_vector * t_f_0,
												const gsl_matrix * sqrt_q_f_0,
												const gsl_vector * x_p_1,
												const gsl_matrix * sqrt_p_p_1,
												const gsl_vector * x_s_1,
												const gsl_matrix * sqrt_p_s_1 );
 * @param[out] t_s_0 : 
 \f$ \hat{t}_{0|N} \f$, smoothing state expectation
 * @param[out] sqrt_q_s_0 :
 \f$ [Q_{0|N}]^{\frac{1}{2}}\f$
 * @param[out] c_s_0 : 
 \f$ [P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T \f$
 * @param[in] t_f_0 : 
 \f$ \hat{t}_{0|0} \f$, filtering state expectation
 * @param[in] sqrt_q_f_0 : 
 \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of the current filtering state covariance matrix 
 * @param[in] x_p_1 : 
 \f$ \hat{x}_{1|0} \f$, following predicting state expectation
 * @param[in] sqrt_p_p_1 : 
 \f$[P_{1|0}]^{\frac{1}{2}}\f$, square root of the following predicting state covariance matrix
 * @param[in] x_s_1 : 
 \f$ \hat{x}_{1|N} \f$, following smoothing state expectation
 * @param[in]  sqrt_p_s_1 : 
 \f$ [P_{1|N}]^{\frac{1}{2}}  \f$, square root of the following smoothing state covariance
  * @brief
  This function does the smoothing step of Pairwise Kalman filter.
 - 1.This function computes Pairwise Kalman smoothing gain:
  \f$K_{0|N} = Q_{0|0} [F_2^{x,t}]' [P_{1|0}]^{-1}\f$
 - 2. Computing the smoothing state expectation:
  \f$  \hat{t}_{0|N} = \hat{x}_{0|0} + K_{0|N} \: (\hat{x}_{1|N} - \hat{x}_{1|0} \f$ 
 - 3. Computing the square root of the current smoothing state covariance and \f$ [P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T \f$
 - A. Building the matrix
\f$
	\begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}}				&	0						\\
		[Q_{0|0}]^{\frac{1}{2}} [F_2^{x,t}]' 	&	[Q_{0|0}]^{\frac{1}{2}} \\
		0										&	[P_{1|N}]^{\frac{1}{2}} K_{0|N}'
	\end{pmatrix}
\f$
 - B.QR decomposition of the previous matrix which gives
\f$
	\begin{pmatrix}
		*	&	[P_{1|N}]^{\frac{1}{2}}\ \; K_{0|N}^T		\\
		0 	&	[P_{0|N}]^{\frac{1}{2}} \\
		0	&	0
	\end{pmatrix}
\f$ 
 * */
void compute_0( gsl_vector * t_s_0,
				gsl_matrix * sqrt_q_s_0,
				gsl_matrix * c_s_0,
				const gsl_vector * t_f_0,
				const gsl_matrix * sqrt_q_f_0,
				const gsl_vector * x_p_1,
				const gsl_matrix * sqrt_p_p_1,
				const gsl_vector * x_s_1,
				const gsl_matrix * sqrt_p_s_1 ) const;


//Accesseurs
/**@fn inline unsigned int tkalman :: smoothing :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: smoothing :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: smoothing :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn inline gsl_matrix tkalman :: smoothing :: f2_xt() const
 * @return
 * \f$ F_2^{x,t}\f$
 **/
inline const gsl_matrix * f2_xt() const
{
	return _f2_xt;
}

/**@fn inline gsl_matrix tkalman :: smoothing :: f2_xx() const
 * @return
 * \f$ F_2^{x,x}\f$
 **/
inline const gsl_matrix * f2_xx() const
{
	return &_f2_xx;
}


/**@fn inline gsl_matrix tkalman :: smoothing :: f2_xy() const
 * @return
 * \f$ F_2^{x,y}\f$
 **/
inline const gsl_matrix * f2_xy() const
{
	return &_f2_xy;
}

/**@fn inline gsl_matrix tkalman :: smoothing :: sqrt_q2_xx() const
 * @return
 \f$ [Q_2^{x,x}]^{\frac{1}{2}} \f$
 **/
inline const gsl_matrix * sqrt_q2_xx() const
{
	return _sqrt_q2_xx;
}

protected:
/**@fn void tkalman :: prediction :: free( );
 * @brief
 * This function frees memory.
 */
void free();

/**@fn void tkalman :: prediction :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

/**@fn void tkalman :: prediction :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();
//Paramètres
unsigned int 	_size_x,
				_size_y,
				_size_t;
const gsl_matrix * _f2_xt;
gsl_matrix _f2_xx;
gsl_matrix _f2_xy;
const gsl_matrix * _sqrt_q2_xx;

mutable smoothing_workspace * w;
};
};


#endif
