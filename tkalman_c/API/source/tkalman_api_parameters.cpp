#include "tkalman_api_parameters.hpp"
using namespace tkalman;
using namespace api;

parameters :: parameters( void )
{
	initialize();
}
int parameters :: setup ( api_parameters & params )
{
	free();
	initialize();
	
	int err = 0;
	
	gsl_vector t_0;
	if ( api_get_vector( params, "filter::t_0", &t_0, &cout ) )
		err = 1;
	
	gsl_matrix q_0;
	if ( api_get_matrix( params, "filter::Q_0", &q_0, &cout ) )
		err = 1;
	
	gsl_matrix f;
	if ( api_get_matrix( params, "filter::F", &f, &cout ) )
		err = 1;
		
	gsl_matrix q;
	if ( api_get_matrix( params, "filter::Q", &q, &cout ) )
		err = 1;
	
	unsigned int size_x;
	if ( api_get_positive_integer( params, "filter::size_x", &size_x, &cout ) )
		err = 1;
		
	if ( err )
		return 1;
		
	unsigned int size_t = t_0.size, size_y = size_t - size_x;
	
	if ( 	! size_x 					|| 
			size_x >= size_t 			||
			q_0.size1 != size_t	||
			q_0.size2 != size_t	||
			q.size1 != size_t		||
			q.size2 != size_t		||
			f.size1 != size_t			||
			f.size2 != size_t			)
	{
		cout << "Error : Dim!" << endl;
		return 1;
	}
	
	
	
	_size_t = size_t;
	_size_x = size_x;
	_size_y = size_y;
	
	alloc();
	
	gsl_vector_memcpy( _t_0, &t_0);
	gsl_matrix_memcpy( _q_0, &q_0 );
	gsl_matrix_memcpy( _q, &q );
	gsl_matrix_memcpy( _f, &f );
	
	return 0;
}

parameters :: ~parameters()
{
	free();
	initialize();
}

void parameters :: free()
{
	if ( _t_0 )
		gsl_vector_free( _t_0 );

	if ( _q_0 )
		gsl_matrix_free( _q_0 );
		
	if ( _q )
		gsl_matrix_free( _q );
		
	if ( _f )
		gsl_matrix_free( _f );

}

void parameters :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;

	_t_0 = 0;
	_q_0 = 0;
	_f = 0;
	_q = 0;
}

void parameters :: alloc()
{
	_t_0 = gsl_vector_alloc( _size_t );
	_q_0 = gsl_matrix_alloc( _size_t, _size_t );
	_f = gsl_matrix_alloc( _size_t, _size_t );
	_q = gsl_matrix_alloc( _size_t, _size_t );
	
}
