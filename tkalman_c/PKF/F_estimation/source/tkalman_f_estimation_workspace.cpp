#include "tkalman_f_estimation_workspace.hpp"
tkalman :: f_estimation :: workspace :: workspace( unsigned int size_t ) throw ( exception & )
{
	tkalman :: f_estimation :: workspace :: initialize();
	if ( ! size_t )
		throw ( invalid_argument ( "Invalid argument in f_estimation :: workspace( unsigned int size_t )" ) );
	_size_t = size_t;
	alloc();
	
	gsl_matrix_view m_view = gsl_matrix_submatrix ( 	_mat_2t_2t_1,
														0,
														0,
														_size_t,
														_size_t );
	_mat_2t_2t_1_view_00 = m_view.matrix;
	
	m_view = gsl_matrix_submatrix ( 	_mat_2t_2t_1,
										0,
										_size_t,
										_size_t,
										_size_t );
	_mat_2t_2t_1_view_01 = m_view.matrix;
	
	
	m_view = gsl_matrix_submatrix ( 	_mat_2t_2t_3,
										0,
										0,
										_size_t,
										_size_t );
	_mat_2t_2t_3_view_00 = m_view.matrix;
	
	
	
	
	
	
}

tkalman :: f_estimation :: workspace :: ~workspace()
{
	free();
	initialize();
}

void tkalman :: f_estimation :: workspace :: initialize()
{
	_size_t = 0;
	_mat_2t_2t_1 = 0;
	_mat_2t_2t_2 = 0;//sq(Cb)
	_mat_2t_2t_3 = 0;
	_mat_tt_1 = 0; //projector & F
	_vect_2t = 0;
	_mat_tt_2 = 0;
}

void tkalman :: f_estimation :: workspace :: free()
{
	if ( _mat_2t_2t_1 )
		gsl_matrix_free (_mat_2t_2t_1);
	if ( _mat_2t_2t_2 )
		gsl_matrix_free (_mat_2t_2t_2);
	if ( _mat_2t_2t_3 )
		gsl_matrix_free (_mat_2t_2t_3);
	if ( _mat_tt_1 )
		gsl_matrix_free (_mat_tt_1);
	if ( _vect_2t )
		gsl_vector_free( _vect_2t );
	if ( _mat_tt_2 )
		gsl_matrix_free( _mat_tt_2 );
		
		
}

void tkalman :: f_estimation :: workspace :: alloc()
{
	_mat_2t_2t_1 = gsl_matrix_alloc( 2 * _size_t, 2 * _size_t );
	_mat_2t_2t_2 = gsl_matrix_alloc( 2 * _size_t, 2 * _size_t );
	_mat_2t_2t_3 = gsl_matrix_alloc( 2 * _size_t, 2 * _size_t );
	_mat_tt_1 = gsl_matrix_alloc( _size_t, _size_t );
	_vect_2t = gsl_vector_alloc( 2 * _size_t );
	_mat_tt_2 = gsl_matrix_alloc( _size_t, _size_t );
}

gsl_matrix tkalman :: f_estimation :: workspace :: m( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_2t_2t_1,
													0,
													0,
													2 * _size_t,
													_size_t + size_i );
	return m_view.matrix;
	
}

gsl_matrix tkalman :: f_estimation :: workspace :: m_view_11( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_2t_2t_1,
													_size_t,
													_size_t,
													_size_t,
													size_i );
	return m_view.matrix;
}

gsl_matrix tkalman :: f_estimation :: workspace :: sqrt_sum( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_2t_2t_3,
													0,
													0,
													size_i + _size_t,
													size_i + _size_t);
	return m_view.matrix;
}
gsl_matrix tkalman :: f_estimation :: workspace :: sqrt_sum_mat_2t_tpi( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_2t_2t_3,
													0,
													0,
													2 * _size_t,
													size_i + _size_t);
	return m_view.matrix;
}


gsl_matrix tkalman :: f_estimation :: workspace :: sqrt_sum_01( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_2t_2t_3,
													0,
													_size_t,
													_size_t,
													size_i);
	return m_view.matrix;
}

gsl_matrix tkalman :: f_estimation :: workspace :: f( unsigned int size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_tt_1,
													0,
													0,
													size_i,
													_size_t);
	return m_view.matrix;
}


gsl_vector tkalman :: f_estimation :: workspace :: vect( unsigned int size_i )
{
	
	gsl_vector_view v_view = gsl_vector_subvector(	_vect_2t,
													0,
													size_i + _size_t );
	return v_view.vector;
}

gsl_vector tkalman :: f_estimation :: workspace :: s_vect( unsigned int size_i )
{
	gsl_vector_view v_view = gsl_vector_subvector(	_vect_2t,
													0,
													size_i );
	return v_view.vector;
}



gsl_matrix tkalman :: f_estimation :: workspace :: mat_ti( unsigned size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_tt_2,
													0,
													0,
													_size_t,
													size_i);
	return m_view.matrix;
}

gsl_matrix tkalman :: f_estimation :: workspace :: sqrt_q_i( unsigned size_i )
{
	gsl_matrix_view m_view = gsl_matrix_submatrix (	_mat_tt_2,
													0,
													0,
													size_i,
													size_i);
	return m_view.matrix;
	
}





