#include "tkalman_q_estimation_free_block_estimator.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <cmath>
#include "gsl_triangle_matrix.hpp"

#include <iostream>
using namespace std;

namespace tkalman
{
namespace q_estimation
{
namespace free_block
{
estimator :: estimator ( void )
{
	initialize();
}

estimator :: estimator ( unsigned int size_i,
						 unsigned int size_t) throw( exception &)
{
	initialize();
	if ( setup ( size_i, size_t ) )
		throw ( invalid_argument ( "Invalid argument : size == 0 in tkalman :: q_estimation :: free_block :: estimator :: estimator ( unsigned int size )!" ) );
	
}

int estimator :: setup(	unsigned int size_i,
						unsigned int size_t)
{
	reset();
	if ( size_i > size_t || size_t == 0 )
		return 1;
	_size_i = size_i;
	_size_t = size_t;

	alloc();
	return 0;
}

void estimator :: reset()
{
	free();
	initialize();
}

void estimator :: estimate (	gsl_matrix * sqrt_q,
								const gsl_matrix * f,
								const gsl_matrix * sqrt_c,
								unsigned int nb_observations ) const
{
	//Computing sq(C) [F^I; -I] 
		//[F, -I]
		//[n_i, n_t + n_i]
		gsl_matrix_memcpy( w->mat_i_tpi_view_F(), f );
	
	// (2n_t by n_t) - matrix
	
	gsl_blas_dgemm(	CblasNoTrans,
					CblasTrans,
					1.0,
					sqrt_c,
					w->mat_i_tpi(),
					0,
					w->mat_tpi_i() );
					
	// QR decomposition
	gsl_linalg_QR_decomp(w->mat_tpi_i(),
						 w->vect_i());
	gsl_triangle_matrix(w->mat_tpi_i());
				
	// V / sq(N+1)
	gsl_matrix_scale (	w->mat_tpi_i_view_00(),
						1.0 / sqrt( nb_observations) );
	// sq(Q) !! 
	gsl_matrix_memcpy(	sqrt_q, 
						w->mat_tpi_i_view_00() );
}

estimator :: ~estimator()
{
	reset();
}

void estimator :: free()
{
	if ( w )
		delete w;
}

void estimator :: alloc()
{
	w = new free_block :: workspace ( _size_i, _size_t );
}

void estimator :: initialize()
{
	w = 0;
	_size_i = 0;
	_size_t = 0;
}



};
};
};
