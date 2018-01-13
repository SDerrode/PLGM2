#ifndef _TKALMAN_PREDICTION_HPP_
#define _TKALMAN_PREDICTION_HPP_
#include "tkalman_prediction_workspace.hpp"
namespace tkalman
{
/**@fn void tkalman :: compute_x_p(	gsl_vector * x_p,
									const gsl_vector * _x_f,
									const gsl_vector * __y,
									const gsl_vector * _y,
									const gsl_matrix * f2_xx,
									const gsl_matrix * f2_xy,
									const gsl_matrix * q2_xy);
 * @param[out] x_p : 
 \f$ \hat{x}_{n|n - 1} \f$, predicting state expectation
 * @param[in] _x_f : 
 \f$ \hat{x}_{n - 1|n - 1} \f$, previous filtering state expectation
 * @param[in] __y : 
 \f$ y_{n-2} \f$, observation \f$(n-2)\f$
 * @param[in] _y : 
 \f$ y_{n-1} \f$, previous observation
 * @param[in] f2_xx : 
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$
 * @param[in] f2_xy : 
 \f$ F_2^{x,y} \f$, \f$ F^{x,y} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,y} \f$
 * @param[in] q2_xy : 
 \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-1} \f$
 * @brief
 This function computes the predicting state expectation:
 - \f$ \hat{x}_{n|n - 1} = F_2^{x,x} \hat{x}_{n - 1|n - 1} + F_2^{x,y} y_{n-2} + Q_2^{x,y} y_{n-1}  \f$
 */
void compute_x_p(	gsl_vector * x_p,
					const gsl_vector * _x_f,
					const gsl_vector * __y,
					const gsl_vector * _y,
					const gsl_matrix * f2_xx,
					const gsl_matrix * f2_xy,
					const gsl_matrix * q2_xy);

/**@fn void tkalman::compute_sqrt_p_p_1(gsl_matrix * sqrt_p_p_1,
								   const gsl_matrix * sqrt_q_0_f,
								   const gsl_matrix * f2_xt,
								   const gsl_matrix * sqrt_q2_xx,
								   gsl_matrix * mat_xpt_x,
								   gsl_matrix * mat_xpt_x_view_00,
								   gsl_matrix * mat_xpt_x_view_10,
								   gsl_vector * vect_x)
 * @param[out] sqrt_p_p_1 : 
 \f$[P_{1|0}]^{\frac{1}{2}}\f$, square root of predicting state 1 covariance matrix
 * @param[in] sqrt_q_0_f : 
 \f$[Q_{0|0}]^{\frac{1}{2}}\f$, square root of filtering state 0 covariance matrix
 * @param[in] f2_xt : 
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param w : allocated workspace
 * @brief
 This function computes the square root of predicting state 1 covariance:
 - 1. building the matrix
 \f$
 \begin{pmatrix}
	[Q_2^{x,x}]^{\frac{1}{2}} \\
	[Q_{0|0}]^{\frac{1}{2}} [F_2^{x,t}]'
 \end{pmatrix}
 \f$
 - 2. QR decomposition, which can be written:
 \f$
 \begin{pmatrix}
	[P_{1|0}]^{\frac{1}{2}} \\
	0
 \end{pmatrix}
 \f$
 * 
 **/
void compute_sqrt_p_p_1(	gsl_matrix * sqrt_p_p_1,
							const gsl_matrix * sqrt_q_f_0,
							const gsl_matrix * f2_xt,
							const gsl_matrix * sqrt_q2_xx,
							prediction_workspace * w );
							
/**@fn void tkalman::compute_sqrt_p_p(gsl_matrix * sqrt_p_p,
								 const gsl_matrix * _sqrt_p_f,
								 const gsl_matrix * f2_xx,
								 const gsl_matrix * sqrt_q2_xx,
								 gsl_matrix * mat_2xx,
								 gsl_matrix * mat_2xx_view_00,
								 gsl_matrix * mat_2xx_view_10,
								 gsl_vector * vect_x)
 * @param[out] sqrt_p_p : 
 \f$[P_{n|n-1}]^{\frac{1}{2}}\f$, square root of predicting state covariance matrix
 * @param[in] _sqrt_p_f :
 \f$[P_{n-1|n-1}]^{\frac{1}{2}}\f$, square root of previous filtering state covariance matrix
 * @param[in] f2_xx : 
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param w : allocated workspace
 * @brief
 This function computes the square root of predicting state covariance:
 - 1. building the matrix
 \f$
 \begin{pmatrix}
	[Q_2^{x,x}]^{\frac{1}{2}} \\
	[P_{n-1|n-1}]^{\frac{1}{2}} [F_2^{x,x}]'
 \end{pmatrix}
 \f$
 - 2. QR decomposition, which can be written:
 \f$
 \begin{pmatrix}
	[P_{n|n-1}]^{\frac{1}{2}} \\
	0
 \end{pmatrix}
 \f$

 */
void compute_sqrt_p_p(gsl_matrix * sqrt_p_p,
						  const gsl_matrix * _sqrt_p_f,
						  const gsl_matrix * f2_xx,
						  const gsl_matrix * sqrt_q2_xx,
						  prediction_workspace * w );

/**@fn void tkalman :: compute_prediction ( gsl_vector * x_p,
									gsl_matrix * sqrt_p_p,
									const gsl_vector * _x_f,
									const gsl_matrix * _sqrt_p_f,
									const gsl_vector * __y,
									const gsl_vector * _y,
									const gsl_matrix * f2_xx,
									const gsl_matrix * f2_xy,
									const gsl_matrix * sqrt_q2_xx,
									const gsl_matrix * q2_xy,
									gsl_matrix * mat_2xx,
									gsl_matrix * mat_2xx_view_00,
									gsl_matrix * mat_2xx_view_10,
									gsl_vector * vect_x);
 * @param[out] x_p : 
 \f$ \hat{x}_{n|n - 1} \f$, predicting state expectation
 * @param[out] sqrt_p_p : 
 \f$[P_{n|n-1}]^{\frac{1}{2}}\f$, square root of predicting state covariance matrix
 * @param[in] _x_f : 
 \f$ \hat{x}_{n - 1|n - 1} \f$, previous filtering state expectation
 * @param[in] _sqrt_p_f :
 \f$[P_{n-1|n-1}]^{\frac{1}{2}}\f$, square root of previous filtering state covariance matrix
 * @param[in] __y : 
 \f$ y_{n-2} \f$, observation \f$(n-2)\f$
 * @param[in] _y : 
 \f$ y_{n-1} \f$, previous observation
 * @param[in] f2_xx : 
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$
 * @param[in] f2_xy : 
 \f$ F_2^{x,y} \f$, \f$ F^{x,y} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,y} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[in] q2_xy : 
 \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-1} \f$
 * @param w : allocated workspace
 * @brief
 This function performs the prediction step of Pairwise Kalman filter.
 - 1. building the matrix
 \f$
 \begin{pmatrix}
	[Q_2^{x,x}]^{\frac{1}{2}} \\
	[P_{n-1|n-1}]^{\frac{1}{2}} [F_2^{x,x}]'
 \end{pmatrix}
 \f$
 - 2. QR decomposition, which can be written:
 \f$
 \begin{pmatrix}
	[P_{n|n-1}]^{\frac{1}{2}} \\
	0
 \end{pmatrix}
 \f$
 - 3. Computing predicting state expectation
	\f$ \hat{x}_{n|n - 1} = F_2^{x,x} \hat{x}_{n - 1|n - 1} + F_2^{x,y} y_{n-2} + Q_2^{x,y} y_{n-1}  \f$
**/
void compute_prediction ( gsl_vector * x_p,
						  gsl_matrix * sqrt_p_p,
						  const gsl_vector * _x_f,
						  const gsl_matrix * _sqrt_p_f,
						  const gsl_vector * __y,
						  const gsl_vector * _y,
						  const gsl_matrix * f2_xx,
						  const gsl_matrix * f2_xy,
						  const gsl_matrix * sqrt_q2_xx,
						  const gsl_matrix * q2_xy,
						  prediction_workspace * w );

/**@fn void tkalman :: compute_prediction_1 ( gsl_vector * x_p_1,
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
							   gsl_matrix * mat_xpt_x,
							   gsl_matrix * mat_xpt_x_view_00,
							   gsl_matrix * mat_xpt_x_view_10,
							   gsl_vector * vect_x
							  );
 * @param[out] x_p_1 : 
 \f$ \hat{x}_{1|0} \f$, predicting state 1 expectation
 * @param[out] sqrt_p_p_1 : 
 \f$[P_{1|0}]^{\frac{1}{2}}\f$, square root of predicting state 1 covariance matrix
 * @param[in] x_f_0 : 
 \f$ \hat{x}_{0|0} \f$, filtering state 0 expectation
 * @param[in] y_f_m1 : 
 \f$ \hat{y}_{-1|0} \f$, 
 "filtering state" 0 expectation
 * @param[in] sqrt_q_0_f : 
 \f$ [Q_{0|0}]^{\frac{1}{2}} \f$, square root of initial filtering state covariance
 * @param[in] y_0 : 
 \f$y_0\f$, initial observation
 * @param[in] f2_xt : 
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[in] f2_xx : 
 \f$ F_2^{x,x} \f$, \f$ F^{x,x} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,x} \f$
 * @param[in] f2_xy : 
 \f$ F_2^{x,y} \f$, \f$ F^{x,y} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,y} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[in] q2_xy : 
 \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-1} \f$
 * @param w : allocated workspace
 * @brief
 This function performs the first prediction step of Pairwise Kalman filter.
 - 1. building the matrix
 \f$
 \begin{pmatrix}
	[Q_2^{x,x}]^{\frac{1}{2}} \\
	[Q_{0|0}]^{\frac{1}{2}} [F_2^{x,t}]'
 \end{pmatrix}
 \f$
 - 2. QR decomposition, which can be written:
 \f$
 \begin{pmatrix}
	[P_{1|0}]^{\frac{1}{2}} \\
	0
 \end{pmatrix}
 \f$
 - 3. Computing predicting state expectation
	\f$ \hat{x}_{1|0} = F_2^{x,t} \hat{t}_{0|0} + Q_2^{x,y} y_{0}  \f$
 */
void compute_prediction_1 (	gsl_vector * x_p_1,
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
						  );
/**@class tkalman :: prediction
 * @brief
 * PK prediction
 * 
 **/
class prediction
{
public:

/**@fn tkalman :: prediction :: prediction()
 * @brief
 * Default constructor
 * 
 **/
prediction ( );

/**@fn tkalman :: prediction :: prediction( const gsl_matrix * f2_xt,
											const gsl_matrix * sqrt_q2_xx,
											const gsl_matrix * q2_xy ) throw (exception &);
 * @param[in] f2_xt : 
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[in] q2_xy : 
 \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-1} \f$
 * @brief
 * Constructor
 * 
 **/
prediction ( 	const gsl_matrix * f2_xt,
				const gsl_matrix * sqrt_q2_xx,
				const gsl_matrix * q2_xy ) throw (exception &);

/**@fn void tkalman :: prediction :: reset()
 * @brief
 * - Reset
 * - frees object memory
 * - sets object attributes to 0.
 * 
 */
virtual void reset();


/**@fn int tkalman :: prediction :: setup( 	const gsl_matrix * f2_xt,
											const gsl_matrix * sqrt_q2_xx,
											const gsl_matrix * q2_xy );
 * @param[in] f2_xt : 
 \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[in] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[in] q2_xy : 
 \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-1} \f$
 * @brief
 * Setup
 * @return
 * - 1 -> unvalid parameters 
 * - 0 -> OK
 */
virtual int setup (	const gsl_matrix * f2_xt,
					const gsl_matrix * sqrt_q2_xx,
					const gsl_matrix * q2_xy );

//Prediction
/** @fn void  tkalman :: prediction :: compute_1 ( 	gsl_vector * x_p_1,
													gsl_matrix * sqrt_p_p_1,
													const gsl_vector * t_f_0,
													const gsl_matrix * sqrt_q_f_0,
													const gsl_vector * y_0 );
* @param[out] x_p_1 : 
 \f$ \hat{x}_{1|0} \f$, predicting state 1 expectation
 * @param[out] sqrt_p_p_1 : 
 \f$[P_{1|0}]^{\frac{1}{2}}\f$, square root of predicting state 1 covariance matrix
 * @param[in] t_f_0 : 
 \f$ \hat{t}_{0|0} \f$, filtering state 0 expectation
 * @param[in] sqrt_q_0_f : 
 \f$ [Q_{0|0}]^{\frac{1}{2}} \f$, square root of initial filtering state covariance
 * @param[in] y_0 : 
 \f$y_0\f$, initial observation
 **/
void compute_1 ( 	gsl_vector * x_p_1,
					gsl_matrix * sqrt_p_p_1,
					const gsl_vector * t_f_0,
					const gsl_matrix * sqrt_q_f_0,
					const gsl_vector * y_0 ) const;


/** @fn void  tkalman :: prediction :: compute ( 	gsl_vector * x_p,
													gsl_matrix * sqrt_p_p,
													const gsl_vector * _x_f,
													const gsl_matrix * _sqrt_p_f,
													const gsl_vector * __y,
													const gsl_vector * _y)
	 * @param[out] x_p : 
	 \f$ \hat{x}_{n|n - 1} \f$, predicting state expectation
	 * @param[out] sqrt_p_p : 
	 \f$[P_{n|n-1}]^{\frac{1}{2}}\f$, square root of predicting state covariance matrix
	 * @param[in] _x_f : 
	 \f$ \hat{x}_{n - 1|n - 1} \f$, previous filtering state expectation
	 * @param[in] _sqrt_p_f :
	 \f$[P_{n-1|n-1}]^{\frac{1}{2}}\f$, square root of previous filtering state covariance matrix
	 * @param[in] __y : 
	 \f$ y_{n-2} \f$, observation \f$(n-2)\f$
	 * @param[in] _y : 
	 \f$ y_{n-1} \f$, previous observation
	 * @brief
	 This function performs the prediction step of Pairwise Kalman filter.
	 - 1. building the matrix
	 \f$
	 \begin{pmatrix}
		[Q_2^{x,x}]^{\frac{1}{2}} \\
		[P_{n-1|n-1}]^{\frac{1}{2}} [F_2^{x,x}]'
	 \end{pmatrix}
	 \f$
	 - 2. QR decomposition, which can be written:
	 \f$
	 \begin{pmatrix}
		[P_{n|n-1}]^{\frac{1}{2}} \\
		0
	 \end{pmatrix}
	 \f$
	 - 3. Computing predicting state expectation
		\f$ \hat{x}_{n|n - 1} = F_2^{x,x} \hat{x}_{n - 1|n - 1} + F_2^{x,y} y_{n-2} + Q_2^{x,y} y_{n-1}  \f$
 **/
void compute ( 	gsl_vector * x_p,
				gsl_matrix * sqrt_p_p,
				const gsl_vector * _x_f,
				const gsl_matrix * _sqrt_p_f,
				const gsl_vector * __y,
				const gsl_vector * _y) const;

/**@fn tkalman :: prediction :: ~prediction()
 * 
 **/
virtual ~prediction();
//Accesseurs
/**@fn inline unsigned int tkalman :: prediction :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: prediction :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: prediction :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn inline gsl_matrix tkalman :: prediction :: f2_xt() const
 * @return
 * \f$ F_2^{x,t}\f$
 **/
inline const gsl_matrix * f2_xt() const
{
	return _f2_xt;
}

/**@fn inline gsl_matrix tkalman :: prediction :: f2_xx() const
 * @return
 * \f$ F_2^{x,x}\f$
 **/
inline const gsl_matrix * f2_xx() const
{
	return &_f2_xx;
}


/**@fn inline gsl_matrix tkalman :: prediction :: f2_xy() const
 * @return
 * \f$ F_2^{x,y}\f$
 **/
inline const gsl_matrix * f2_xy() const
{
	return &_f2_xy;
}

/**@fn inline gsl_matrix tkalman :: prediction :: sqrt_q2_xx() const
 * @return
 \f$ [Q_2^{x,x}]^{\frac{1}{2}} \f$
 **/
inline const gsl_matrix * sqrt_q2_xx() const
{
	return _sqrt_q2_xx;
}

/**@fn inline gsl_matrix tkalman :: prediction :: q2_xy() const
 * @return
 \f$ [Q_2^{x,y}]\f$
 **/
inline const gsl_matrix * q2_xy() const
{
	return _q2_xy;
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

//Données propres
unsigned int _size_x,
			 _size_y,
			 _size_t;
//Paramètres
const gsl_matrix * _f2_xt;
gsl_matrix _f2_xx;
gsl_matrix _f2_xy;
const gsl_matrix * _sqrt_q2_xx;
const gsl_matrix * _q2_xy;

//Données temporaires
mutable prediction_workspace * w;
};


};
#endif
