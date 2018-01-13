#include "tkalman_q_estimation_workspace.hpp"
tkalman :: q_estimation :: workspace :: workspace ( unsigned int size_t ) throw ( exception & )
{
	initialize();
	if ( size_t == 0 )
		throw ( invalid_argument( "Invalid argument in kalman :: q_estimation :: workspace :: workspace ( unsigned int size_t ) throw ( exception & )") );
		
	_size_t = size_t;
	
	alloc();
	
	gsl_matrix_view m_view = gsl_matrix_submatrix(	_mat_2t_2t_3,
													_size_t,
													_size_t,
													_size_t,
													_size_t );
													
	_mat_2t_2t_3_view_11 = m_view.matrix;
	
}
tkalman :: q_estimation :: workspace :: ~workspace()
{
	free();
	initialize();
}

void tkalman :: q_estimation :: workspace :: initialize()
{
	_size_t = 0;
	_mat_2t_2t_1 = 0;
	_mat_tt_2 = 0;
	_mat_tt_1 = 0;
	_mat_tt_3 = 0;
	_mat_tt_4 = 0;
	_mat_2t_2t_2 = 0;
	_mat_2t_2t_3 = 0;
	_vect_2t = 0;
}

void tkalman :: q_estimation :: workspace :: free()
{
	if ( _mat_2t_2t_1 )
		gsl_matrix_free( _mat_2t_2t_1 );
	if ( _mat_2t_2t_2 )
		gsl_matrix_free( _mat_2t_2t_2 );
	if ( _mat_2t_2t_3 )
		gsl_matrix_free( _mat_2t_2t_3 );
	if ( _mat_tt_1 )
		gsl_matrix_free( _mat_tt_1 );
	if ( _mat_tt_2 )
		gsl_matrix_free( _mat_tt_2 );
	if ( _mat_tt_3 )
		gsl_matrix_free( _mat_tt_3 );
	if ( _mat_tt_4 )
		gsl_matrix_free( _mat_tt_4 );
	if ( _vect_2t )
		gsl_vector_free( _vect_2t );
}

void tkalman :: q_estimation :: workspace :: alloc()
{
	_mat_2t_2t_1 = gsl_matrix_alloc( 2 * _size_t, 2 * _size_t );
	_mat_2t_2t_2 = gsl_matrix_alloc( 2 * _size_t, 2 * _size_t );
	_mat_2t_2t_3 = gsl_matrix_alloc( 2 * _size_t, 2 * _size_t );
	
	_mat_tt_1 = gsl_matrix_alloc( _size_t, _size_t );
	_mat_tt_2 = gsl_matrix_alloc( _size_t, _size_t );
	_mat_tt_3 = gsl_matrix_alloc( _size_t, _size_t );
	_mat_tt_4 = gsl_matrix_alloc( _size_t, _size_t );
	
	_vect_2t = gsl_vector_alloc ( 2 * _size_t );
}

gsl_matrix tkalman :: q_estimation :: workspace :: f_i( unsigned int size_i)
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_tt_3,
													0,
													0,
													size_i,
													_size_t );
	return m_view.matrix;
}

gsl_matrix tkalman :: q_estimation :: workspace :: sqrt_q_i( unsigned int size_i)
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_tt_4,
													0,
													0,
													size_i,
													size_i );
	return m_view.matrix;
}

gsl_matrix tkalman :: q_estimation :: workspace :: sqrt_c_i( unsigned int size_i)
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_2t_2t_2,
													0,
													0,
													_size_t + size_i,
													_size_t + size_i );
	return m_view.matrix;
}

gsl_matrix  tkalman :: q_estimation :: workspace :: sqrt_c_i_2t_tpi( unsigned int size_i)
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_2t_2t_2,
													0,
													0,
													2 * _size_t,
													_size_t + size_i );
	return m_view.matrix;
}

gsl_matrix tkalman :: q_estimation :: workspace :: mat_2t_tpi_1( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_2t_2t_3,
													0,
													0,
													2 * _size_t,
													_size_t + size_i );
	return m_view.matrix;
}

gsl_matrix tkalman :: q_estimation :: workspace :: mat_2t_tpi_1_view_00( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_2t_2t_3,
													0,
													0,
													_size_t,
													_size_t );
	return m_view.matrix;
}
gsl_matrix tkalman :: q_estimation :: workspace :: mat_2t_tpi_1_view_11( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix ( _mat_2t_2t_3,
													_size_t,
													_size_t,
													_size_t,
													size_i );
	return m_view.matrix;
}

gsl_vector tkalman :: q_estimation :: workspace :: vect_tpi(unsigned int size_i)
{
	gsl_vector_view v_view = 
		gsl_vector_subvector
		( 	_vect_2t, 
			0, 
			size_i + _size_t );
	return v_view.vector;
}
