#include "tkalman_moments.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "gsl_triangle_matrix.hpp"
#include <iostream>
using namespace std;
using namespace tkalman;
moments :: moments ( void )
{
	initialize();
}

moments :: moments (	unsigned int size_x,
						unsigned int size_y,
						unsigned int nb_moments ) throw( exception&)
{
	initialize();
	if ( ! setup( size_x, size_y, nb_moments ) )
		throw ( invalid_argument( "Invalid argument in moments :: moments" ) );
	
}

int moments :: setup(	unsigned int size_x,
						unsigned int size_y,
						unsigned int nb_moments )
{
	reset();
	if ( ! size_x || ! size_y )
		return 1;
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_x + size_y;
	_max_moments = nb_moments;
	alloc();
	if ( _max_moments > 0 )
	{
		gsl_vector_view view = gsl_vector_subvector( _x_p[0], 0, _size_x );
		_x_p_0 = view.vector;
		
		view = gsl_vector_subvector( _x_f[0], 0, _size_x );
		_x_f_0 = view.vector;
		
		view = gsl_vector_subvector( _x_s[0], 0, _size_x );
		_x_s_0 = view.vector;
	}
	return 0;
}

void moments :: reset()
{
	free();
	initialize();
}

void moments :: set_nb_moments( unsigned int nb )
{
	if ( nb > _max_moments )
	{
		free();
		_max_moments = nb;
		alloc();
		if ( nb > 0 )
		{
			gsl_vector_view view = gsl_vector_subvector( _x_p[0], 0, _size_x );
			_x_p_0 = view.vector;
			
			view = gsl_vector_subvector( _x_f[0], 0, _size_x );
			_x_f_0 = view.vector;
			
			view = gsl_vector_subvector( _x_s[0], 0, _size_x );
			_x_s_0 = view.vector;
		}
	}
	_nb_moments = nb;
}

void update_x( 	gsl_vector * x,
				gsl_matrix * mat_x,
				const gsl_matrix * m_xx,
				gsl_vector * tmp_x,
				gsl_matrix * tmp_mat_x )
{
	gsl_vector_memcpy( tmp_x, x );
	gsl_blas_dgemv(	CblasNoTrans,
					1.0,
					m_xx,
					tmp_x,
					0,
					x );
					
	gsl_matrix_memcpy( tmp_mat_x, mat_x );
	gsl_blas_dgemm(	CblasNoTrans,
					CblasTrans,
					1.0,
					tmp_mat_x,
					m_xx,
					0.0,
					mat_x );
	gsl_linalg_QR_decomp(	mat_x,
							tmp_x );
	gsl_triangle_matrix( mat_x );			
}






//Transformation
int moments :: transformation(  const gsl_matrix * m,
								const gsl_vector * const * y )
{
	if ( m->size1 != _size_t	|| m->size2 != _size_t )
		return 1;
	//0
	{
		gsl_matrix * mat_t = gsl_matrix_alloc( _size_t, _size_t );
		gsl_vector * vect_t = gsl_vector_alloc( _size_t );
		
		update_x( 	_x_p[0],
					_sqrt_p_p[0],
					m,
					vect_t,
					mat_t  );
		update_x( 	_x_f[0],
					_sqrt_p_f[0],
					m,
					vect_t,
					mat_t  );
		update_x( 	_x_s[0],
					_sqrt_p_s[0],
					m,
					vect_t,
					mat_t  );
		
		gsl_matrix_free( mat_t );		
		gsl_vector_free( vect_t );			
	}
	
	//1 -> N
	{
		gsl_matrix_const_view m_view = gsl_matrix_const_submatrix( m, 0, 0, _size_x, _size_x );
		gsl_matrix m_xx = m_view.matrix;
		
		gsl_matrix_const_view m_view_2 = gsl_matrix_const_submatrix( m, 0, _size_x, _size_x, _size_y );
		gsl_matrix m_xy = m_view_2.matrix;
		
		
		gsl_matrix * mat_x = gsl_matrix_alloc( _size_x, _size_x );
		gsl_vector * vect_x = gsl_vector_alloc( _size_x );
		for ( unsigned int i = 1; i < _nb_moments; ++ i )
		{
			update_x( 	_x_p[i],
						_sqrt_p_p[i],
						&m_xx,
						vect_x,
						mat_x  );
			gsl_blas_dgemv( CblasNoTrans,
							1.0,
							&m_xy,
							y[i-1],
							1.0,
							_x_p[i] );
			
						
			update_x( 	_x_f[i],
						_sqrt_p_f[i],
						&m_xx,
						vect_x,
						mat_x  );
			gsl_blas_dgemv( CblasNoTrans,
							1.0,
							&m_xy,
							y[i-1],
							1.0,
							_x_f[i] );
						
			update_x( 	_x_s[i],
						_sqrt_p_s[i],
						&m_xx,
						vect_x,
						mat_x  );
			gsl_blas_dgemv( CblasNoTrans,
							1.0,
							&m_xy,
							y[i-1],
							1.0,
							_x_s[i] );
							
		}
		gsl_matrix_free( mat_x );
		gsl_vector_free( vect_x );	
	}
	return 0;
}


moments :: ~moments()
{
	reset();
}

