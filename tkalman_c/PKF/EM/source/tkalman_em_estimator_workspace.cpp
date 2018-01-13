#include "tkalman_em_estimator_workspace.hpp"
using namespace tkalman;
using namespace EM;
estimator_workspace  :: estimator_workspace (	unsigned int size_x,
												unsigned int size_y ) throw ( exception & )
: workspace ( size_x, size_y )
{
	initialize();
	alloc();
	gsl_matrix_view view;
	gsl_vector_view view42;
	view = gsl_matrix_submatrix(_mat_4t2t,
								0,
								0,
								_size_t * 2,
								_size_t * 2);
	_mat_4t2t_view_0 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_4t2t,
								_size_t * 2,
								0,
								_size_t * 2,
								_size_t * 2);
	_mat_4t2t_view_1 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2tp1_t,
								0,
								0,
								_size_t,
								_size_t);
	_mat_2tp1_t_view_0 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2tp1_t,
								_size_t,
								0,
								_size_t,
								_size_t);
	_mat_2tp1_t_view_1 = view.matrix;
	
	view42 = gsl_matrix_row (_mat_2tp1_t,
								2 * _size_t);
	_mat_2tp1_t_view_2 = view42.vector;

	_pkf_parameters->setup( _size_x, _size_t );
}
estimator_workspace  :: ~estimator_workspace ()
{
	free();
	initialize();
}

void estimator_workspace  :: free()
{
	if (_mat_2tp1_t)
		gsl_matrix_free( _mat_2tp1_t );
	if (_mat_4t2t )
		gsl_matrix_free( _mat_4t2t);
	if ( _vect_2t )
		gsl_vector_free(_vect_2t);
	if ( _vect_t )
		gsl_vector_free(_vect_t);
	if ( _pkf_parameters )
		delete _pkf_parameters;
}
void estimator_workspace  :: initialize()
{
	_mat_2tp1_t = 0;
	_mat_4t2t = 0;
	_vect_2t = 0;
	_vect_t = 0;
	_pkf_parameters = 0;
}

void estimator_workspace  :: alloc()
{
	_mat_2tp1_t = gsl_matrix_alloc( 2 * _size_t + 1, _size_t );
	_mat_4t2t = gsl_matrix_alloc( 4 * _size_t, 2 * _size_t );
	_vect_2t = gsl_vector_alloc( 2 * _size_t );
	_vect_t = gsl_vector_alloc( _size_t );
	_pkf_parameters = new tkalman::parameters;
	
}
