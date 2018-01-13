#ifndef _TKALMAN_FILTER_WORKSPACE_HPP_
#define _TKALMAN_FILTER_WORKSPACE_HPP_
#include "tkalman_workspace.hpp"
namespace tkalman
{
/**@class tkalman :: filter_workspace
 * @brief
 * PK filter workspace
 * 
 **/
class filter_workspace : public workspace
{
public:
	/**@fn tkalman :: filter_workspace :: filter_workspace ( unsigned int size_x, unsigned int size_y )
	 * @param size_x : size of x 
	 * @param size_y : size of y
	 * @brief
	 * Constructor
	 **/
	filter_workspace ( 	unsigned int size_x, 
						unsigned int size_y ) throw (exception &);

	/**@fn tkalman :: filter_workspace :: ~filter_workspace()
	 * @brief
	 * Destructor
	 **/
	~filter_workspace();
	
	/**@fn gsl_matrix * tkalman :: filter_workspace :: f2_xt()
	 * @return
	 * $F_2^{x,t}$
	 **/
	inline gsl_matrix * f2_xt()
	{
		return _f2_xt;
	}
	
	/**@fn gsl_matrix * tkalman :: filter_workspace :: sqrt_q2_xx()
	 * @return
	 * $[Q_2^{x,x}]^{\frac{1}{2}}$
	 **/
	inline gsl_matrix * sqrt_q2_xx()
	{
		return _sqrt_q2_xx;
	}
	/**@fn gsl_matrix * tkalman :: filter_workspace :: q2_xy()
	 * @return
	 * $Q_2^{x,y}$
	 **/
	inline gsl_matrix * q2_xy()
	{
		return _q2_xy;
	}
	
	/**@fn gsl_matrix * tkalman :: filter_workspace :: sqrt_q_yy()
	 * @return
	 * $[Q^{y,y}]^{\frac{1}{2}}$
	 **/
	inline gsl_matrix * sqrt_q_yy()
	{
		return _sqrt_q_yy;
	}
	
	/**@fn gsl_vector * tkalman :: filter_workspace :: vect_y()
	 * @return
	 **/
	inline gsl_vector * vect_y()
	{
		return _vect_y;
	}
	
protected:
	/**@fn void tkalman :: filter_workspace ::  free();
	 * @brief
	 * This function frees memory.
	 */
	void free();
	/**@fn void tkalman :: filter_workspace ::  initialize();
	 * @brief
	 * This function sets object attributes to 0.
	 */
	void initialize();
	/**@fn void tkalman :: filter_workspace ::  alloc();
	 * @brief
	 * This function allocates attributes.
	 */
	void alloc();	
	
	
	
	gsl_matrix 	*_f2_xt,
				*_sqrt_q2_xx,
				*_q2_xy,
				*_sqrt_q_yy;
				
	gsl_vector 	*_vect_y;
				
				
	
};
	
};


#endif
