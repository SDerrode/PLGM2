#ifndef _TKALMAN_F_ESTIMATION_t2_block_PARAMETERS_HPP_
#define _TKALMAN_F_ESTIMATION_t2_block_PARAMETERS_HPP_
#include "tkalman_f_estimation_parameters.hpp"
namespace tkalman
{
namespace f_estimation
{
namespace t2_block
{

	
/**@class tkalman :: f_estimation :: t2_block :: parameters
 * @brief
 * tensioral constraints parameters for F estimation.
 * 
 **/
class parameters : public tkalman :: f_estimation :: parameters
{
public:
	/**@fn tkalman :: f_estimation :: t2_block :: parameters :: parameters( 	unsigned int size_i, 
																							unsigned int size_t
																							unsigned int size_lambda ) throw ( exception &);
	 * @param[in] size_i : \f$n_i\f$
	 * @param[in] size_t : \f$n_t\f$
	 * @param[in] size_lambda : \f$n^{\lambda}_i\f$
	 * @brief
	 * Constructor
	 **/
	parameters( 	unsigned int size_i, 
					unsigned int size_t,
					unsigned int size_lambda ) throw ( exception &);
	/** int tkalman :: f_estimation :: t2_block :: parameters :: set(	const gsl_matrix * const *m );
	 * @param[in] m : \f$M_i^j\f$
	 **/
	int set(	const gsl_matrix * const *m );

	/**@fn tkalman :: f_estimation :: t2_block :: parameters :: ~parameters();
	 * @brief
	 * Destructor
	 * 
	 **/
	~parameters();
	
	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_lambda() const
	 * @brief
	 * \f$n^{\lambda}_i\f$
	 * 
	 **/
	inline unsigned int size_lambda() const
	{
		return _size_lambda;
	}

	/**@fn inline const gsl_matrix * const * tkalman :: f_estimation :: t2_block :: parameters :: m() const
	 * @brief
	 * \f$ M_i^j\f$
	 * 
	 **/
	inline const gsl_matrix * const * m() const
	{
		return _m;
	}

	
protected:
	/**@fn void tkalman :: f_estimation :: t2_block :: parameters :: free();
	 * @brief
	 * Free memory
	 **/
	void free();

	/**@fn void tkalman :: f_estimation :: t2_block :: parameters :: alloc();
	 * @brief
	 * memory allocation
	 **/
	void alloc();

	/**@fn void tkalman :: f_estimation :: t2_block :: parameters :: initialize();
	 * @brief
	 * Set object attributes to 0.
	 **/
	void initialize();


	unsigned int _size_lambda;
	gsl_matrix **_m;
};
};
	
	
};
};


#endif
