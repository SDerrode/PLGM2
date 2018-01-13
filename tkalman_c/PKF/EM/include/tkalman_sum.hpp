#ifndef _TKALMAN_SUM_HPP_
#define _TKALMAN_SUM_HPP_
#include "tkalman_sum_workspace.hpp"
namespace tkalman
{


/**@class
 * PK sum
 * 
 **/
class sum
{
public:
/**@fn tkalman :: sum ( void )
 * @brief
 * Default constructor
 **/
sum ( void );

/**@fn tkalman :: sum (	const gsl_matrix * f2_xt,
						const gsl_matrix * sqrt_q2_xx);
 * @param f2_xt : \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ 
 * @param sqrt_q2_xx : \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance
 * @brief
 * Constructor
 **/
sum (	const gsl_matrix * f2_xt,
		const gsl_matrix * sqrt_q2_xx) throw ( exception & );

/**@fn void tkalman :: sum :: reset ( );
 * @brief
 * Reset
 **/
void reset();

/**@fn int tkalman :: sum :: setup (	const gsl_matrix * f2_xt,
									const gsl_matrix * sqrt_q2_xx); 
 * @param f2_xt : \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$ 
 * @param sqrt_q2_xx : \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance
 * @brief
 * Setup
 **/
int setup (	const gsl_matrix * f2_xt,
			const gsl_matrix * sqrt_q2_xx);

/**@fn tkalman :: sum :: ~sum()
 * @brief
 * Destructor
 **/
~sum();

/**@fn void  tkalman :: sum :: compute(	gsl_matrix * tilde_c,
										const gsl_matrix * const * sqrt_p_f,
										const gsl_vector * const * x_s,
										const gsl_matrix * const * sqrt_p_s,
										const gsl_matrix * const * c_s,
										const gsl_vector * const * y,
										unsigned int nb_observations );
 * @param[in] sqrt_p_f : 
 \f$[P_{n|n}]^{\frac{1}{2}}\f$, square roots of the filtering state covariance matrix
 * @param[in] x_s : 
 \f$ \hat{x}_{n|N} \f$, smoothing state expectations
 * @param[in] sqrt_p_s : 
 \f$[P_{n|N}]^{\frac{1}{2}}\f$, square roots of the smoothing state covariance matrix
 * @param[in] c_s :  
 \f$ [P_{n + 1|N}]^{\frac{1}{2}}\ \; K_{n|N}^T \f$
 * @param[in] y : 
 \f$ y_{n} \f$, observations
 * @param[in] nb_observations : 
 number of observations.
 * @brief
 * Computing EM sums.
 * - A. Initialising 
 * \f$
 * 	[W_N]^{\frac{1}{2}} = [Corr(t_{N|N}; t_{N + 1|N}) ]^{\frac{1}{2}} =
 * \f$
 * - B. For p = N - 1 to 0
 *   -- Building the matrix
 * \f$
 * M_p = 
 * \begin{pmatrix}
 * [W_{p+1}]^{\frac{1}{2}}
 * [Corr(t_{p|N}; t_{p + 1|N}) ]^{\frac{1}{2}}
 * \end{pmatrix}
 * 
 * \f$
 * -- QR decompositon which gives:
 * \f$ 
 * M_p' = 
 * \begin{pmatrix}
 * [W_{p}]^{\frac{1}{2}} \\
 * 0
 * \end{pmatrix}
 * \f$
 * - C. Result gives:
 * \f$
 * M_{sums} = W_{0} = 
 * [
 * \begin{pmatrix}
 * \tilde{C}_{0,0} & \tilde{C}_{0,1} \\
 * \tilde{C}_{1,0} & \tilde{C}_{1,1}
 * \end{pmatrix}
 * ]^{\frac{1}{2}}
 * \f$
 */
void compute(	gsl_matrix * tilde_c,
				const gsl_matrix * const * sqrt_p_f,
				const gsl_vector * const * x_s,
				const gsl_matrix * const * sqrt_p_s,
				const gsl_matrix * const * c_s,
				const gsl_vector * const * y,
				unsigned int nb_observations ) const;



//Accesseurs
/**@fn inline unsigned int tkalman :: sum :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: sum :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: sum :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn inline gsl_matrix tkalman :: sum :: f2_xt() const
 * @return
 * \f$ F_2^{x,t}\f$
 **/
inline const gsl_matrix * f2_xt() const
{
	return _f2_xt;
}

/**@fn inline gsl_matrix tkalman :: sum :: f2_xx() const
 * @return
 * \f$ F_2^{x,x}\f$
 **/
inline const gsl_matrix * f2_xx() const
{
	return &_f2_xx;
}


/**@fn inline gsl_matrix tkalman :: sum :: f2_xy() const
 * @return
 * \f$ F_2^{x,y}\f$
 **/
inline const gsl_matrix * f2_xy() const
{
	return &_f2_xy;
}

/**@fn inline gsl_matrix tkalman :: sum :: sqrt_q2_xx() const
 * @return
 \f$ [Q_2^{x,x}]^{\frac{1}{2}} \f$
 **/
inline const gsl_matrix * sqrt_q2_xx() const
{
	return _sqrt_q2_xx;
}	
	
protected:
/**@fn void tkalman :: sum :: free( );
 * @brief
 * This function frees memory.
 */
void free();

/**@fn void tkalman :: sum :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

/**@fn void tkalman :: sum :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();

//Paramètres
unsigned int _size_x;
unsigned int _size_y;
unsigned int _size_t;
const gsl_matrix * _f2_xt;
gsl_matrix _f2_xx;
gsl_matrix _f2_xy;
const gsl_matrix * _sqrt_q2_xx;

mutable sum_workspace * w;
};

};




#endif
