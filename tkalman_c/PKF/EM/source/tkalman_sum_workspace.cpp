#include "tkalman_sum_workspace.hpp"
using namespace tkalman;
sum_workspace :: sum_workspace (	unsigned int size_x,
									unsigned int size_y ) 
throw ( exception & )
: workspace ( size_x, size_y )
{
	initialize();
	alloc();
	gsl_matrix_view view;
	gsl_vector_view view42;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								0,
								0,
								_size_x,
								_size_x);
	_mat_2xpt_2xpt_view_00 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x,
								0,
								_size_t,
								_size_x);
	_mat_2xpt_2xpt_view_10 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x,
								_size_x,
								_size_t,
								_size_t);
	_mat_2xpt_2xpt_view_11 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x,
								_size_x + _size_t,
								_size_t,
								_size_x);
	_mat_2xpt_2xpt_view_12 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x + _size_t,
								_size_x,
								_size_x,
								_size_t);
	_mat_2xpt_2xpt_view_21 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x + _size_t,
								_size_x + _size_t,
								_size_x,
								_size_x);
	_mat_2xpt_2xpt_view_22 = view.matrix;
	
	
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								0,
								0,
								3 * _size_x,
								3 * _size_x);
	_mat_3x3x = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								0,
								0,
								_size_x,
								_size_x);
	_mat_3x3x_view_00 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x,
								0,
								_size_x,
								_size_x);
	_mat_3x3x_view_10 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x,
								_size_x,
								_size_x,
								_size_x);
	_mat_3x3x_view_11 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x,
								_size_x + _size_x,
								_size_x,
								_size_x);
	_mat_3x3x_view_12 = view.matrix;
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x + _size_x,
								_size_x,
								_size_x,
								_size_x);
	_mat_3x3x_view_21 = view.matrix;
	
	
	
	
	
	view = gsl_matrix_submatrix(_mat_2xpt_2xpt,
								_size_x + _size_x,
								_size_x + _size_x,
								_size_x,
								_size_x);
	_mat_3x3x_view_22 = view.matrix;
	
	
	
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								0,
								0,
								4 * _size_t,
								2 * _size_t);
	_mat_4t2t = view.matrix;
	

	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								2 * _size_t,
								0,
								2 * _size_t + 1,
								2 * _size_t);
	_mat_2tp1_2t = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								2 * _size_t,
								0,
								_size_x,
								_size_x);
	_mat_2tp1_2t_view_00 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								2 * _size_t,
								0,
								_size_t,
								_size_t);
	_mat_2tp1_2t_view_00_bis = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								2 * _size_t,
								_size_t,
								_size_x,
								_size_x);
	_mat_2tp1_2t_view_02 = view.matrix;
	
	
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								0,
								0,
								2 * _size_t,
								2 * _size_t);
	
	
	 _mat_4t2t_view_sum = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								2 * _size_t,
								_size_t,
								_size_t,
								_size_x);
	_mat_2tp1_2t_view_02_bis = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_4tp1_2t,
								3 * _size_t,
								_size_t,
								_size_x,
								_size_x);
	_mat_2tp1_2t_view_22 = view.matrix;
	
	view42 = gsl_matrix_subrow (_mat_4tp1_2t, 
								4 * _size_t, 
								0, 
								_size_x);
	_mat_2tp1_2t_view_30 = view42.vector;
							
	view42 = gsl_matrix_subrow (_mat_4tp1_2t, 
								4 * _size_t, 
								0, 
								_size_t);
	_mat_2tp1_2t_view_30_bis = view42.vector;					
								
	view42 = gsl_matrix_subrow (_mat_4tp1_2t, 
								4 * _size_t, 
								_size_x, 
								_size_y);
	_mat_2tp1_2t_view_31 = view42.vector;
								
	view42 = gsl_matrix_subrow (_mat_4tp1_2t, 
								4 * _size_t, 
								_size_t, 
								_size_x);
	_mat_2tp1_2t_view_32 = view42.vector;
								
	view42 = gsl_matrix_subrow (_mat_4tp1_2t, 
								4 * _size_t, 
								_size_t + _size_x, 
								_size_y);
	_mat_2tp1_2t_view_33 = view42.vector;	
	
	
	
	

	view42 = gsl_vector_subvector(_vect_2xpt, 0, 3 * _size_x);
	_vect_3x = view42.vector;
}				

sum_workspace :: ~sum_workspace()
{
	free();
	initialize();
}
void sum_workspace :: free()
{
	if ( _mat_2xpt_2xpt )
		gsl_matrix_free( _mat_2xpt_2xpt );
	if ( _mat_4tp1_2t )
		gsl_matrix_free( _mat_4tp1_2t );
	if ( _vect_2xpt )
		gsl_vector_free ( _vect_2xpt );
	if ( _vect_2t )
		gsl_vector_free ( _vect_2t );
}

void sum_workspace :: initialize()
{
	_mat_2xpt_2xpt = 0;
	_mat_4tp1_2t = 0;
	_vect_2xpt = 0;
	_vect_2t = 0;
}
void sum_workspace :: alloc()
{
	_mat_2xpt_2xpt = gsl_matrix_alloc( 2 * _size_x + _size_t, 2 * _size_x + _size_t );
	_mat_4tp1_2t = gsl_matrix_alloc( 4 * _size_t + 1, 2 * _size_t );
	_vect_2xpt = gsl_vector_alloc( 2 * _size_x + _size_t );
	_vect_2t = gsl_vector_alloc( 2 * _size_t );
}
