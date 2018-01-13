#ifndef _TKALMAN_Q_ESTIMATION_T2_BLOCK_HPP_
#define _TKALMAN_Q_ESTIMATION_T2_BLOCK_HPP_
#include "tkalman_q_estimation_typedef.hpp"

namespace tkalman
{
namespace q_estimation
{
namespace t2_block
{
/**@fn const function_set * tkalman :: f_estimation :: tensorial_constraints :: get_function_set();
 * @return 
 * Associated function set.
 **/
function_set * get_function_set();


/**@struct tkalman :: f_estimation :: t2_block :: parameters_size
 * @brief
 * Sizes of parameters
 **/
struct parameters_size
{
	unsigned int size_i,
				 size_t;
};




};
};
};



#endif
