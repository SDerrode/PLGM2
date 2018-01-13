#include "tkalman_filter_workspace.hpp"
using namespace tkalman;
filter_workspace :: filter_workspace (	unsigned int size_x, 
										unsigned int size_y ) throw (exception &)
: workspace( size_x, size_y )
{
	initialize();
	alloc();
}

filter_workspace :: ~filter_workspace()
{
	free();
	initialize();
}

void filter_workspace :: free()
{
	if ( _f2_xt )
		gsl_matrix_free( _f2_xt ) ;

	if ( _sqrt_q2_xx )
		gsl_matrix_free( _sqrt_q2_xx ) ;
	
	if ( _q2_xy )
		gsl_matrix_free ( _q2_xy );

	if ( _sqrt_q_yy )
		gsl_matrix_free( _sqrt_q_yy );

	if ( _vect_y )
		gsl_vector_free( _vect_y );
}

void filter_workspace :: initialize()
{
	_f2_xt = 0;
	_sqrt_q2_xx = 0;
	_q2_xy = 0;
	_sqrt_q_yy = 0;  
	_vect_y = 0;
}

void filter_workspace :: alloc()
{
	_f2_xt = gsl_matrix_alloc( _size_x, _size_t );
	_sqrt_q2_xx = gsl_matrix_alloc( _size_x, _size_x );
	_q2_xy = gsl_matrix_alloc( _size_x, _size_y );
	_sqrt_q_yy = gsl_matrix_alloc( _size_y, _size_y );
	_vect_y = gsl_vector_alloc( _size_y );
	
}
