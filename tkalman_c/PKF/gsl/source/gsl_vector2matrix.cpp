#include "gsl_vector2matrix.hpp"
int gsl_vector2matrix( 	gsl_matrix * matrix,
						const gsl_vector * vect )
{
	if ( vect->size != matrix->size1 * matrix->size2 )
		return 1;
	
	for ( unsigned int i = 0; i < matrix->size1; ++ i )
	{
		for ( unsigned int j = 0; j < matrix->size2; ++ j )
		{
			matrix->data[ i * matrix->tda + j ] =
				vect->data[ (i * matrix->size1 + j) * vect->stride ];
		}
	}
	return 0;
}
