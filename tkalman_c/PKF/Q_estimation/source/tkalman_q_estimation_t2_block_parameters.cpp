#include "tkalman_q_estimation_t2_block_parameters.hpp"
#include "gsl_matrix_rank.hpp"
#include <gsl/gsl_linalg.h>
using namespace tkalman;
using namespace q_estimation;
using namespace t2_block;

parameters :: parameters 
	( 	unsigned int size_i, 
		unsigned int size_t ) throw ( exception &)
{
	initialize();
	if ( 	size_i > size_t || 
			size_i == 0 	)
		throw ( invalid_argument("Invalid argument in tkalman :: q_estimation :: t2_block :: parameters :: parameters ( unsigned int size_i, unsigned int size_t)") );
	_size_i = size_i;
	_size_t = size_t;
	
	_sqrt_q = gsl_matrix_alloc( 	_size_i,
										_size_i );
	_inv_sqrt_q = gsl_matrix_alloc( 	_size_i,
										_size_i );
		
	
}

int parameters :: set( const gsl_matrix * m )
{
	if ( ! m )
		return -1;
	
	if ( 	m->size1 != _size_i 	||
			m->size2 != _size_i 	)
		return -2;
		
	if ( gsl_matrix_rank( m ) < _size_i )
		return 1;
		
	gsl_matrix_memcpy( _sqrt_q, m );
	{
		int Neo;
		gsl_matrix * mat_tmp = gsl_matrix_alloc( _size_i, _size_i );
		gsl_permutation * perm = gsl_permutation_alloc( _size_i );
		gsl_matrix_memcpy( 	mat_tmp, 
							_sqrt_q);  
							
		gsl_linalg_LU_decomp (	mat_tmp, 
								perm, 
								&Neo );
		gsl_linalg_LU_invert (	mat_tmp, 
								perm, 
								_inv_sqrt_q );
		gsl_matrix_free( mat_tmp );
		gsl_permutation_free( perm );
	}
	
	return 0;
}

parameters :: ~parameters()
{
	free();
	initialize();
}

void parameters :: free()
{
	if ( _sqrt_q )
		gsl_matrix_free( _sqrt_q );
	if ( _inv_sqrt_q )
		gsl_matrix_free( _inv_sqrt_q );
	
}

void parameters :: initialize()
{
	_size_i = 0;
	_size_t = 0;
	_sqrt_q = 0;
	_inv_sqrt_q = 0;
	
}
