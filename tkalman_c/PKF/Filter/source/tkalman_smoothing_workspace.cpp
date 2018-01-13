#include "tkalman_smoothing_workspace.hpp"
using namespace tkalman;
smoothing_workspace :: smoothing_workspace(	unsigned int size_x, 
											unsigned int size_y ) throw ( exception & )
: workspace ( size_x, size_y )
{
	initialize();
	alloc();
	
	gsl_matrix_view view;
	view = gsl_matrix_submatrix(_mat_tx,
								0,
								0,
								_size_x,
								_size_x);
	_mat_xx = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								0,
								0,
								3 * _size_x,
								2 * _size_x);
	_mat_3x2x = view.matrix;
	//00
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								0,
								0,
								_size_x,
								_size_x);
	_mat_3x2x_view_00 = view.matrix;
	_mat_2xpt_xpt_view_00 = view.matrix;
	//01
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								0,
								_size_x,
								_size_x,
								_size_t);
	_mat_2xpt_xpt_view_01 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								0,
								_size_x,
								_size_x,
								_size_x);
	_mat_3x2x_view_01 = view.matrix;
	//10
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								_size_x,
								0,
								_size_t,
								_size_x);
	_mat_2xpt_xpt_view_10 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								_size_x,
								0,
								_size_x,
								_size_x);
	_mat_3x2x_view_10 = view.matrix;
	//11
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								_size_x,
								_size_x,
								_size_t,
								_size_t);
	_mat_2xpt_xpt_view_11 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								_size_x,
								_size_x,
								_size_x,
								_size_x);
	_mat_3x2x_view_11 = view.matrix;
	
	//20
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								_size_x + _size_t,
								0,
								_size_x,
								_size_x);
	_mat_2xpt_xpt_view_20 = view.matrix;
	
	
	
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								2 * _size_x,
								0,
								_size_x,
								_size_x);
	_mat_3x2x_view_20 = view.matrix;
	
	
	//21
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								_size_x + _size_t,
								_size_x,
								_size_x,
								_size_t);
	_mat_2xpt_xpt_view_21 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_xpt,
								2 * _size_x,
								_size_x,
								_size_x,
								_size_x);
	_mat_3x2x_view_21 = view.matrix;
	
	//Vect
	gsl_vector_view view42 = gsl_vector_subvector(_vect_xpt, 0, 2 * _size_x);
	_vect_2x = view42.vector;
	
}

smoothing_workspace :: ~smoothing_workspace( )
{
	free();
	initialize();
}

void smoothing_workspace :: free()
{
	if ( _perm_x )
		gsl_permutation_free( _perm_x );
	if ( _vect_xpt )
		gsl_vector_free ( _vect_xpt );
	if ( _mat_tx )
		gsl_matrix_free( _mat_tx );
	if ( _mat_2xpt_xpt )
		gsl_matrix_free( _mat_2xpt_xpt );
	if (  _psi_workspace )
		delete  _psi_workspace ;
}

void smoothing_workspace :: initialize()
{
	_perm_x = 0;
	_vect_xpt = 0;
	_mat_tx = 0;
	_mat_2xpt_xpt = 0;
	 _psi_workspace = 0;
}

void smoothing_workspace :: alloc()
{
	_perm_x = gsl_permutation_alloc( _size_x );
	_vect_xpt = gsl_vector_alloc( _size_t + _size_x );
	_mat_tx = gsl_matrix_alloc( _size_t, _size_x );
	_mat_2xpt_xpt = gsl_matrix_alloc( 2 * _size_x + _size_t, _size_x + _size_t );
	 _psi_workspace = new gsl_pseudo_inverse_workspace( _size_x );
}
