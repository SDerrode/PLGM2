#include "tkalman_q_estimation_t3_block_workspace.hpp"
tkalman :: q_estimation :: t3_block ::workspace :: workspace ( 	unsigned int size,
																unsigned int size_t,
																unsigned int size_b ) throw ( exception & )
: tkalman :: workspace ( size, size_t - size )
{
	tkalman :: q_estimation :: t3_block :: workspace :: initialize();
	_size_b = size_b;
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
	
	view = 
		gsl_matrix_submatrix ( 	_mat_tpipb_b,
								0,
								0,
								_size_b,
								_size_b );
	
	_mat_tpipb_b_view_00 = view.matrix;
	
	view = 
		gsl_matrix_submatrix ( 	_mat_tpipb_b,
								_size_b,
								0,
								_size_t + _size_x,
								_size_b );
	
	_mat_tpipb_b_view_10 = view.matrix;

	
}

tkalman :: q_estimation :: t3_block :: workspace :: ~workspace()
{
	tkalman :: q_estimation :: t3_block :: workspace :: free();
	tkalman :: q_estimation :: t3_block :: workspace :: initialize();
}

void tkalman :: q_estimation :: t3_block :: workspace :: initialize()
{
	_mat_i_tpi = 0;
	_mat_tpi_i_1 = 0;
	_mat_tpi_b_1 = 0;
	_mat_tpipb_b = 0;
	_mat_bb = 0;
	_mat_bi = 0;
	_vect_b = 0;
	_size_b = 0;
}

void tkalman :: q_estimation :: t3_block :: workspace :: alloc()
{
	_mat_i_tpi = 
		gsl_matrix_alloc ( 
			_size_x, 
			_size_t + _size_x );
			
	_mat_tpi_i_1 = 
		gsl_matrix_alloc( 
			_size_x + _size_t, 
			_size_x );
		
	_mat_tpi_b_1 = 
		gsl_matrix_alloc( 
			_size_x + _size_t, 
			_size_b );
	
	_mat_tpipb_b =
		gsl_matrix_alloc(
			_size_t + _size_x + _size_b,
			_size_b );
	
	_mat_bb =
		gsl_matrix_alloc(
			_size_b,
			_size_b );
			
	_mat_bi =
		gsl_matrix_alloc(
			_size_b,
			_size_x );
			
	_vect_b = 
		gsl_vector_alloc( _size_b );
}

void tkalman :: q_estimation :: t3_block :: workspace ::  free()
{
	if ( _mat_i_tpi )
		gsl_matrix_free( _mat_i_tpi );
	if ( _mat_tpi_i_1 )
		gsl_matrix_free( _mat_tpi_i_1 );
	if ( _mat_tpi_b_1 )
		gsl_matrix_free ( _mat_tpi_b_1 );
	if ( _mat_tpipb_b )
		gsl_matrix_free( _mat_tpipb_b );
	if ( _mat_bb )
		gsl_matrix_free( _mat_bb );
	if ( _mat_bi )
		gsl_matrix_free (_mat_bi );
	if ( _vect_b )
		gsl_vector_free (_vect_b );
		
}


 
