#include "tkalman_simulation.hpp"
#include <gsl/gsl_randist.h>
#include <gsl/gsl_blas.h>
#include <cmath>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <iostream>
#include "lib_PKF.hpp"
using namespace std;


tkalman_simualtion :: tkalman_simualtion( 	const gsl_vector * t0,
        const gsl_matrix * q0,
        const gsl_matrix * f,
        const gsl_matrix * q,
        gsl_rng * rng )
{
	initialize();
	setup( t0, q0, f, q, rng );
}

int tkalman_simualtion :: setup( 	const gsl_vector * t0,
                                    const gsl_matrix * q0,
                                    const gsl_matrix * f,
                                    const gsl_matrix * q,
                                    gsl_rng * rng )
{
	free();
	initialize();

	if ( ! t0 || ! q0 || ! f || ! q || ! rng )
		return 1;

	_size_t = t0->size;

	if (	q0->size1 != _size_t		||
	        q0->size2 != _size_t		||
	        q->size1 != _size_t		||
	        q->size2 != _size_t		||
	        f->size2 != _size_t					||
	        f->size1 != _size_t 			)
	{
		initialize();
		return 1;
	}

	_t_0 = t0;
	_q_0 = q0;
	_q = q;
	_f = f;
	_rng = rng;
	alloc();
	update_sqrts();



	return 0;
}

tkalman_simualtion :: ~tkalman_simualtion()
{
	free();
	initialize();
}

void tkalman_simualtion :: initialize()
{
	_t_0 = 0;
	_sqrt_q_0 = 0;
	_q_0 = 0;
	_q = 0;
	_f = 0;
	_sqrt_q = 0;
	_rng = 0;
	vect_t_2 = 0;
	_size_t = 0;
}
void tkalman_simualtion :: alloc()
{
	vect_t_2 = gsl_vector_alloc( _size_t );
	_sqrt_q = gsl_matrix_alloc( _size_t, _size_t);
	_sqrt_q_0 = gsl_matrix_alloc( _size_t, _size_t );
}

void tkalman_simualtion :: free()
{
	if ( vect_t_2 )
		gsl_vector_free( vect_t_2 );
	if ( _sqrt_q )
		gsl_matrix_free( _sqrt_q );
	if ( _sqrt_q_0 )
		gsl_matrix_free (_sqrt_q_0 );
}

int tkalman_simualtion :: update_sqrts()
{

	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (_size_t);
	gsl_matrix * q_cp = gsl_matrix_alloc( _size_t, _size_t );
	gsl_matrix * _p = gsl_matrix_alloc( _size_t, _size_t );
	gsl_vector * vp = gsl_vector_alloc( _size_t );

	//Recopie de q
	gsl_matrix_memcpy( q_cp, _q );

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


	gsl_matrix_memcpy( q_cp, _q_0 );

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

	return 0;
}

void tkalman_transition( 	gsl_vector * t,
                            const gsl_vector * _t,
                            const gsl_matrix * f,
                            const gsl_matrix * sqrt_q,
                            gsl_rng * rng,
                            gsl_vector * vect_t_2  )
{
	//Calcul de F T
	gsl_blas_dgemv(CblasNoTrans,
	               1.0,
	               f,
	               _t,
	               0.0,
	               t);

	//Bruit
	gaussian_rand ( 	t,
	                    t,
	                    sqrt_q,
	                    rng,
	                    vect_t_2 );
}

void do_tkalman_simulation(	gsl_vector ** t,
                            const gsl_vector * t0,
                            const gsl_matrix * sqrt_q0,
                            const gsl_matrix * f,
                            const gsl_matrix * sqrt_q,
                            const unsigned int n,
                            gsl_vector * vect_t_2,
                            gsl_rng * rng)
{
	//t0
	gaussian_rand (	t[0],
	                t0,
	                sqrt_q0,
	                rng,
	                vect_t_2 );

	//
	for ( unsigned int i = 1; i <= n; ++ i )
	{
		tkalman_transition(	t[i],
		                    t[i - 1],
		                    f,
		                    sqrt_q,
		                    rng,
		                    vect_t_2  );

	}
}





