#include "tkalman_q_estimation_t2_block_workspace.hpp"
tkalman :: q_estimation :: t2_block ::workspace :: workspace ( 	unsigned int size,
																unsigned int size_t ) throw ( exception & )
: tkalman :: workspace ( size, size_t - size )
{
	tkalman :: q_estimation :: t2_block :: workspace :: initialize();
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
}

tkalman :: q_estimation :: t2_block :: workspace :: ~workspace()
{
	tkalman :: q_estimation :: t2_block :: workspace :: free();
	tkalman :: q_estimation :: t2_block :: workspace :: initialize();
}

void tkalman :: q_estimation :: t2_block :: workspace :: initialize()
{
	_mat_i_tpi = 0;
	_mat_tpi_i_1 = 0;
	_mat_tpi_i_2 = 0;
	_mat_ii = 0;
}

void tkalman :: q_estimation :: t2_block :: workspace :: alloc()
{
	_mat_i_tpi = gsl_matrix_alloc ( _size_x, _size_t + _size_x );
	_mat_tpi_i_1 = gsl_matrix_alloc( _size_x + _size_t, _size_x );
	_mat_tpi_i_2 = gsl_matrix_alloc( _size_x + _size_t, _size_x );
	_mat_ii = gsl_matrix_alloc ( _size_x, _size_x );
}

void tkalman :: q_estimation :: t2_block :: workspace ::  free()
{
	if ( _mat_i_tpi )
		gsl_matrix_free( _mat_i_tpi );
	if ( _mat_tpi_i_1 )
		gsl_matrix_free( _mat_tpi_i_1 );
	if ( _mat_tpi_i_2 )
		gsl_matrix_free( _mat_tpi_i_2 );
	if ( _mat_ii )
		gsl_matrix_free( _mat_ii );
		
		
		
}


 
