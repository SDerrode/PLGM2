#ifndef _TKALMAN_CONSTANTS_HPP_
#define _TKALMAN_CONSTANTS_HPP_
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h> 
#include "tkalman_constants_workspace.hpp"
namespace tkalman
{

/**@fn void tkalman::compute_f2_xt(	gsl_matrix * f2_x_,
									const gsl_matrix * f_x_,
									const gsl_matrix * f_y_,
									const gsl_matrix * q2_xy)
 * @param[out] f2_x_ : \f$ F_2^{x,z} \f$, \f$ F^{x,z} - Q^{x,y} [Q^{y,y}]^{-1} F^{y,z} \f$, with z = x or y.
 * @param[in] f_x_ : \f$ F^{x,z} \f$, submatrix of transition matrix.
 * @param[in] f_y_ : \f$ F^{y,z} \f$, submatrix of transition matrix.
 * @param[in] q2_xy : \f$ Q_2^{x,y}\f$, \f$ Q^{x,y} [Q^{y,y}]^{-\frac{1}{2}} \f$
 * @brief
 * This function computes \f$ F_2^{x,z} \f$ by the formula:
 * \f$ Q_2^{x,y}\f$, \f$ Q^{x,y} [Q^{y,y}]^{-\frac{1}{2}} \f$
*/
void compute_f2_xt(	gsl_matrix * f2_x_,
					const gsl_matrix * f_x_,
					const gsl_matrix * f_y_,
					const gsl_matrix * q2_xy );
							
/**@fn void tkalman::compute_sqrt_constants(	gsl_matrix * sqrt_q2_xx,
																	gsl_matrix * q2_xy,
																	gsl_matrix * sqrt_q_yy,
																	const gsl_matrix * sqrt_q_view_xx,
																	const gsl_matrix * sqrt_q_view_xy,
																	const gsl_matrix * sqrt_q_view_yy,
																	constants_workspace * w )
 * @param[out] sqrt_q2_xx : 
 \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[out] q2_xy : 
 \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-\frac{1}{2}} \f$
 * @param[out] sqrt_q_yy : \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
 * @param[in] sqrt_q_view_xx : 
 \f$ [Q^{\frac{1}{2}}]^{x,x} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_x -1, n_x-1) \f$
 * @param[in] sqrt_q_view_xy : 
 \f$ [Q^{\frac{1}{2}}]^{x,y} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,n_x) \f$, ending at \f$ (n_t -1, n_x-1) \f$
 * @param[in] sqrt_q_view_yy :  
 \f$ [Q^{\frac{1}{2}}]^{y,y}\f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (n_x,n_x) \f$, ending at \f$ (n_t -1, n_t -1) \f$
 * @param w : allocated workspace
 * @brief
 This function computes:
 - \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$
 - \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-\frac{1}{2}} \f$
 - \f$ [Q^{y,y}]^{\frac{1}{2}}\f$
 - A. First, it builds the matrix :
  \f$ 
  M=
	 \begin{pmatrix}
		[Q^{\frac{1}{2}}]^{y,y}	&	0 \\
		[Q^{\frac{1}{2}}]^{x,y} & 	[Q^{\frac{1}{2}}]^{x,x}
	\end{pmatrix}
 \f$
 - B. Its effectuates the QR decompostion of the previous matrix which gives:
 \f$ 
 \begin{pmatrix}
	[Q^{y,y}]^{\frac{1}{2}}	&	[Q_2^{x,y}]'			\\
	0						& 	[Q_2^{x,x}]^{\frac{1}{2}}	 
 \end{pmatrix}
\f$ 
	**/
void compute_sqrt_constants(	gsl_matrix * sqrt_q2_xx,
								gsl_matrix * q2_xy,
								gsl_matrix * sqrt_q_yy,
								const gsl_matrix * sqrt_q_view_xx,
								const gsl_matrix * sqrt_q_view_xy,
								const gsl_matrix * sqrt_q_view_yy,
								constants_workspace * w );


/**@fn void tkalman:: compute_constants(	gsl_matrix * f2_xt,
											gsl_matrix * sqrt_q2_xx,
											gsl_matrix * q2_xy,
											gsl_matrix * sqrt_q_yy,
											const gsl_matrix * f_xt,
											const gsl_matrix * f_yt,
											const gsl_matrix * sqrt_q_view_xx,
											const gsl_matrix * sqrt_q_view_xy,
											const gsl_matrix * sqrt_q_view_yy,
											constants_workspace * w )
 * @param[out] f2_xt : \f$ F_2^{x,t} \f$, \f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[out] sqrt_q2_xx : \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, square root of the reduced noise covariance.
 * @param[out] q2_xy : \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-\frac{1}{2}} \f$
 * @param[out] sqrt_q_yy : \f$ [Q^{y,y}]^{\frac{1}{2}}\f$, square root of measurement covariance matrix.
 * @param[in] f_xt : \f$ F^{x,t} \f$, submatrix of transition matrix.
 * @param[in] f_yt : \f$ F^{y,t} \f$, submatrix of transition matrix.
 * @param[in] sqrt_q_view_xx : \f$ [Q^{\frac{1}{2}}]^{x,x} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_x -1, n_x-1) \f$
 * @param[in] sqrt_q_view_xy : \f$ [Q^{\frac{1}{2}}]^{x,y} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,n_x) \f$, ending at \f$ (n_t -1, n_x-1) \f$
 * @param[in] sqrt_q_view_yy :  \f$ [Q^{\frac{1}{2}}]^{y,y}\f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (n_x,n_x) \f$, ending at \f$ (n_t -1, n_t -1) \f$
 * @param w : allocated workspace
 * @brief
 * This function computes Pairwise Kalman constants.
 * - \f$ F^{x,t} - Q^{t,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * - \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$
 * - \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-\frac{1}{2}} \f$
 * - \f$ [Q^{y,y}]^{\frac{1}{2}}\f$
 * 
**/
void compute_constants(	gsl_matrix * f2_x_,
						gsl_matrix * sqrt_q2_xx,
						gsl_matrix * q2_xy,
						gsl_matrix * sqrt_q_yy,
						const gsl_matrix * f_x_,
						const gsl_matrix * f_y_,
						const gsl_matrix * sqrt_q_view_xx,
						const gsl_matrix * sqrt_q_view_xy,
						const gsl_matrix * sqrt_q_view_yy,
						constants_workspace * w );

	
/**@class tkalman::constants
 * @brief
 * Class for the constant computing in Pairwise Kalman filter.
 * 
 **/
class constants
{
public:

/**@fn tkalman :: constants :: constants()
 * @brief
 * - Default constructor
 * - Sets object attributes to 0.
 * 
 */
constants( );


/**@fn tkalman :: constants :: constants(	const gsl_matrix * f_xt,
											const gsl_matrix * f_yt,
											const gsl_matrix * sqrt_q_xx,
											const gsl_matrix * sqrt_q_xy,
											const gsl_matrix * sqrt_q_yy)
 * @param[in] f_xt : \f$ F^{x,t} \f$, submatrix of transition matrix.
 * @param[in] f_yt : \f$ F^{y,t} \f$, submatrix of transition matrix.
 * @param[in] sqrt_q_xx : 
 \f$ [Q^{\frac{1}{2}}]^{x,x} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_x -1, n_x-1) \f$
 * @param[in] sqrt_q_xy : 
 \f$ [Q^{\frac{1}{2}}]^{x,y} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,n_x) \f$, ending at \f$ (n_t -1, n_x-1) \f$
 * @param[in] sqrt_q_yy :  
 \f$ [Q^{\frac{1}{2}}]^{y,y}\f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (n_x,n_x) \f$, ending at \f$ (n_t -1, n_t -1) \f$
 * @brief
 * Constructor
 * @exception
 * - unvalid parameters 
 */
constants(	const gsl_matrix * f_xt,
			const gsl_matrix * f_yt,
			const gsl_matrix * sqrt_q_xx,
			const gsl_matrix * sqrt_q_xy,
			const gsl_matrix * sqrt_q_yy) throw (exception &);


/**@fn void tkalman :: constants :: reset()
 * @brief
 * - Reset
 * - frees object memory
 * - sets object attributes to 0.
 * 
 */
virtual void reset ( );


/**@fn int tkalman :: constants :: setup(	const gsl_matrix * f_xt,
											const gsl_matrix * f_yt,
											const gsl_matrix * sqrt_q)
 * @param[in] f_xt : \f$ F^{x,t} \f$, submatrix of transition matrix.
 * @param[in] f_yt : \f$ F^{y,t} \f$, submatrix of transition matrix.
 * @param[in] sqrt_q_xx : 
 \f$ [Q^{\frac{1}{2}}]^{x,x} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_x -1, n_x-1) \f$
 * @param[in] sqrt_q_xy : 
 \f$ [Q^{\frac{1}{2}}]^{x,y} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,n_x) \f$, ending at \f$ (n_t -1, n_x-1) \f$
 * @param[in] sqrt_q_yy :  
 \f$ [Q^{\frac{1}{2}}]^{y,y}\f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (n_x,n_x) \f$, ending at \f$ (n_t -1, n_t -1) \f$
 * @brief
 * Setup
 * @return
 * - 1 -> unvalid parameters 
 * - 0 -> OK
 */
virtual int setup (	const gsl_matrix * f_xt,
					const gsl_matrix * f_yt,
					const gsl_matrix * sqrt_q_xx,
					const gsl_matrix * sqrt_q_xy,
					const gsl_matrix * sqrt_q_yy);

/**@fn tkalman :: constants ::  ~constants()
 * @brief
 * Destructor
 **/
virtual ~constants();
		
//Accessors
/**@fn inline unsigned int tkalman :: constants :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: constants :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: constants :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn inline gsl_matrix tkalman :: constants :: f_xt() const
 * @return
 * \f$ F^{x,t}\f$
 **/
inline const gsl_matrix * f_xt() const
{
	return _f_xt;
}

/**@fn inline gsl_matrix tkalman :: constants :: f_yt() const
 * @return
 * \f$ F^{y,t}\f$
 **/
inline const gsl_matrix * f_yt() const
{
	return _f_yt;
}

/**@fn inline gsl_matrix tkalman :: constants :: sqrt_q_xx() const
 * @return
 \f$ [Q^{\frac{1}{2}}]^{x,x} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_x -1, n_x-1) \f$
 **/
inline const gsl_matrix * sqrt_q_xx() const
{
	return _sqrt_q_xx;
}

/**@fn inline gsl_matrix tkalman :: constants :: sqrt_q_xy() const
 * @return
 \f$ [Q^{\frac{1}{2}}]^{x,y} \f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (0,n_x) \f$, ending at \f$ (n_t -1, n_x-1) \f$
 **/
inline const gsl_matrix * sqrt_q_xy() const
{
	return _sqrt_q_xy;
}

/**@fn inline gsl_matrix tkalman :: constants :: sqrt_q_yy() const
 * @return
 \f$ [Q^{\frac{1}{2}}]^{y,y}\f$, matrix view on \f$[Q]^{\frac{1}{2}}\f$,  starting at \f$ (n_x,n_x) \f$, ending at \f$ (n_t -1, n_t -1) \f$
 **/
inline const gsl_matrix * sqrt_q_yy() const
{
	return _sqrt_q_yy;
}

/**@fn inline void tkalman :: constants :: compute (gsl_matrix * f2_xt,
													   gsl_matrix * sqrt_q2_xx,
													   gsl_matrix * q2_xy,
													   gsl_matrix * sqrt_q_yy)
 * @param[out] f2_xt : 
	\f$ F_2^{x,t} \f$, 
	\f$ F^{x,t} - Q^{x,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * @param[out] sqrt_q2_xx : 
	\f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$, 
	square root of the reduced noise covariance.
 * @param[out] q2_xy : 
	\f$ Q_2^{x,y} \f$, 
	\f$ Q^{x,y} \: [Q^{y,y}]^{-1}} \f$
 * @param[out] sqrt_q_yy : 
	\f$ [Q^{y,y}]^{\frac{1}{2}}\f$, 
	square root of measurement covariance matrix.
 * @brief
 * This function computes Pairwise Kalman constants.
 * - \f$ F^{x,t} - Q^{t,y} \: [Q^{y,y}]^{-1} \: F^{y,t} \f$
 * - \f$ [Q_2^{x,x}]^{\frac{1}{2}}\f$
 * - \f$ Q_2^{x,y} \f$, \f$ Q^{x,y} \: [Q^{y,y}]^{-\frac{1}{2}} \f$
 * - \f$ [Q^{y,y}]^{\frac{1}{2}}\f$
 */
inline void compute (	gsl_matrix * f2_xt,
						gsl_matrix * sqrt_q2_xx,
						gsl_matrix * q2_xy,
						gsl_matrix * sqrt_q_yy) const
{
	compute_constants(	f2_xt,
						sqrt_q2_xx,
						q2_xy,
						sqrt_q_yy,
						_f_xt,
						_f_yt,
						_sqrt_q_xx,
						_sqrt_q_xy,
						_sqrt_q_yy,
						w );
}

protected:
/**@fn void tkalman :: constants :: free();
 * @brief
 * This function frees memory.
 */
void free();

/**@fn void tkalman :: constants :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

/**@fn void tkalman :: constants :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();

//Object data (const)
	unsigned int 	_size_x,
					_size_y,
					_size_t;

	const gsl_matrix * _f_xt,
					 * _f_yt;
					 
	const gsl_matrix 	* _sqrt_q_xx,
						* _sqrt_q_xy,
						* _sqrt_q_yy;

//Workspace data (no-const)
	mutable constants_workspace * w;
}; 

};
#endif
