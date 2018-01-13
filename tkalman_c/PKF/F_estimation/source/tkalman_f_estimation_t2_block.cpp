#include "tkalman_f_estimation_t2_block.hpp"
#include "tkalman_f_estimation_t2_block_estimator.hpp"
//Function
namespace tkalman
{
namespace f_estimation
{
namespace t2_block
{

//Functions
void * parameters_allocation_function ( const void * data )
{
	const parameters_size * p = (const parameters_size *) data;
	return (void*) new parameters( 	p->size_i, 
									p->size_t, 
									p->size_lambda );
}

int  parameters_setting_function(	void *object,
									const void * params )
{
	parameters * p = ( parameters * ) object;
	const parameters_data * d = (const parameters_data *) params;
	return (p->set( d->m ));
	
}

void parameters_freeing_function ( void * data )
{
	parameters * p = ( parameters * ) data;
	delete p;
}

void * estimator_allocation_function ( const void * data )
{
	const parameters * p = (const parameters *) data;
	return (void*) new estimator( p );
}

void estimator_freeing_function ( void * data )
{
	estimator * p = (estimator *) data;
	delete p;
}

void f_estimation_function(	gsl_matrix * f_i,
							const gsl_matrix * sqrt_c_i_view_00,
							const gsl_matrix * sqrt_c_i_view_01,
							const void * est,
							const gsl_matrix * sqrt_q_i  )
{
	const estimator * e = (const estimator *) est;
	e->estimate(	f_i, 
					sqrt_c_i_view_00,
					sqrt_c_i_view_01,
					sqrt_q_i );
}



//Def de du "function set"
tkalman :: f_estimation :: function_set
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


