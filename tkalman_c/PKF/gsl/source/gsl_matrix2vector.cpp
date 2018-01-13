#include "gsl_matrix2vector.hpp"
int gsl_matrix2vector( 	gsl_vector * vect,
						const gsl_matrix * matrix )
{
	if ( vect->size != matrix->size1 * matrix->size2 )
		return 1;
	
	for ( unsigned int i = 0; i < matrix->size1; ++ i )
	{
		for ( unsigned int j = 0; j < matrix->size2; ++ j )
		{
			vect->data[ (i * matrix->size1 + j) * vect->stride ] = 
				matrix->data[ i * matrix->tda + j ];
		}
	}
	return 0;
}
