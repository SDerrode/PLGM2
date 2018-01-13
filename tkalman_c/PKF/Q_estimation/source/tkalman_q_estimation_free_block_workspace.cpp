#include "tkalman_q_estimation_free_block_workspace.hpp"
tkalman :: q_estimation :: free_block ::workspace :: workspace ( 	unsigned int size,
																	unsigned int size_t ) throw ( exception & )
: tkalman :: workspace ( size, size_t - size )
{
	tkalman :: q_estimation :: free_block :: workspace :: initialize();
	alloc();
	//F
	gsl_matrix_view view = 
		gsl_matrix_submatrix ( 	_mat_i_tpi,
								0,
								0,
								_size_x,
								_size_t );
	_mat_i_tpi_view_F = view.matrix;
	//-I
	view = 
		gsl_matrix_submatrix ( 	_mat_i_tpi,
								0,
								_size_t,
								_size_x,
								_size_x );
	
	gsl_matrix_set_identity( &view.matrix);
	gsl_matrix_scale( &view.matrix, -1);
	//sq(Q)
	view = 
		gsl_matrix_submatrix ( 	_mat_tpi_i,
								0,
								0,
								_size_x,
								_size_x );
	_mat_tpi_i_view_00 = view.matrix;
}

tkalman :: q_estimation :: free_block :: workspace :: ~workspace()
{
	tkalman :: q_estimation :: free_block ::workspace :: free();
	tkalman :: q_estimation :: free_block ::workspace :: initialize();
}

void tkalman :: q_estimation :: free_block :: workspace :: initialize()
{
	_mat_i_tpi = 0;
	_mat_tpi_i = 0;
	_vect_i = 0;
}

void tkalman :: q_estimation :: free_block :: workspace :: alloc()
{
	_mat_i_tpi = gsl_matrix_alloc ( _size_x, _size_t + _size_x );
	_mat_tpi_i = gsl_matrix_alloc( _size_x + _size_t, _size_x );
	_vect_i = gsl_vector_alloc( _size_x );
}

void tkalman :: q_estimation :: free_block :: workspace ::  free()
{
	if ( _mat_i_tpi )
		gsl_matrix_free( _mat_i_tpi );
	if ( _mat_tpi_i )
		gsl_matrix_free( _mat_tpi_i );
	if ( _vect_i )
		gsl_vector_free( _vect_i );
}


