/**@file gsl_triangle_matrix.hpp
 * @author Valérian Némesin

**/

#ifndef GSL_TRIANGLE_MATRIX2_HPP_INCLUDED
#define GSL_TRIANGLE_MATRIX2_HPP_INCLUDED
	#include <gsl/gsl_matrix.h>
    /**\fn void gsl_triangle_matrix(gsl_matrix * matrix);
     * @param matrix : matrix
     * @brief
     This function transforms a matrix into an upper triangular matrix.
     */
    void gsl_triangle_matrix(gsl_matrix * matrix);

#endif // GSL_TRIANGLE_MATRIX_HPP_INCLUDED

