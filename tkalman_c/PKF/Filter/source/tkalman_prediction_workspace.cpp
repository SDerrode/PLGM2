#include "tkalman_prediction_workspace.hpp"
using namespace tkalman;
prediction_workspace :: prediction_workspace(	unsigned int size_x, 
												unsigned int size_y ) throw( exception & )
: workspace( size_x, size_y )
{
	initialize();
	alloc();
	gsl_matrix_view view;
	view = gsl_matrix_submatrix(_mat_xpt_x,
								0,
								0,
								_size_x,
								_size_x);
	_mat_xpt_x_view_00 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_xpt_x,
								_size_x,
								0,
								_size_t,
								_size_x);
	_mat_xpt_x_view_10 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_xpt_x,
								0,
								0,
								2 * _size_x,
								_size_x);
	_mat_2xx = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_xpt_x,
								0,
								0,
								_size_x,
								_size_x);
	_mat_2xx_view_00 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_xpt_x,
								_size_x,
								0,
								_size_x,
								_size_x);
	_mat_2xx_view_10 = view.matrix;
}

prediction_workspace :: ~prediction_workspace()
{
	free();
	initialize();
}

void prediction_workspace :: free()
{
	if ( _mat_xpt_x )
		gsl_matrix_free( _mat_xpt_x );
	if ( _vect_x )
		gsl_vector_free( _vect_x );
		
}

void prediction_workspace :: initialize()
{
	_mat_xpt_x = 0;
	_vect_x = 0;
}

void prediction_workspace :: alloc()
{
	_mat_xpt_x = gsl_matrix_alloc( _size_x + _size_t, _size_x ); 
	_vect_x = gsl_vector_alloc( _size_x );
	
}
