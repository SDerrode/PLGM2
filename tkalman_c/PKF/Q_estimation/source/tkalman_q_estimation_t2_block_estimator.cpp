#include "tkalman_q_estimation_t2_block_estimator.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <cmath>
#include "gsl_matrix_trace.hpp"
namespace tkalman
{
namespace q_estimation
{
namespace t2_block
{
estimator :: estimator ( void )
{
	initialize();
}

estimator :: estimator ( const parameters * params ) throw( exception &)
{
	initialize();
	if ( setup( params ) )
	{
		throw ( invalid_argument( "Invalid argument in tkalman :: q_estimation :: t2_block :: estimator :: estimator ( const parameters * params )" ) );
	}
}

int estimator :: setup( const parameters * params )
{
	if ( ! params )
		return 1;
		
	p = params;
	alloc();
	return 0;
}

void estimator :: reset()
{
	free();
	initialize();
}

void estimator :: estimate ( 	gsl_matrix * sqrt_q,
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
					w->mat_tpi_i_1() );
	
	//sq(C) [F^I; -I] [Q^{\frac{1}{2}}]^{-1}
	gsl_blas_dgemm(	CblasNoTrans,
					CblasNoTrans,
					1.0,
					w->mat_tpi_i_1(),
					p->inv_sqrt_q(),
					0,
					w->mat_tpi_i_2() );
	
	gsl_blas_dgemm(	CblasTrans,
					CblasNoTrans,
					1.0,
					w->mat_tpi_i_2(),
					w->mat_tpi_i_2(),
					0,
					w->mat_ii() );
	double lambda;

	gsl_matrix_trace(lambda, w->mat_ii() );
	
	gsl_matrix_memcpy( sqrt_q, p->sqrt_q() );
	gsl_matrix_scale( sqrt_q, sqrt( lambda / ( ( nb_observations) * p->size_i())  ) );
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

void estimator :: initialize()
{
	w = 0;
	p = 0;
} 

void estimator :: alloc()
{
	w = new tkalman :: q_estimation :: t2_block :: workspace ( p->size_i(), p->size_t() );
}

};

};

};
