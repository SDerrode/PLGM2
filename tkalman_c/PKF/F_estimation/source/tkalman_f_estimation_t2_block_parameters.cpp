#include "tkalman_f_estimation_t2_block_parameters.hpp"
#include "gsl_matrix_rank.hpp"
#include <gsl/gsl_linalg.h>

tkalman :: f_estimation :: t2_block :: parameters :: parameters( 	unsigned int size_i, 
																	unsigned int size_t,
																	unsigned int size_lambda) throw (exception &)
: tkalman :: f_estimation :: parameters( size_i, size_t )
{
	tkalman :: f_estimation :: t2_block :: parameters :: initialize();
	if ( size_lambda == 0 )
		_size_lambda = 0;
	else
	{
		_size_i = size_i;
		_size_t = size_t;
		_size_lambda = size_lambda;
		tkalman :: f_estimation :: t2_block :: parameters :: alloc();
	}
	
}

int tkalman :: f_estimation :: t2_block :: parameters :: set(	const gsl_matrix * const * m )
{
	if ( _size_lambda == 0 )
		return 0;
	else
	{
		if ( !m )
			return 1;
		//Dimensions
		for ( unsigned int i = 0; i < _size_lambda; ++ i )
		{
			if ( 	_size_i != m[i]->size1 ||
					_size_t != m[i]->size2 )
				return 1;
		}
		//Indépendance des M
		{
			unsigned int n = _size_i * _size_t;
			if ( _size_lambda > n )
				return 4;
			gsl_matrix * tmp = gsl_matrix_alloc(	n,
													_size_lambda );
			for ( unsigned int i = 0; i < _size_lambda; ++ i )
			{
				for ( unsigned int j = 0; j < _size_i; ++ j )
				{
					for ( unsigned int k = 0; k < _size_t; ++ k )
					{
						tmp->data[(j * _size_t + k ) * tmp->tda + i] = m[i]->data[j * m[i]->tda + k];
					}
				}
			}
			
			unsigned int rk = gsl_matrix_rank( tmp );
			gsl_matrix_free( tmp );
			
			if ( rk != _size_lambda )
				return 5;
			
		}
		
		//Recopie des M(i)
		for ( unsigned int i = 0; i < _size_lambda; ++ i )
		{
			gsl_matrix_memcpy( _m[i], m[i] );
			
		}
		
		
	}
	return 0;
}


tkalman :: f_estimation :: t2_block :: parameters :: ~parameters()
{
	tkalman :: f_estimation :: t2_block :: parameters :: free();
	tkalman :: f_estimation :: t2_block :: parameters :: initialize();
}

void tkalman :: f_estimation :: t2_block :: parameters :: free()
{
	if ( _m )
	{
		for ( unsigned int i = 0; i < _size_lambda; ++ i )
		{
			if ( _m[i] )
				gsl_matrix_free( _m[i] );
		}
		delete[] _m;
	}
}

void tkalman :: f_estimation :: t2_block :: parameters :: alloc()
{
	_m = new gsl_matrix*[_size_lambda];
	for ( unsigned int i = 0; i < _size_lambda; ++ i )
	{
		_m[i] = gsl_matrix_alloc( _size_i, _size_t );
	}
}

void tkalman :: f_estimation :: t2_block :: parameters :: initialize()
{
	_size_lambda = 0;
	_m = 0;
}
