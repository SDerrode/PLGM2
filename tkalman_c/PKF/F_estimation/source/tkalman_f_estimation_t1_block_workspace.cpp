#include "tkalman_f_estimation_t1_block_workspace.hpp"
tkalman :: f_estimation :: t1_block :: workspace :: workspace( 	unsigned int size_i,
																unsigned int size_t,
																unsigned int size_g )
: tkalman :: workspace( size_i, 
						size_t - size_i )
{
	tkalman :: f_estimation :: t1_block :: workspace :: initialize();
	_size_g = size_g;
	_mat_tpi_gpi_1 = gsl_matrix_calloc(	_size_t + _size_x, 
										_size_g + _size_x );
										
	_mat_tpi_tpi = gsl_matrix_calloc( 	_size_t + _size_x,
										_size_t + _size_x );
										
	_mat_tpi_gpi_2 = gsl_matrix_calloc(	_size_t + _size_x, 
										_size_g + _size_x );
										
	_vect_gpi = gsl_vector_alloc( _size_g + _size_x );
	
	_perm_g = gsl_permutation_alloc( _size_g );
	
	_mat_gi = gsl_matrix_alloc( _size_g, _size_x );
	_mat_gg = gsl_matrix_alloc( _size_g, _size_g );
	
	gsl_matrix_view m_v = gsl_matrix_submatrix ( 	_mat_tpi_gpi_1,
													0,
													0,
													_size_t,
													_size_g );
	_mat_tpi_gpi_1_view_00 = m_v.matrix;
	
	m_v = gsl_matrix_submatrix ( 	_mat_tpi_gpi_1,
									_size_t,
									_size_g,
									_size_x,
									_size_x );
	gsl_matrix_set_identity( &m_v.matrix);
	
	
	m_v = gsl_matrix_submatrix ( 	_mat_tpi_tpi,
									0,
									0,
									_size_t,
									_size_t );
	_mat_tpi_tpi_view_00 = m_v.matrix;
	
	m_v = gsl_matrix_submatrix ( 	_mat_tpi_tpi,
									0,
									_size_t,
									_size_t,
									_size_x );
	_mat_tpi_tpi_view_01 = m_v.matrix;
	
	m_v = gsl_matrix_submatrix ( 	_mat_tpi_gpi_2,
									0,
									0,
									_size_g,
									_size_g );
	_mat_tpi_gpi_2_view_00 = m_v.matrix;
	
	
	m_v = gsl_matrix_submatrix ( 	_mat_tpi_gpi_2,
									0,
									_size_g,
									_size_g,
									_size_x );
	_mat_tpi_gpi_2_view_01 = m_v.matrix;
}


tkalman :: f_estimation :: t1_block :: workspace :: ~workspace()
{
	if ( _mat_tpi_gpi_1 )
		gsl_matrix_free ( _mat_tpi_gpi_1 );
	if ( _mat_tpi_tpi )
		gsl_matrix_free( _mat_tpi_tpi );
	if( _mat_tpi_gpi_2 )
		gsl_matrix_free( _mat_tpi_gpi_2 );
	if ( _vect_gpi )
		gsl_vector_free (_vect_gpi );
	if ( _perm_g )
		gsl_permutation_free( _perm_g );
	if ( _mat_gi )
		gsl_matrix_free( _mat_gi );
	if (_mat_gg )
		gsl_matrix_free( _mat_gg );
		
		
	tkalman :: f_estimation :: t1_block :: workspace :: initialize();
}

void tkalman :: f_estimation :: t1_block :: workspace :: initialize()
{
	_size_g = 0;
	_mat_tpi_gpi_1 = 0;
	_mat_tpi_tpi = 0;
	_mat_tpi_gpi_2 = 0;
	_vect_gpi = 0;
	_perm_g = 0;
	_mat_gi = 0;
	_mat_gg = 0;

}
