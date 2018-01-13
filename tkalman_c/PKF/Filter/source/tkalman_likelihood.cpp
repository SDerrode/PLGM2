#include "tkalman_likelihood.hpp"
#include <gsl/gsl_blas.h>
#include <cmath>
#include "../../gsl/lib_PKF_gsl.hpp"
double tkalman :: pdf ( 	const gsl_vector * x,
							const gsl_vector * mean_x,
							const gsl_matrix * sqrt_var_x,
							gsl_vector * vect_x )
{
	return ( exp( 	tkalman :: log_pdf( 	x, 
										mean_x, 
										sqrt_var_x, 
										vect_x ) ) );
	
}
							
							
double tkalman :: log_pdf ( 	const gsl_vector * x,
								const gsl_vector * mean_x,
								const gsl_matrix * sqrt_var_x,
								gsl_vector * vect_x )
{
	//Calcul de log(|S|)^1/2
	double log_det = 0;
	for ( unsigned int i = 0; i < sqrt_var_x->size1; ++ i )
	{
		double v = sqrt_var_x->data[sqrt_var_x->tda * i + i ];
		if ( v < 0 )
			v = - v;
		log_det += log( v );
	}
	double n2 = 0;
	
	gsl_vector_memcpy(	vect_x,
						x );
	
	gsl_vector_sub(	vect_x, 
					mean_x );
	
	gsl_blas_dtrsv(	CblasUpper, 
					CblasNoTrans, 
					CblasNonUnit,
					sqrt_var_x,
					vect_x );
	
	gsl_blas_ddot( vect_x, vect_x, &n2 );
	
	return - 0.5 * ( 2 * log_det + n2 );
	
}
							
double tkalman :: log_likelihood( 	const gsl_vector * innovation,
									const gsl_matrix * sqrt_s,
									gsl_vector * vect_y )
{
	//Calcul de log(|S|)^1/2
	double log_det = 0;
	for ( unsigned int i = 0; i < sqrt_s->size1; ++ i )
	{
		double v = sqrt_s->data[sqrt_s->tda * i + i ];
		if ( v < 0 )
			v = - v;
		if ( v != 0 )
			log_det += log( v );
	}
	
	//Calcul de ||S^{-1/2}ý||²
	double n2 = 0;
	gsl_vector_memcpy( 	vect_y, 
						innovation );
	gsl_matrix * toto = gsl_matrix_alloc( sqrt_s->size1, sqrt_s->size1 );
	gsl_pseudo_inverse( toto, sqrt_s );
	gsl_blas_dtrsv(	CblasUpper, 
					CblasTrans, 
					CblasNonUnit,
					toto,
					vect_y );
	gsl_matrix_free(toto);
	gsl_blas_ddot( vect_y, vect_y, &n2 );
	
	
	return - 0.5 * ( 2 * log_det + n2 + 2 * sqrt_s->size1 * log( 2 * M_PI ) );
	
}

double tkalman :: likelihood( 	const gsl_vector * innovation,
								const gsl_matrix * sqrt_s,
								gsl_vector * vect_y )
{
	return exp ( 
		tkalman :: log_likelihood( 	innovation,
									sqrt_s,
									vect_y ) );
}
