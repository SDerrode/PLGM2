#ifndef _TKALMAN_F_ESTIMATION_t1_block_HPP_
#define _TKALMAN_F_ESTIMATION_t1_block_HPP_
#include "tkalman_f_estimation_typedef.hpp"
namespace tkalman
{
namespace f_estimation
{
namespace t1_block
{

/**@struct tkalman :: f_estimation :: t2_block :: parameters_size
 * @brief
 * Sizes of parameters
 **/
struct parameters_size
{
	unsigned int size_i,
				 size_t,
				 size_g;
};
	
/**@struct tkalman :: f_estimation :: t2_block :: parameters_data
 * @brief
 * Data for parameters setting
 **/
struct parameters_data
{
	const gsl_matrix * m;
};
	
	
	
/**@fn const function_set * tkalman :: f_estimation :: t2_block :: get_function_set();
 * @return 
 * Associated function set.
 **/
function_set * get_function_set();
};
};
};


#endif
