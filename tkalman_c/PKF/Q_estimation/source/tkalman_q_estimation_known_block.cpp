#include "tkalman_q_estimation_known_block.hpp"
#include "gsl_matrix_rank.hpp"
namespace tkalman
{
namespace q_estimation
{
namespace known_block
{
void * parameters_allocation_function ( const void * data )
{
	unsigned int size = * ( (unsigned int*) data );
	return (void*) gsl_matrix_calloc( size, size );
}

void parameters_freeing_function ( void * data )
{
	if ( data )
		gsl_matrix_free ( (gsl_matrix *) data );
}

int parameters_setting_function (	void *object,
									const void * params )
{
	if (	params == NULL	|| object == NULL )
		return -1;
	
	if ( 	( (gsl_matrix*) object)->size1 != ( (const gsl_matrix *) params)->size1	||
			( (gsl_matrix*) object)->size1 != ( (const gsl_matrix *) params)->size2	||
			( (gsl_matrix*) object)->size1 != ( (gsl_matrix*) object)->size2		)
		return -2;
	if( gsl_matrix_rank( (const gsl_matrix *) params ) != ( (gsl_matrix*) object)->size1 )
		return 1;
	
	
	gsl_matrix_memcpy(	(gsl_matrix*) object, 
						(const gsl_matrix *) params );
	return 0;
}

void * estimator_allocation_function ( const void * data )
{
	gsl_matrix * est = gsl_matrix_alloc(	 ( (const gsl_matrix *) data )->size1,
											( (const gsl_matrix *) data )->size2 );
	
	gsl_matrix_memcpy(	est, 
						(const gsl_matrix *) data);
	
	return (void*) est;
	
}

void estimator_freeing_function ( void * data )
{
	gsl_matrix_free( (gsl_matrix *) data );
}

void f_estimation_function (	gsl_matrix * sqrt_q_i,
								const gsl_matrix * f_i,
								const gsl_matrix * sqrt_c_i,
								unsigned int nb_observations,
								const void * estimator )
{
	gsl_matrix_memcpy(	sqrt_q_i, 
						(const gsl_matrix *) estimator );
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
