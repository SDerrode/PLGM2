#include "tkalman_parameters.hpp"
#include <cstring>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
#include <cmath>
#include <gsl/gsl_eigen.h>
using namespace tkalman;
parameters :: parameters( void )
{
	initialize();
}

parameters :: parameters ( const parameters & p ) throw ( exception &)
{
	initialize();
	if ( setup( p._t_0, 
				p._q_0, 
				p._f, 
				p._q, 
				p._size_x ) )
		throw ( invalid_argument( "Invalid argument in parameters :: parameters"));
}
parameters :: parameters(	const gsl_vector * t_0,
							const gsl_matrix * q_0,
							const gsl_matrix * f,
							const gsl_matrix * q,
							unsigned int size_x ) throw ( exception &)
{
	initialize();
	if ( setup( t_0, 
				q_0, 
				f, 
				q, 
				size_x ) )
		throw ( invalid_argument( "Invalid argument in parameters :: parameters"));
}

int parameters :: setup( 	unsigned int size_x,
							unsigned int size_t )
{
	if ( size_t <= size_x )
		return 1;
	if ( ! size_x )
		return 2;
	_size_x = size_x;
	_size_t = size_t;
	_size_y = size_t - size_x;
	alloc();
	gsl_matrix_view m_view = gsl_matrix_submatrix( _sqrt_q, 0, 0, _size_x, _size_x );
	_sqrt_q_xx = m_view.matrix;
	
	m_view = gsl_matrix_submatrix( _sqrt_q, 0, _size_x, _size_x, _size_y );
	_sqrt_q_xy = m_view.matrix;
	
	m_view = gsl_matrix_submatrix( _sqrt_q, _size_x, _size_x, _size_y, _size_y );
	_sqrt_q_yy = m_view.matrix;
	
	
	m_view = gsl_matrix_submatrix( _f, 0, 0, _size_x, _size_t );
	_f_xt = m_view.matrix;
	
	m_view = gsl_matrix_submatrix( _f, _size_x, 0, _size_y, _size_t );
	_f_yt = m_view.matrix;
	return 0;
}
					
int parameters :: setup ( const parameters & p )
{
	if(	p._size_x != _size_x	||
		p._size_t != _size_t 	)
		return setup( 	p._t_0, 
						p._q_0, 
						p._f, 
						p._q, 
						p._size_x );
						
	if ( ! _size_x || ! _size_t )
		return 1;
		
	gsl_vector_memcpy( _t_0, p._t_0);
	gsl_matrix_memcpy( _f, p._f );
	gsl_matrix_memcpy( _q_0, p._q_0 );
	gsl_matrix_memcpy( _q, p._q );

	gsl_matrix_memcpy( _sqrt_q_0, p._sqrt_q_0 );
	gsl_matrix_memcpy( _sqrt_q, p._sqrt_q );
	
	return 0;
}

parameters & parameters :: operator=( const parameters & p ) throw ( exception &)
{
	if ( setup ( p ) )
		throw ( invalid_argument( "Invalid argument in parameters :: operator="));
		
	return *this;
}

