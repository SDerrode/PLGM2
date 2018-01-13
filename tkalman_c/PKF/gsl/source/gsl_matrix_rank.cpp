#include "gsl_matrix_rank.hpp"
#include <gsl/gsl_linalg.h>
unsigned int gsl_matrix_rank( const gsl_matrix * mat )
{
	if ( mat == NULL )
		return 0;
	
	gsl_matrix * tmp;
	
	if ( mat->size1 > mat->size2 )
	{
		tmp = gsl_matrix_alloc( mat->size1, 
										 mat->size2);
		gsl_matrix_memcpy( tmp, mat );
	}
	else
	{
		tmp = gsl_matrix_alloc( mat->size2, 
								mat->size1);
		gsl_matrix_transpose_memcpy( tmp, mat );
	}
	

	unsigned int size;
	if ( mat->size1 < mat->size2 )
		size = mat->size1;
	else
		size = mat->size2;
		
	gsl_vector * vect = gsl_vector_alloc( size );
	
	gsl_linalg_QR_decomp(	tmp,
							vect );
	
	unsigned int rk = 0;
	for ( unsigned int i = 0; i < size; ++ i )
	{
		if ( tmp->data[ i * (1 + tmp->tda) ] != 0 )
			rk ++;
	}
	
	gsl_matrix_free( tmp );
	gsl_vector_free( vect );
	
	return rk;
}
