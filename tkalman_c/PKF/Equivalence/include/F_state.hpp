#ifndef _F_STATE_HPP_
#define _F_STATE_HPP_
#include "F_state_workspace.hpp"
namespace equivalence
{

/**@class
 * @brief
 * 
 * 
 **/
class f_state
{
public:
	/**@fn
	 * @brief
	 * Default constructor
	 * 
	 **/
	f_state( void );
	
	/**@fn
	 * @param[in] f_xx : \f$ \Fxx \f$
	 * @param[in] f_xy : \f$ \Fxy \f$
	 * @brief
	 * Constructor
	 * 
	 **/
	f_state( 	const gsl_matrix * f_xx, 
				const gsl_matrix * f_xy );
				
	/**@fn
	 * @brief
	 * Reset
	 * 
	 **/
	void reset();
			
	/**@fn
	 * @param[in] f_xx : \f$ \Fxx \f$
	 * @param[in] f_xy : \f$ \Fxy \f$
	 * @brief
	 * Setup
	 * 
	 **/
	int setup( 	const gsl_matrix * f_xx, 
				const gsl_matrix * f_xy );
				
					
	/**@fn
	 * @brief
	 * Destructor
	 **/			
	~f_state();
	
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
	 * @return \f$ \Fyx \f$
	 * 
	 **/
	const gsl_matrix * f_xx() const
	{
		return _f_xx;
	}
	
	/**@fn
	 * @return \f$ \Fyy \f$
	 * 
	 **/
	const gsl_matrix * f_xy() const
	{
		return _f_xy;
	}
	
	/**@fn
	 * @param[out] m : \f$ \mat{}{} \f$
	 * @param[in] f : \f$ \F{} \f$
	 * 
	 **/
	int compute_m ( 	gsl_matrix * m,
						const gsl_matrix * f ) const;
	
	
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
	
	const gsl_matrix * _f_xx,
					 * _f_xy;
					 
	unsigned int _size_x,
				 _size_y,
				 _size_t;
				 
	mutable f_state_workspace * w;	 
	
};
	
	
	
};


#endif
