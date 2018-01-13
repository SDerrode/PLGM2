#ifndef _TKALMAN_Q_ESTIMATION_T2_BLOCK_PARAMETERS_HPP_
#define _TKALMAN_Q_ESTIMATION_T2_BLOCK_PARAMETERS_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
namespace q_estimation
{
namespace t2_block
{
/**@class tkalman :: f_estimation :: t1_block :: parameters
 * @brief
 * Parameters for partial estimation of F.
 * 
 **/
class parameters
{
public:
	/**@fn tkalman :: f_estimation :: t1_block :: parameters :: parameters( 	unsigned int size_i, 
																				unsigned int size_t ) throw ( exception &);
	 * @param[in] size_i : \f$n_i\f$
	 * @param[in] size_t : \f$n_t\f$
	 * @brief
	 * Constructor
	 **/
	parameters( 	unsigned int size_i, 
					unsigned int size_t ) throw ( exception &);

	/**@fn int tkalman :: f_estimation :: t1_block :: parameters :: set( const gsl_matrix * m );
	 * @param[in] m : \f$ M_i \f$
	 * @brief
	 * Set parameters
	 * @return 
	 * - 1 if m == NULL <=> ? or rk(m) < size_g <=> :(
	 * - 0 <=> :) 
	 **/
	int set( const gsl_matrix * m );

	/**@fn tkalman :: f_estimation :: t1_block :: parameters :: ~parameters();
	 * @brief
	 * Destructor
	 * 
	 **/
	~parameters();
	
	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_t() const
	 * @brief
	 * \f$n_t\f$
	 * 
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}

	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_i() const
	 * @brief
	 * \f$n_i\f$
	 * 
	 **/
	inline unsigned int size_i() const
	{
		return _size_i;
	}
	



	/**@fn inline const gsl_matrix * tkalman :: f_estimation :: t2_block :: parameters :: sqrt_q() const
	 * @brief
	 * \f$ Q^{\frac{1}{2}} \f$
	 * 
	 **/
	inline const gsl_matrix * sqrt_q() const
	{
		return _sqrt_q;
	}
	
	/**@fn inline const gsl_matrix * tkalman :: f_estimation :: t2_block :: parameters :: inv_sqrt_q() const
	 * @brief
	 * \f$ Q^{\frac{1}{2}} \f$
	 * 
	 **/
	inline const gsl_matrix * inv_sqrt_q() const
	{
		return _inv_sqrt_q;
	}
	
	
	
protected:
	/**@fn void tkalman :: f_estimation :: t1_block :: free();
	 * @brief
	 * Free memory
	 **/
	void free();

	/**@fn void tkalman :: f_estimation :: t1_block :: initialize();
	 * @brief
	 * Set object attributes to 0.
	 **/
	void initialize();

	unsigned int 	_size_i,
					_size_t;
	gsl_matrix * _sqrt_q;
	gsl_matrix * _inv_sqrt_q;

};
};
};
};


#endif