int parameters :: setup(	const gsl_vector * t_0,
							const gsl_matrix * q_0,
							const gsl_matrix * f,
							const gsl_matrix * q,
							unsigned int size_x )
{
	reset();

	if ( ! t_0 || ! q_0 || !f || ! q || ! size_x )
		return 1;
	unsigned int size_t = t_0->size,
				 size_y = size_t - size_x;

	if ( size_x >= size_t )
		return 2;

	if (	q_0->size1 != size_t	||
			q_0->size2 != size_t	||
			q->size1 != size_t		||
			q->size2 != size_t		||
			f->size1 != size_t		||
			f->size2 != size_t		)
		return 3;
		
	_size_x = size_x;
	_size_t = size_t;
	_size_y = size_y;
	alloc();

	gsl_vector_memcpy( _t_0, t_0);
	gsl_matrix_memcpy( _f, f );
	gsl_matrix_memcpy( _q_0, q_0 );
	gsl_matrix_memcpy( _q, q );
	
	//Calcul de sq(Q) et sq(Q_0)
	{
		gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (_size_t);
		gsl_matrix * q_cp = gsl_matrix_alloc( _size_t, _size_t );
		gsl_matrix * _p = gsl_matrix_alloc( _size_t, _size_t );
		gsl_vector * vp = gsl_vector_alloc( _size_t );
		
		//Recopie de q
		gsl_matrix_memcpy( q_cp, q );
		
		//Calcul des vp
		gsl_eigen_symmv (	q_cp, 
							vp, 
							_p, 
							w );
							
		//Construction de la matrice sq(D)
		gsl_matrix_set_zero( q_cp );
		for ( unsigned int i = 0; i < _size_t; ++ i )
		{
			if ( vp->data[i * vp->stride] < 0 )
			{
				gsl_vector_free ( vp );
				gsl_matrix_free( q_cp );
				gsl_eigen_symmv_free (w);
				return 3;
			}
			q_cp->data[ i * (q_cp->tda + 1) ] = sqrt( vp->data[i * vp->stride] );
			
		}
		
		gsl_blas_dgemm(	CblasNoTrans,
						CblasTrans,
						1.0,
						q_cp,
						_p,
						0.0,
						_sqrt_q );
		gsl_linalg_QR_decomp(_sqrt_q,
							 vp);
		gsl_triangle_matrix(_sqrt_q);
		
		
		gsl_matrix_memcpy( q_cp, q_0 );
		
		//Calcul des vp
		gsl_eigen_symmv (	q_cp, 
							vp, 
							_p, 
							w );
							
		//Construction de la matrice sq(D)
		gsl_matrix_set_zero( q_cp );
		for ( unsigned int i = 0; i < _size_t; ++ i )
		{
			if ( vp->data[i * vp->stride] < 0 )
			{
				gsl_vector_free ( vp );
				gsl_matrix_free( q_cp );
				gsl_eigen_symmv_free (w);
				return 3;
			}
			q_cp->data[ i * (q_cp->tda + 1) ] = sqrt( vp->data[i * vp->stride] );
			
		}
		
		gsl_blas_dgemm(	CblasNoTrans,
						CblasTrans,
						1.0,
						q_cp,
						_p,
						0.0,
						_sqrt_q_0 );
		gsl_linalg_QR_decomp(_sqrt_q_0,
							 vp);
		gsl_triangle_matrix(_sqrt_q_0);
		
		
		
		
		gsl_vector_free ( vp );
		gsl_matrix_free( q_cp );
		gsl_matrix_free( _p );
		gsl_eigen_symmv_free (w);

	}

	gsl_matrix_view m_view = gsl_matrix_submatrix( _sqrt_q, 0, 0, _size_x, _size_x );
	_sqrt_q_xx = m_view.matrix;
	
	m_view = gsl_matrix_submatrix( _sqrt_q, 0, _size_x, _size_x, _size_y );
	_sqrt_q_xy = m_view.matrix;
	
	m_view = gsl_matrix_submatrix( _sqrt_q, _size_x, _size_x, _size_y, _size_y );
	_sqrt_q_yy = m_view.matrix;
	
	
	m_view = gsl_matrix_submatrix( _f, 0, 0, _size_x, _size_t );
	_f_xt = m_view.matrix;
	
	m_view = gsl_matrix_submatrix( _f, _size_x, 0, _size_y, _size_t );
	_f_yt = m_view.matrix;
	
	return 0;
}

