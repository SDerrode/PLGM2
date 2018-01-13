#ifndef Q_DECORRELATION_HPP
#define Q_DECORRELATION_HPP
#include "Q_decorrelation_workspace.hpp"

namespace equivalence
{
/**@class Q_decorrelation
 * @brief
 * Class for finding \f$\mat[M]{}{}\f$ as 
 \f$\mat[M]{}{} \Q{} \mat[M]{T}{} = 
	\begin{bmatrix}
		\power{\Q[M]{}}{x,x}	&	\mat[M]{x,x} \mat[\rho]{}{}	\\
		*						&	\Qyy
	\end{bmatrix}
 \f$
 */
class Q_decorrelation
{
	
public:
	/**@fn
	 * @brief
	 * Default constructor
	 * 
	 **/
	Q_decorrelation( void );

	/**@fn
	 * @param[in] sqrt_q_xx : value of \sq{\Qxx}
	 * @param[in] rho : value of \mat[\rho]{}{}
	 **/
	Q_decorrelation( 	const gsl_matrix * sqrt_q_xx,
						const gsl_matrix * rho );

	/**@fn
	 * @brief
	 * Reset
	 * 
	 **/
	void reset();

	/**@fn
	 * @param[in] sqrt_q_xx : value of \Qxx
	 * @param[in] rho : value of \mat[\rho]{}{}
	 * @brief
	 * Setup
	 * 
	 **/
	int setup( 	const gsl_matrix * sqrt_q_xx,
				const gsl_matrix * rho  );

	/**@fn
	 * @param[out] m : \mat{}{}
	 * @param[in] sqrt_q : \Q[\demi]{}
	 * @brief
	 * Find matrix \mat{}{}
	 **/
	void compute_m ( 	gsl_matrix * m,
						const gsl_matrix * sqrt_q_xx,
						const gsl_matrix * q2_xy ) const;
						
						
	/**@fn
	 * @brief
	 * Destructor
	 * 
	 **/
	~Q_decorrelation();
	
	/**@fn
	 * @return
	 * Size of x
	 **/
	inline unsigned int size_x() const
	{
		return _size_x;
	}
	
	/**@fn
	 * @return
	 * Size of y
	 **/
	inline unsigned int size_y() const
	{
		return _size_y;
	}
	
	/**@fn
	 * @return
	 * Size of t
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}

	/**@fn
	 * @return \f$ \mat[\rho]{}{} \f$
	 * 
	 **/
	inline const gsl_matrix * rho() const
	{
		return _rho;
	}
	
	/**@fn
	 * @return \f$ \Qxx \f$
	 * 
	 **/
	inline const gsl_matrix * sqrt_q_xx() const
	{
		return _sqrt_q_xx;
	}

protected:
	/**@fn void tkalman :: EM  :: initialize();
	 * @brief
	 * This function sets object attributes to 0.
	 */
	void initialize();
	/**@fn void tkalman :: EM :: free();
	 * @brief
	 * This function frees memory.
	 */
	void free();
	/**@fn void tkalman :: EM :: alloc();
	 * @brief
	 * This function allocates attributes.
	 */
	void alloc();
	
	const gsl_matrix * _rho,
					 * _sqrt_q_xx;
	unsigned int _size_x,
				 _size_y,
				 _size_t;
	
	//Workspace
	mutable Q_decorrelation_workspace * w;
	
};




	
};




#endif
