#include "tkalman_f_estimation_t1_block_parameters.hpp"
#include "gsl_matrix_rank.hpp"
tkalman :: f_estimation :: t1_block :: parameters :: parameters( 	unsigned int size_i, 
																	unsigned int size_t,
																	unsigned int size_g ) throw ( exception &)
: tkalman :: f_estimation :: parameters( size_i, size_t )
{
	tkalman :: f_estimation :: t1_block :: parameters :: initialize();
	_size_g = size_g;
	if ( _size_g > 0 )
		parameters :: alloc();
}

int tkalman :: f_estimation :: t1_block :: parameters :: set( const gsl_matrix * m )
{
	if ( _size_g == 0 )
		return 0;
	
	if ( ! m )
		return 565487;
		
	if ( m->size1 != _size_g )
		return 54525;
		
	if ( m->size2 != _size_t )
		return -98788787;
	
	//Rank of m
	if ( gsl_matrix_rank( m) != _size_g )
		return 1;
	gsl_matrix_memcpy( _m, m );
		
	return 0;
}

tkalman :: f_estimation :: t1_block :: parameters :: ~parameters()
{
	parameters :: free();
	parameters :: initialize();
}

void tkalman :: f_estimation :: t1_block :: parameters :: free()
{
	if ( _m )
	{
		gsl_matrix_free( _m );
	}
}

void tkalman :: f_estimation :: t1_block :: parameters :: initialize()
{
	_m = 0;
	_size_g = 0;
}


void tkalman :: f_estimation :: t1_block :: parameters :: alloc()
{
	_m = gsl_matrix_alloc( _size_g, _size_t );
}
