#include "tkalman_f_estimation_t2_block_estimator.hpp"
#include "gsl_matrix_trace.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "gsl_triangle_matrix.hpp"
tkalman :: f_estimation :: t2_block :: estimator :: estimator()
{
	initialize();
}

tkalman :: f_estimation :: t2_block :: estimator :: estimator( const t2_block :: parameters * params ) throw ( exception &)
{
	initialize();
	if ( setup ( params ) )
		throw ( invalid_argument( "Invalid argument(s) in t2_block :: t2_block!") );
}

void tkalman :: f_estimation :: t2_block :: estimator :: reset()
{
	free();
	initialize();
}

int tkalman :: f_estimation :: t2_block :: estimator :: setup (	const tkalman :: f_estimation :: t2_block :: parameters * params  )
{
	reset();
	if ( params == NULL )
		return 1;
	p = params;
	if ( p->size_lambda() == 0 )
		return 0;
	else
	{
		alloc();
	}
	return 0;
}

void tkalman :: f_estimation :: t2_block :: estimator ::  estimate
	( 	gsl_matrix * f_i,
		const gsl_matrix * sqrt_c_i_view_00,
		const gsl_matrix * sqrt_c_i_view_01,
		const gsl_matrix * sqrt_q_i ) const
{
	gsl_matrix_set_zero( f_i );
	//Rien à faire ici!
	if ( p->size_lambda() == 0 )
		return;

	//0. Calcul de sqrt_q_i^{-1}
		//Test de l'inversabilité
		for ( unsigned int i = 0; i < sqrt_q_i->size1; ++ i )
		{
			if (sqrt_q_i->data[ i * ( 1 + sqrt_q_i->tda) ] == 0 )
				return;
		}

		//Inversion de Q_0^i
		{
			gsl_linalg_LU_invert (	sqrt_q_i, 
									w->perm_i(), 
									w->inv_sqrt_qi() );
		}
		

	//A. Calcul des V_i^k
	for ( unsigned int i = 0; i < p->size_lambda(); ++ i )
	{
		
		gsl_blas_dgemm(	CblasNoTrans, 
						CblasTrans,
						1.0,
						p->m()[i],
						sqrt_c_i_view_00,
						0.0,
						w->mat_it() );

		gsl_blas_dgemm(	CblasTrans, 
						CblasNoTrans,
						1.0,
						w->inv_sqrt_qi(),
						w->mat_it(),
						0.0,
						w->v_it(i) );

	}

	//B. Construction de A_i
	for ( unsigned int i = 0; i < p->size_lambda(); ++ i )
	{
		for ( unsigned int j = i; j < p->size_lambda(); ++ j )
		{
			gsl_blas_dgemm(	CblasNoTrans, 
							CblasTrans,
							1.0,
							w->v_it(i),
							w->v_it(j),
							0.0,
							w->mat_ii() );
			//Trace
			double tr = 0;
			gsl_matrix_trace( tr, w->mat_ii() );
				
			w->mat_lambda_lambda()->data[i * w->mat_lambda_lambda()->tda + j] = tr;
			w->mat_lambda_lambda()->data[j * w->mat_lambda_lambda()->tda + i] = tr;
		}
	}
	
	//C. Inversion de A_i
	gsl_linalg_cholesky_decomp ( w->mat_lambda_lambda() );
	gsl_linalg_cholesky_invert ( w->mat_lambda_lambda() );
	
	//D. Calcul de B_i
	for ( unsigned int i = 0; i < p->size_lambda(); ++ i )
	{
			gsl_blas_dgemm(	CblasNoTrans, 
							CblasNoTrans,
							1.0,
							w->inv_sqrt_qi(),
							w->v_it(i),
							0.0,
							w->mat_it() );
							
			gsl_blas_dgemm(	CblasNoTrans, 
							CblasNoTrans,
							1.0,
							w->mat_it(),
							sqrt_c_i_view_01,
							0.0,
							w->mat_ii() );
			//Trace
			double tr = 0;
			gsl_matrix_trace( tr, w->mat_ii() );
				
			w->vect_lambda()->data[i * w->vect_lambda()->stride] = tr;
	}
	
	//E. lambda_i = A_i^-1 B_i
	gsl_blas_dgemv(	CblasNoTrans, 
					1.0, 
					w->mat_lambda_lambda(),
					w->vect_lambda(),
					0.0,
					w->lambda() );
	
	//F. F_i
	for ( unsigned int i = 0; i < p->size_lambda(); ++ i )
	{
		gsl_matrix_memcpy(	w->mat_it(), 
							p->m()[i]);
		gsl_matrix_scale ( 	w->mat_it(), 
							w->lambda()->data[i * w->lambda()->stride] );
		gsl_matrix_add( f_i, w->mat_it() );
	}
}

tkalman :: f_estimation :: t2_block :: estimator :: ~estimator()
{
	reset();
}

void tkalman :: f_estimation :: t2_block :: estimator :: free()
{
	if (w)
		delete w;
}

void tkalman :: f_estimation :: t2_block :: estimator :: alloc()
{
	w = new t2_block :: workspace( 	p->size_i(),
									p->size_t(), 
									p->size_lambda() );
}

void tkalman :: f_estimation :: t2_block :: estimator :: initialize()
{
	p = 0;
	w = 0;
}
