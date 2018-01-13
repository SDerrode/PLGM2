#ifndef _GSL_MATRIX_TRACE_HPP_
#define _GSL_MATRIX_TRACE_HPP_
#include <gsl/gsl_matrix.h>
/**@fn int gsl_matrix_trace(	double & trace,
								const gsl_matrix * m );
 * @param[out] trace : trace
 * @param[in] m : square matrix
 * @return
 * - 1 -> no square matrix
 * - 0 -> OK 
 **/
int gsl_matrix_trace(	double & trace,
						const gsl_matrix * m );

#endif
