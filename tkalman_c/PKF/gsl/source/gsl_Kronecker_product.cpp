#include "gsl_Kronecker_product.hpp"
int gsl_Kronecker_product( 	gsl_matrix * prod, 
							const gsl_matrix * a, 
							const gsl_matrix * b )
{
	
	if ( 	prod->size1 != a->size1 * b->size1	||
			prod->size2 != a->size2 * b->size2  )
		return 1;
	
	
	for ( unsigned int i = 0; i < a->size1; ++ i )
	{
		for ( unsigned int j = 0; j < a->size2; ++ j )
		{
			gsl_matrix toto = gsl_matrix_submatrix( prod, i * b->size1, j * b->size2, b->size1, b->size2 ).matrix;
			gsl_matrix_memcpy( &toto, b );
			gsl_matrix_scale( &toto, a->data[ i * a->tda + j] );
		}
	}
	
	
	
	return 0;
}
