#include "tkalman_q_estimation_t2_block.hpp"
#include "tkalman_q_estimation_t2_block_estimator.hpp"
#include "tkalman_q_estimation_t2_block_parameters.hpp"
namespace tkalman
{
namespace q_estimation
{
namespace t2_block
{
void * parameters_allocation_function ( const void * data )
{
	const parameters_size * size = (const parameters_size*) data;
	return (void*) new parameters( size->size_i, size->size_t );
}

void parameters_freeing_function ( void * data )
{
	delete ( parameters*) data;
}

int parameters_setting_function (	void *object,
									const void * params )
{
	if ( !params )
		return -1;
	return ( (parameters *) object )->set( (const gsl_matrix*) params );
}

void * estimator_allocation_function ( const void * data )
{
	estimator * est = new estimator( 	(const parameters *) data );
	return (void*) est;
}

void estimator_freeing_function ( void * data )
{
	delete (estimator*) data;
}

void f_estimation_function (	gsl_matrix * sqrt_q_i,
								const gsl_matrix * f_i,
								const gsl_matrix * sqrt_c_i,
								unsigned int nb_observations,
								const void * e )
{
	const estimator * est = (const estimator *) e;
	est->estimate(	sqrt_q_i, 
					f_i, 
					sqrt_c_i, 
					nb_observations );
}

function_set
	f_set(	estimator_allocation_function,
			f_estimation_function,
			estimator_freeing_function,
			parameters_allocation_function,
			parameters_setting_function,
			parameters_freeing_function );


/**@fn const function_set * tkalman :: f_estimation :: tensorial_constraints :: get_function_set();
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
