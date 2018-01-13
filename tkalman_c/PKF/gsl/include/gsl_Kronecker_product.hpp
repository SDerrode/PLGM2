#ifndef _GSL_KRONECKER_PRODUCT_HPP_
#define _GSL_KRONECKER_PRODUCT_HPP_
#include <gsl/gsl_matrix.h>
int gsl_Kronecker_product( 	gsl_matrix * prod, 
							const gsl_matrix * a, 
							const gsl_matrix * b );


#endif
