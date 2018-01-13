#ifndef _RESTORATION_HPP_
#define _RESTORATION_HPP_
#include "restoration_workspace.hpp"

namespace equivalence
{
/**@class restoration
 * 
 **/
class restoration
{
public:
	/**@fn
	 * @brief
	 * Default constructor
	 * 
	 **/
	restoration( void );
	
	/**@fn
	 * @param[in] f_yx : \f$ \Fyx \f$
	 * @param[in] f_yy : \f$ \Fyy \f$
	 * @brief
	 * Constructor
	 * 
	 **/
	restoration( 	const gsl_matrix * f_yx, 
					const gsl_matrix * f_yy );

	/**@fn
	 * @brief
	 * Reset
	 * 
	 **/
	void reset();
	
	/**@fn
	 * @param[in] f_yx : \f$ \Fyx \f$
	 * @param[in] f_yy : \f$ \Fyy \f$
	 * @brief
	 * Setup
	 * 
	 **/
	int setup( 	const gsl_matrix * f_yx, 
				const gsl_matrix * f_yy );

	/**@fn
	 * @brief
	 * Destructor
	 **/
	~restoration();
	
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
	const gsl_matrix * f_yx() const
	{
		return _f_yx;
	}
	
	/**@fn
	 * @return \f$ \Fyy \f$
	 * 
	 **/
	const gsl_matrix * f_yy() const
	{
		return _f_yy;
	}
	
	/**@fn
	 * @param[out] m : \f$ \mat{}{} \f$
	 * @param[in] f : \f$ \F{} \f$
	 * 
	 **/
	void compute_m ( 	gsl_matrix * m,
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


	const gsl_matrix * _f_yx,
					 * _f_yy;
					 
	unsigned int _size_x,
				 _size_y,
				 _size_t;
				 
	mutable restoration_workspace * w;	 
					 
};
	
};




#endif
