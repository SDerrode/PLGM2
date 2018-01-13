#include "tkalman_q_estimation_t3_block_estimator.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "gsl_triangle_matrix.hpp"
#include <cmath>

namespace tkalman
{
namespace q_estimation
{
namespace t3_block
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
		throw ( invalid_argument( "Invalid argument in tkalman :: q_estimation :: t3_block :: estimator :: estimator ( const parameters * params )" ) );
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
	//0
	gsl_matrix_set_zero( sqrt_q );
	
	
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

	//W=0
	gsl_matrix_set_zero( w->mat_tpipb_b_view_00() );
	
	//Wn
	for ( unsigned int i = 0; i < p->nb_blocks(); ++ i )
	{

		//Cte Pi^T
		gsl_blas_dgemm(	CblasNoTrans,
						CblasTrans,
						1.0,
						w->mat_tpi_i_1(),
						p->projectors(i),
						0,
						w->mat_tpi_b_1() );
		gsl_blas_dgemm(	CblasNoTrans,
						CblasNoTrans,
						1.0,
						w->mat_tpi_b_1(),
						p->matrix_inverses(i),
						0,
						w->mat_tpipb_b_view_10() );
		
		//Decomposition QR
		gsl_linalg_QR_decomp(w->mat_tpipb_b(),
							 w->vect_b());
		gsl_triangle_matrix(w->mat_tpipb_b());
						
			
		
		
	}
	
	gsl_matrix_scale(	w->mat_tpipb_b_view_00(),
						1.0 / sqrt( p->nb_blocks() * (nb_observations ) ) );
		
	//Reconstruction des Q_i
	for ( unsigned int i = 0; i < p->nb_blocks(); ++ i )
	{
		//sq(Q_i) M_j^T
		gsl_blas_dgemm(	CblasNoTrans,
						CblasTrans,
						1.0,
						w->mat_tpipb_b_view_00(),
						p->matrices(i),
						0,
						w->mat_bb() );
		
		//QR
		gsl_linalg_QR_decomp(w->mat_bb() ,
							 w->vect_b());
		gsl_triangle_matrix(w->mat_bb() );
		//sq(Q_i) M_j^T P_j
		gsl_blas_dgemm(	CblasNoTrans,
						CblasNoTrans,
						1.0,
						w->mat_bb(),
						p->projectors(i),
						0,
						w->mat_bi() );
		
		//sq(Q_i) M_j^T P_j
		gsl_blas_dgemm(	CblasTrans,
						CblasNoTrans,
						1.0,
						p->projectors(i),
						w->mat_bi(),
						1.0,
						sqrt_q );
	}
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
	w = new tkalman :: q_estimation :: t3_block :: workspace (	p->size_i(), 
																p->size_t(), 
																p->size_block() );
}

};

};

};
