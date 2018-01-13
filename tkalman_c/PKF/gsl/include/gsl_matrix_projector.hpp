#ifndef _GSL_MATRIX_PROJECTOR_HPP_
#define _GSL_MATRIX_PROJECTOR_HPP_
#include <gsl/gsl_matrix.h>


int gsl_matrix_projector(	gsl_matrix * mat,
							const unsigned int * row_ids );
							
int gsl_matrix_projector_transpose(	gsl_matrix * mat,
									const unsigned int * row_ids );
									

#endif
