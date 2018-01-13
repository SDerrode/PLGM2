#include "tkalman_f_estimation_known_block.hpp"
namespace tkalman
{
namespace f_estimation
{
namespace known_block
{
//Functions
void * parameters_allocation_function ( const void * data )
{
	return NULL;
}

int  parameters_setting_function(	void *object,
									const void * params )
{
	return 0;
}

void parameters_freeing_function ( void * data )
{
}

void * estimator_allocation_function ( const void * data )
{
	return NULL;
}

void estimator_freeing_function ( void * data )
{
}

void f_estimation_function(	gsl_matrix * f_i,
							const gsl_matrix * sqrt_c_i_view_00,
							const gsl_matrix * sqrt_c_i_view_01,
							const void * est,
							const gsl_matrix * sqrt_q_i )
{
	gsl_matrix_set_zero( f_i );
}



//Def de du "function set"
function_set
	f_set(	estimator_allocation_function,
			f_estimation_function,
			estimator_freeing_function,
			parameters_allocation_function,
			parameters_setting_function,
			parameters_freeing_function );


/**@fn const function_set * tkalman :: f_estimation :: t2_block :: get_function_set();
 * @return 
 * Associated function set.
 **/
function_set * get_function_set()
{
	return (&f_set);
}

};
};
};