const gsl_vector * moments :: get_innovation( unsigned int n ) const
{
	if ( n > _nb_moments )
		return NULL;
	else
		return _y_p[n];
}

int moments :: get_s( 	gsl_matrix * s,
						unsigned int n ) const
{
	if ( n > _nb_moments || s->size1 != _size_y || s->size2 != _size_y )
		return 1;
	
	gsl_blas_dgemm(	CblasTrans, 
					CblasNoTrans, 
					1.0, 
					_sqrt_s_p[n], 
					_sqrt_s_p[n], 
					0, 
					s );
	return 0;
}

const gsl_vector * moments :: get_x_p( unsigned int n ) const
{
	if ( n > _nb_moments )
		return NULL;
	else if ( n == 0 )
		return &_x_p_0;
	else
		return _x_p[n];
}

int moments :: get_p_p( 	gsl_matrix * s,
							unsigned int n ) const
{
	if ( n > _nb_moments || s->size1 != _size_x || s->size2 != _size_x )
		return 1;
	if ( n != 0 )
		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans, 
						1.0, 
						_sqrt_p_p[n], 
						_sqrt_p_p[n], 
						0, 
						s );
	else
	{
		gsl_matrix_view m_view = gsl_matrix_submatrix( _sqrt_p_p[0], 0, 0, _size_x, _size_x );
		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans, 
						1.0, 
						&m_view.matrix, 
						&m_view.matrix, 
						0, 
						s );
	}
	return 0;
}

const gsl_vector * moments :: get_x_f( unsigned int n ) const
{
	if ( n > _nb_moments )
		return NULL;
	else if ( n == 0 )
		return &_x_f_0;
	else
		return _x_f[n];
}

int moments :: get_p_f( 	gsl_matrix * s,
							unsigned int n ) const
{
	if ( n > _nb_moments || s->size1 != _size_x || s->size2 != _size_x )
		return 1;
	if ( n != 0 )
		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans, 
						1.0, 
						_sqrt_p_f[n], 
						_sqrt_p_f[n], 
						0, 
						s );
	else
	{
		gsl_matrix_view m_view = gsl_matrix_submatrix( _sqrt_p_f[0], 0, 0, _size_x, _size_x );
		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans, 
						1.0, 
						&m_view.matrix, 
						&m_view.matrix, 
						0, 
						s );
	}
	return 0;
}

const gsl_vector * moments :: get_x_s( unsigned int n ) const
{
	if ( n > _nb_moments )
		return NULL;
	else if ( n == 0 )
		return &_x_s_0;
	else
		return _x_s[n];
}

int moments :: get_p_s( 	gsl_matrix * s,
							unsigned int n ) const
{
	if ( n > _nb_moments || s->size1 != _size_x || s->size2 != _size_x )
		return 1;
	if ( n != 0 )
		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans, 
						1.0, 
						_sqrt_p_s[n], 
						_sqrt_p_s[n], 
						0, 
						s );
	else
	{
		gsl_matrix_view m_view = gsl_matrix_submatrix( _sqrt_p_s[0], 0, 0, _size_x, _size_x );
		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans, 
						1.0, 
						&m_view.matrix, 
						&m_view.matrix, 
						0, 
						s );
	}
	return 0;
}


void moments :: initialize()
{
	_y_p = 0;
	_sqrt_s_p = 0;
	_x_p = 0;
	_sqrt_p_p = 0;
	_x_f = 0;
	_sqrt_p_f = 0;
	_x_s = 0;
	_sqrt_p_s = 0;
	_c_s = 0;
	_nb_moments = 0;
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_max_moments = 0;
}

void moments :: free()
{
	tkalman_expectation_unref( _y_p, _max_moments )
	tkalman_expectation_unref( _x_p, _max_moments )
	tkalman_expectation_unref( _x_f, _max_moments )
	tkalman_expectation_unref( _x_s, _max_moments )
	
	tkalman_covariance_unref( _sqrt_s_p, _max_moments )
	tkalman_covariance_unref( _sqrt_p_p, _max_moments )
	tkalman_covariance_unref( _sqrt_p_f, _max_moments )
	tkalman_covariance_unref( _sqrt_p_s, _max_moments )
	tkalman_covariance_unref( _c_s, _max_moments )

}

void moments :: alloc()
{
	if ( _max_moments )
	{
		tkalman_expectation_ref(_y_p, _max_moments, _size_y, _size_y)
		tkalman_expectation_ref(_x_p, _max_moments, _size_x, _size_t)
		tkalman_expectation_ref(_x_s, _max_moments, _size_x, _size_t)
		tkalman_expectation_ref(_x_f, _max_moments, _size_x, _size_t)
		
		tkalman_covariance_ref( _sqrt_s_p, _max_moments, _size_y, _size_y, _size_y, _size_y )
		tkalman_covariance_ref( _sqrt_p_p, _max_moments, _size_x, _size_x, _size_t, _size_t )
		tkalman_covariance_ref( _sqrt_p_f, _max_moments, _size_x, _size_x, _size_t, _size_t)
		tkalman_covariance_ref( _sqrt_p_s, _max_moments, _size_x, _size_x, _size_t, _size_t )
		tkalman_covariance_ref( _c_s, _max_moments, _size_x, _size_x, _size_x, _size_t )
	}
}


