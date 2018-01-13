#include "signal_splitting.hpp"
#include <iostream>
using namespace std;
signal_splitting :: signal_splitting ( 	const gsl_vector * const * t,
										unsigned int nb_observations,
										unsigned int size_x )
{
	initialize();
	setup( t, nb_observations, size_x );
}

int signal_splitting :: setup ( 	const gsl_vector * const * t,
									unsigned int nb_observations,
									unsigned int size_x )
{
	free();
	initialize();
	if ( ! t || ! nb_observations || ! size_x )
		return 1;
		
	_size_t = t[0]->size;
	_size_x = size_x;
	_size_y = _size_t - _size_x;
	_nb_samples = nb_observations;
	
	if ( _size_x >= _size_t )
	{
		initialize();
		return 1;
	}
	
	for ( unsigned int i = 0; i <= _nb_samples; ++ i )
	{
		if ( t[i]->size != _size_t )
		{
			initialize();
			return 1;
		}
	}
	
	_x_data = new gsl_vector[_nb_samples + 1 ];
	_x = new gsl_vector*[_nb_samples + 1 ];
	
	_y_data = new gsl_vector[_nb_samples ];
	_y = new gsl_vector*[_nb_samples ];
	
	for ( unsigned int i = 0; i <= _nb_samples; ++ i )
	{

		gsl_vector_const_view v = 
			gsl_vector_const_subvector ( 	t[i],
											0,
											_size_x );
											
		_x_data[i] = v.vector;
		_x[i] = _x_data + i;
	}
	for ( unsigned int i = 0; i < _nb_samples; ++ i )
	{
		gsl_vector_const_view v = 
			gsl_vector_const_subvector ( 	t[i + 1],
											_size_x,
											_size_y );
		_y_data[i] = v.vector;
		_y[i] = _y_data + i;
		
		
	}
		
	return 0;
}
signal_splitting :: ~signal_splitting()
{
	free();
	initialize();
}

void signal_splitting :: initialize()
{
	_x_data = 0;
	_x = 0;
	_y_data = 0;
	_y = 0;
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_nb_samples = 0;
}

void signal_splitting :: free()
{
	if ( _x_data )
		delete[] _x_data;
	if ( _y_data )
		delete[] _y_data;
	if ( _x )
		delete[] _x;
	if ( _y )
		delete[] _y;
}