int parameters :: transformation( const gsl_matrix * m )
{
	if ( m->size1 != _size_t	|| m->size2 != _size_t )
		return 1;


	gsl_matrix * m_bis = gsl_matrix_alloc( _size_t, _size_t );
	gsl_permutation * perm = gsl_permutation_alloc( _size_t );
	int toto;
	
	gsl_matrix_memcpy( m_bis, m );
	gsl_linalg_LU_decomp (m_bis, perm, &toto);
	if ( gsl_linalg_LU_det (m_bis, toto) == 0 )
	{
		gsl_matrix_free( m_bis );
		gsl_permutation_free( perm );
		return 1;
	}
	gsl_matrix * m_inv = gsl_matrix_alloc( _size_t, _size_t );
	gsl_linalg_LU_invert (	m_bis, 
							perm,
							m_inv ); // M inv
	

	gsl_matrix 	* tmp_sq_q0 = gsl_matrix_alloc( _size_t, _size_t ),
				* tmp_sq_q  = gsl_matrix_alloc( _size_t, _size_t ),
				* tmp_f     = gsl_matrix_alloc( _size_t, _size_t );
	gsl_vector  * tmp_t0    = gsl_vector_alloc( _size_t );
		
	//Calcul de Feq
	gsl_blas_dgemm( CblasNoTrans,
					CblasNoTrans,
					1.0,
					m,
					_f,
					0.0,
					m_bis );
	gsl_blas_dgemm( CblasNoTrans,
					CblasNoTrans,
					1.0,
					m_bis,
					m_inv,
					0.0,
					tmp_f );
	gsl_matrix_swap( _f, tmp_f );
	
	//Calcul de t0eq
	gsl_blas_dgemv( CblasNoTrans,
					1.0,
					m,
					_t_0,
					0.0,
					tmp_t0 );
	gsl_vector_swap( _t_0, tmp_t0 );
	
	//Calcul de Q0eq
	gsl_blas_dgemm( CblasNoTrans,
					CblasTrans,
					1.0,
					_sqrt_q_0,
					m,
					0.0,
					tmp_sq_q0 );			
					
	gsl_linalg_QR_decomp(	tmp_sq_q0,
							tmp_t0 );
	gsl_triangle_matrix( tmp_sq_q0 );		
	gsl_matrix_swap( _sqrt_q_0, tmp_sq_q0 );
	
			
	//Calcul de Qeq
	gsl_blas_dgemm( CblasNoTrans,
					CblasTrans,
					1.0,
					_sqrt_q,
					m,
					0.0,
					tmp_sq_q );			
					
	gsl_linalg_QR_decomp(	tmp_sq_q,
							tmp_t0 );
	gsl_triangle_matrix( tmp_sq_q );	
	gsl_matrix_swap( _sqrt_q, tmp_sq_q );
		
		
		
	//Lib. mémoire
	gsl_matrix_free( m_bis );
	gsl_permutation_free( perm );
	gsl_matrix_free( tmp_f );
	gsl_matrix_free( tmp_sq_q );
	gsl_matrix_free( tmp_sq_q0);
	gsl_vector_free( tmp_t0 );
	gsl_matrix_free( m_inv );
		
	update_q_0_and_q();	
	return 0;
}


void parameters :: reset()
{
	free();
	initialize();
}

parameters :: ~parameters()
{
	reset();
}

void parameters ::initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	_t_0 = 0;
	_sqrt_q_0 = 0;
	_f = 0;
	_sqrt_q = 0;
	_q_0 = 0;
	_q = 0;
}
void parameters ::free()
{
	if ( _t_0 )
		gsl_vector_free( _t_0 );
	if ( _sqrt_q_0 )
		gsl_matrix_free( _sqrt_q_0 );
	if ( _f )
		gsl_matrix_free( _f );
	if ( _sqrt_q )
		gsl_matrix_free( _sqrt_q );
	if ( _q )
		gsl_matrix_free( _q );
	if ( _q_0 )
		gsl_matrix_free( _q_0 );
}

void parameters :: alloc()
{
	_t_0 = gsl_vector_alloc( _size_t );
	_sqrt_q_0 = gsl_matrix_alloc( _size_t, _size_t );
	_sqrt_q = gsl_matrix_alloc( _size_t, _size_t );
	_f = gsl_matrix_alloc( _size_t, _size_t );
	_q = gsl_matrix_alloc( _size_t, _size_t );
	_q_0 = gsl_matrix_alloc( _size_t, _size_t );
}
void parameters ::  update_q_0_and_q()
{
	gsl_blas_dgemm( CblasTrans,
					CblasNoTrans,
					1.0,
					_sqrt_q,
					_sqrt_q,
					0.0,
					_q );
					
	gsl_blas_dgemm( CblasTrans,
					CblasNoTrans,
					1.0,
					_sqrt_q_0,
					_sqrt_q_0,
					0.0,
					_q_0 );
	
}
