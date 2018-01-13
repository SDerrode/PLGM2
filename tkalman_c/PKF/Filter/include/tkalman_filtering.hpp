#ifndef _TKALMAN_FILTERING_HPP_
#define _TKALMAN_FILTERING_HPP_
#include "tkalman_filtering_workspace.hpp"
namespace tkalman
{
	
	
/**@fn void tkalman :: compute_innovation(	gsl_vector * innovation,
											const gsl_vector * x_p,
											const gsl_vector * _y,
											const gsl_vector * y,
											const gsl_matrix * f_yx,
											const gsl_matrix * f_yy)
 * @param[out] innovation : innovation, \f$ \tilde{y}_{n} \f$
 * @param[in] x_p : \f$ \hat{x}_{n | n - 1} \f$, predicting state expectation
 * @param[in] _y: \f$ \hat{y}_{n - 1} \f$, previous observation
 * @param[in] y : \f$ \hat{y}_{n} \f$, current observation
 * @param[in] f_yx : \f$ F^{y,x} \f$
 * @param[in] f_yy : \f$ F^{y,y} \f$
 * @brief
 -> computes innovation.
 **/
void compute_innovation (	gsl_vector * innovation,
							const gsl_vector * x_p,
							const gsl_vector * _y,
							const gsl_vector * y,
							const gsl_matrix * f_yx,
							const gsl_matrix * f_yy);
	
	
/**@fn void tkalman :: compute_x_f(	gsl_vector * x_f,
									const gsl_vector * x_p,
									const gsl_vector * innovation,
									const gsl_matrix * gain)
 * @param[out] x_f : filtering state expectation, \f$ \hat{x}_{n|n}\f$
 * @param[in] x_p : \f$ \hat{x}_{n | n - 1} \f$, predicting state expectation
 * @param[in] innovation : innovation, \f$ \tilde{y}_{n} \f$
 * @param[in] gain : PK gain
 * @brief
computes filtering state expectation.
 */
void compute_x_f(gsl_vector * x_f,
				 const gsl_vector * x_p,
				 const gsl_vector * innovation,
				 const gsl_matrix * gain);
			
/**@fn void  tkalman :: compute_sqrt_pf_sqrt_s_and_gain(	gsl_matrix * sqrt_p_f,
															gsl_matrix * sqrt_s,
															gsl_matrix * gain,
															const gsl_matrix * sqrt_p_p,
															const gsl_matrix * f_yx,
															const gsl_matrix * sqrt_q_yy,
															filtering_workspace * w )
	 * @param[out] sqrt_p_f : 
	 \f$ [P_{n|n}]^{\frac{1}{2}} \f$, square root of filtering state covariance
	 * @param[out] sqrt_s : 
	 \f$ [S_{n}]^{\frac{1}{2}}  \f$, square root of innovation covariance
	 * @param[in] sqrt_p_p : 
	 \f$ [P_{n|n-1}]^{\frac{1}{2}}  \f$, square root of predicting state covariance
	 * @param[in] f_yx : 
	 \f$ F^{y,x} \f$, submatrix of transition matrix.
	 * @param[in] f_yy : 
	 \f$ F^{y,y} \f$, submatrix of transition matrix.
	 * @param[in] sqrt_q_yy : 
	 \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
	 * @param w : workspace
**/	 
void compute_sqrt_pf_sqrt_s_and_gain(	gsl_matrix * sqrt_p_f,
										gsl_matrix * sqrt_s,
										gsl_matrix * gain,
										const gsl_matrix * sqrt_p_p,
									 	const gsl_matrix * f_yx,
										const gsl_matrix * sqrt_q_yy,
										filtering_workspace * w );
				 
/**@fn void  tkalman :: compute_sqrt_pf_sqrt_s_and_gain_0(	gsl_matrix * sqrt_q_f_0,
															gsl_matrix * sqrt_s_0,
															gsl_matrix * gain_0,
															const gsl_matrix * sqrt_q_0,
															const gsl_matrix * f_yt,
															const gsl_matrix * sqrt_q_yy,
															filtering_workspace * w );
* @param[out] t_f_0 : \f$ \hat{t}_{0|0} \f$, initial filtering state expectation
* @param[out] sqrt_q_f_0, : \f$ [Q_{0|0}]^{\frac{1}{2}} \f$, square root of initial filtering state covariance
* @param[out] sqrt_s_0 : \f$ [S_{0}]^{\frac{1}{2}}  \f$, square root of initial innovation covariance
* @param[in] sqrt_q_0 : \f$ [Q_{0}]^{\frac{1}{2}}  \f$, square root of initial (predicting) state covariance
* @param[in] f_yt : \f$ F^{y,t} \f$, submatrix of transition matrix.
* @param[in] sqrt_q_yy : \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
* @param w : workspace
**/	 
void compute_sqrt_pf_sqrt_s_and_gain_0(	gsl_matrix * sqrt_q_f_0,
										gsl_matrix * sqrt_s_0,
										gsl_matrix * gain_0,
										const gsl_matrix * sqrt_q_0,
										const gsl_matrix * f_yt,
										const gsl_matrix * sqrt_q_yy,
										filtering_workspace * w );
	
/**@fn void tkalman :: compute_filtering(gsl_vector * x_f,
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
 * @param[out] x_f : 
 \f$ \hat{x}_{n|n} \f$, filtering state expectation
 
 * @param[out] sqrt_p_f : 
 \f$ [P_{n|n}]^{\frac{1}{2}} \f$, square root of filtering state covariance
 
 * @param[out] innovation : 
 \f$ \tilde{y}_{n} \f$, innovation expectation
 
 * @param[out] sqrt_s : 
 \f$ [S_{n}]^{\frac{1}{2}}  \f$, square root of innovation covariance
 
 * @param[in] x_p : 
 \f$ \hat{x}_{n | n - 1} \f$, predicting state expectation
 * @param[in] sqrt_p_p : 
 \f$ [P_{n|n-1}]^{\frac{1}{2}}  \f$, square root of predicting state covariance
 
 * @param[in] y : 
 \f$y_n\f$, current observation
 
 * @param[in] _y :
 \f$y_{n-1}\f$, previous observation
 
 * @param[in] f_yx : 
 \f$ F^{y,x} \f$, submatrix of transition matrix.
 
 * @param[in] f_yy : 
 \f$ F^{y,y} \f$, submatrix of transition matrix.
 
 * @param[in] sqrt_q_yy : 
 \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
 
* @param w : workspace
 
 * @brief
 This function does the Pairwise Kalman filtering.
 - 1. Computing innovation expectation
 \f$ \tilde{y}_{n} = y_n - F^{y,x} \hat{x}_{n | n - 1} - F^{y,y} y_{n-1} \f$
 - 2. Computing the matrix
 \f$ 
 M = 
 \begin{pmatrix}
	[Q^{y,y}]^{\frac{1}{2}} 				& 0	\\
	[P_{n|n-1}]^{\frac{1}{2}} [F^{y,x}]'	& [P_{n|n-1}]^{\frac{1}{2}}
 \end{pmatrix}
 \f$
 - 3. QR decompostion of the previous matrix, which gives:
 \f$
 \begin{pmatrix}
	[S_{n}]^{\frac{1}{2}}		& [S_{n}]^{\frac{1}{2}} K_{n,n}^T	\\
	0							& [P_{n|n}]^{\frac{1}{2}}
 \end{pmatrix}
 \f$
 - 4. Calculation of filtering state expectation:
 \f$
	\hat{x}_{n|n} = \hat{x}_{n|n - 1} + K_{n,n} \tilde{y}_{n}
 \f$
 */
void compute_filtering(	gsl_vector * x_f,
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
						filtering_workspace * w );
	
/**@fn void tkalman :: compute_filtering_0(gsl_vector * t_f_0,
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
							filtering_workspace * w );
 * @param[out] t_f_0 : 
 \f$ \hat{t}_{0|0} \f$, initial filtering state expectation
 * @param[out] sqrt_q_f_0, : 
 \f$ [Q_{0|0}]^{\frac{1}{2}} \f$, square root of initial filtering state covariance
 
 * @param[out] innovation : 
 \f$ \tilde{y}_{0} \f$, initial innovation expectation
 
 * @param[out] sqrt_s_0 : 
 \f$ [S_{0}]^{\frac{1}{2}}  \f$, square root of initial innovation covariance
 
 * @param[in] t_0, : 
 \f$ \hat{t}_{0} \f$, initial (predicting) state expectation

 * @param[in] x_0 : 
 \f$ \hat{x}_{0}\f$, initial (predicting) state expectation
 
 @param[in] sqrt_q_0 :
 \f$ [Q_{0}]^{\frac{1}{2}}  \f$, square root of initial (predicting) state covariance
 
 * @param[in] y_0 : 
 \f$y_0\f$, initial observation
 
 * @param[in] y_m1 : 
 \f$y_{-1}\f$, observation "-1" expectation
 
 * @param[in] f_yt : 
 \f$ F^{y,t} \f$, submatrix of transition matrix.
 
 * @param[in] f_yx : 
 \f$ F^{y,x} \f$, submatrix of transition matrix.
 
 * @param[in] f_yy : 
 \f$ F^{y,y} \f$, submatrix of transition matrix.
 
 * @param[in] sqrt_q_yy : 
 \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
* @param w : workspace
 * @brief
 This function does the Pairwise Kalman filtering.
 - 1. Computing innovation expectation
 \f$ \tilde{y}_{0} = y_0 - F^{y,t} \hat{t}_{0} - F^{y,y} \hat{y}_{-1} \f$
 - 2. Computing the matrix
 \f$ 
 M = 
 \begin{pmatrix}
	[Q^{y,y}]^{\frac{1}{2}} 				& 0	\\
	[Q_{0}]^{\frac{1}{2}} [F^{y,t}]'	& [Q_{0}]^{\frac{1}{2}}
 \end{pmatrix}
 \f$
 - 3. QR decompostion of the previous matrix, which gives:
 \f$
 \begin{pmatrix}
	[S_{0}]^{\frac{1}{2}}		& [S_{0}]^{\frac{1}{2}} K_{n,n}^T	\\
	0							& [Q_{0|0}]^{\frac{1}{2}}
 \end{pmatrix}
 \f$
 - 4. Calculation of filtering state expectation:
 \f$
	\hat{x}_{0|0} = \hat{x}_{0} + K_{0,0} \tilde{y}_{0}
 \f$
 */
void compute_filtering_0(	gsl_vector * t_f_0,
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
							filtering_workspace * w );

/**@class tkalman :: filtering
 * @brief
 * PK filtering
 **/
class filtering
{
public:
/**@fn tkalman :: filtering :: filtering ();
 * @brief
 * Default constructor
 * 
 **/
filtering ();

/**@fn tkalman :: filtering :: filtering(	const gsl_matrix * f_yt,
											const gsl_matrix * sqrt_q_yy);
 * @param[in] f_yt : 
 \f$ F^{y,t} \f$, submatrix of transition matrix.
 * @param[in] sqrt_q_yy : 
 \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
 **/
filtering(	const gsl_matrix * f_yt,
			const gsl_matrix * sqrt_q_yy) throw(exception & );

/**@fn void tkalman :: filtering :: reset()
 * @brief
 * - Reset
 * - frees object memory
 * - sets object attributes to 0.
 * 
 */
virtual void reset(); 
		
/**@fn int tkalman :: setup (	const gsl_matrix * f_yt,
								const gsl_matrix * sqrt_q_yy) 
 * @param[in] f_yt : 
 \f$ F^{y,t} \f$, submatrix of transition matrix.
 * @param[in] sqrt_q_yy : 
 \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
 **/
virtual int setup (	const gsl_matrix * f_yt,
					const gsl_matrix * sqrt_q_yy);
		
/**@fn tkalman :: filtering :: ~filtering();
 **/
virtual ~filtering();
		
		
//Filtrages
/**@fn void tkalman :: filtering :: compute(	gsl_vector * x_f,
												gsl_matrix * sqrt_p_f,
												gsl_vector * innovation,
												gsl_matrix * sqrt_s,
												const gsl_vector * x_p,
												const gsl_matrix * sqrt_p_p,
												const gsl_vector * y,
												const gsl_vector * _y);
 * @param[out] x_f : 
 \f$ \hat{x}_{n|n} \f$, filtering state expectation
 
 * @param[out] sqrt_p_f : 
 \f$ [P_{n|n}]^{\frac{1}{2}} \f$, square root of filtering state covariance
 
 * @param[out] innovation : 
 \f$ \tilde{y}_{n} \f$, innovation expectation
 
 * @param[out] sqrt_s : 
 \f$ [S_{n}]^{\frac{1}{2}}  \f$, square root of innovation covariance

 * @param[in] x_p : 
 \f$ \hat{x}_{n | n - 1} \f$, predicting state expectation
 * @param[in] sqrt_p_p : 
 \f$ [P_{n|n-1}]^{\frac{1}{2}}  \f$, square root of predicting state covariance
 
 * @param[in] y : 
 \f$y_n\f$, current observation
 
 * @param[in] _y :
 \f$y_{n-1}\f$, previous observation
 
 **/
void compute(	gsl_vector * x_f,
				gsl_matrix * sqrt_p_f,
				gsl_vector * innovation,
				gsl_matrix * sqrt_s,
				const gsl_vector * x_p,
				const gsl_matrix * sqrt_p_p,
				const gsl_vector * y,
				const gsl_vector * _y) const;
				
/**@fn void tkalman :: filtering :: compute_0( 	gsl_vector * t_f_0,
												gsl_matrix * sqrt_q_f_0,
												gsl_vector * innovation,
												gsl_matrix * sqrt_s_0,
												const gsl_vector * t_0,
												const gsl_matrix * sqrt_q_0,
												const gsl_vector * y_0 );
 * @param[out] t_f_0 : 
 \f$ \hat{t}_{0|0} \f$, initial filtering state expectation
 * @param[out] sqrt_q_f_0, : 
 \f$ [Q_{0|0}]^{\frac{1}{2}} \f$, square root of initial filtering state covariance
 
 * @param[out] innovation : 
 \f$ \tilde{y}_{0} \f$, initial innovation expectation
 
 * @param[out] sqrt_s_0 : 
 \f$ [S_{0}]^{\frac{1}{2}}  \f$, square root of initial innovation covariance
 
 * @param[in] t_0, : 
 \f$ \hat{t}_{0} \f$, initial (predicting) state expectation

 * @param[in] x_0 : 
 \f$ \hat{x}_{0}\f$, initial (predicting) state expectation
 
 @param[in] sqrt_q_0 :
 \f$ [Q_{0}]^{\frac{1}{2}}  \f$, square root of initial (predicting) state covariance
 
 * @param[in] y_0 : 
 \f$y_0\f$, initial observation
 
 **/
void compute_0( gsl_vector * t_f_0,
				gsl_matrix * sqrt_q_f_0,
				gsl_vector * innovation,
				gsl_matrix * sqrt_s_0,
				const gsl_vector * t_0,
				const gsl_matrix * sqrt_q_0,
				const gsl_vector * y_0 ) const;
		
//Accesseurs
/**@fn inline unsigned int tkalman :: filtering :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: filtering :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: filtering :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn const gsl_matrix * tkalman :: filtering ::f_yt() const
 * @return \f$ F^{y,t}\f$
 **/
inline const gsl_matrix * f_yt() const
{
	return _f_yt;
}

/**@fn const gsl_matrix * tkalman :: filtering ::f_yx() const
 * @return \f$ F^{y,x}\f$
 **/
inline const gsl_matrix * f_yx() const
{
	return &_f_yx;
}

/**@fn const gsl_matrix * tkalman :: filtering ::f_yy() const
 * @return \f$ F^{y,y}\f$
 **/
inline const gsl_matrix * f_yy() const
{
	return &_f_yy;
}

/**@fn const gsl_matrix * tkalman :: filtering ::sqrt_q_yy() const
 * @return \f$ [Q^{y,y}]^{\frac{1}{2}}\f$
 **/
inline const gsl_matrix * sqrt_q_yy() const
{
	return _sqrt_q_yy;
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

unsigned int _size_x;
unsigned int _size_y;
unsigned int _size_t;
const gsl_matrix * _f_yt;
gsl_matrix _f_yx;
gsl_matrix _f_yy;
const gsl_matrix * _sqrt_q_yy;
mutable filtering_workspace * w;


};




};




#endif
