#ifndef _TKALMAN_LIKELIHOOD_HPP_
#define _TKALMAN_LIKELIHOOD_HPP_
#include <gsl/gsl_matrix.h>
namespace tkalman
{
/**@fn double tkalman :: pdf ( 	const gsl_vector * x,
								const gsl_vector * mean_x,
								const gsl_matrix * sqrt_var_x,
								gsl_vector * vect_x );
 * @param x : observated x
 * @param mean_x : expectation of x
 * @param sqrt_var_x : sqrt of covariance matrix of x
 * @param vect_x : tmp vector
 * @brief
 * Gaussian pdf. 
 **/
double pdf ( 	const gsl_vector * x,
				const gsl_vector * mean_x,
				const gsl_matrix * sqrt_var_x,
				gsl_vector * vect_x );
				
/**@fn double tkalman :: pdf ( 	const gsl_vector * x,
								const gsl_vector * mean_x,
								const gsl_matrix * sqrt_var_x,
								gsl_vector * vect_x );
 * @param x : observated x
 * @param mean_x : expectation of x
 * @param sqrt_var_x : sqrt of covariance matrix of x
 * @param vect_x : tmp vector
 * @brief
 * Gaussian log pdf. 
 **/
double log_pdf ( 	const gsl_vector * x,
					const gsl_vector * mean_x,
					const gsl_matrix * sqrt_var_x,
					gsl_vector * vect_x );
					
/**@fn double tkalman :: log_likelihood( 	const gsl_vector * innovation,
											const gsl_matrix * sqrt_s,
											gsl_vector * vect_y );
 * @param innovation : innovation
 * @param sqrt_s : sqrt of covariance of innovation
 * @param vect_y : tmp vector
 * @brief
 * PK log-likelihood
 **/
double log_likelihood( 	const gsl_vector * innovation,
						const gsl_matrix * sqrt_s,
						gsl_vector * vect_y );
						
/**@fn double tkalman :: likelihood( 	const gsl_vector * innovation,
										const gsl_matrix * sqrt_s,
										gsl_vector * vect_y );
 * @param innovation : innovation
 * @param sqrt_s : sqrt of covariance of innovation
 * @param vect_y : tmp vector
 * @brief
 * PK likelihood
 **/
double likelihood( 	const gsl_vector * innovation,
					const gsl_matrix * sqrt_s,
					gsl_vector * vect_y );
};
#endif
