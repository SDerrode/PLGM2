#ifndef _TKALMAN_F_ESTIMATION_PARAMATERS_HPP_
#define _TKALMAN_F_ESTIMATION_PARAMATERS_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
namespace f_estimation
{
/**@class
 * @brief
 * Parameters for F estimation.
 * 
 **/
class parameters
{
public:
	/**@fn parameters :: parameters ( 	unsigned int size_i, 
										unsigned int size_t );
	 * @param size_i : \f$ n_i \f$
	 * @param size_t : \f$ n_t \f$
	 **/
	parameters ( 	unsigned int size_i, 
					unsigned int size_t ) throw (exception &);

	/**@fn
	 * @brief
	 * Destructor.
	 * 
	 **/
	~parameters();

	/**@fn 
	 * @brief
	 * \f$n_i\f$
	 * 
	 **/
	inline unsigned int size_i() const
	{
		return _size_i;
	}

	/**@fn 
	 * @brief
	 * \f$n_t\f$
	 * 
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}


protected:
	/**@fn
	 * @brief
	 * Set object. attributes to 0.
	 * 
	 **/
	void initialize();

	unsigned int _size_i,
				 _size_t;
	
};

	
};
};
#endif
