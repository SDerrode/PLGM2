#ifndef _TKALMAN_F_ESTIMATION_t1_block_PARAMETERS_HPP_
#define _TKALMAN_F_ESTIMATION_t1_block_PARAMETERS_HPP_
#include "tkalman_f_estimation_parameters.hpp"
namespace tkalman
{
namespace f_estimation
{
namespace t1_block
{
/**@class tkalman :: f_estimation :: t1_block :: parameters
 * @brief
 * Parameters for partial estimation of F.
 * 
 **/
class parameters : public tkalman :: f_estimation :: parameters
{
public:
	/**@fn tkalman :: f_estimation :: t1_block :: parameters :: parameters( 	unsigned int size_i, 
																						unsigned int size_t
																						unsigned int size_g ) throw ( exception &);
	 * @param[in] size_i : \f$n_i\f$
	 * @param[in] size_t : \f$n_t\f$
	 * @param[in] size_g : \f$n^{G}_i\f$
	 * @brief
	 * Constructor
	 **/
	parameters( 	unsigned int size_i, 
					unsigned int size_t,
					unsigned int size_g ) throw ( exception &);

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
	
	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_g() const
	 * @brief
	 * \f$n^{G}_i\f$
	 * 
	 **/
	inline unsigned int size_g() const
	{
		return _size_g;
	}
	
	/**@fn inline const gsl_matrix * tkalman :: f_estimation :: t2_block :: parameters :: m() const
	 * @brief
	 * \f$ M_i \f$
	 * 
	 **/
	inline const gsl_matrix * m() const
	{
		return _m;
	}
	
protected:
	/**@fn void tkalman :: f_estimation :: t1_block :: free();
	 * @brief
	 * Free memory
	 **/
	void free();

	/**@fn void tkalman :: f_estimation :: t1_block :: alloc();
	 * @brief
	 * memory allocation
	 **/
	void alloc();

	/**@fn void tkalman :: f_estimation :: t1_block :: initialize();
	 * @brief
	 * Set object attributes to 0.
	 **/
	void initialize();

	unsigned int _size_g;
	gsl_matrix * _m;


};
};
};
};


#endif
