#include "gsl_matrix_projector.hpp"

int gsl_matrix_projector(	gsl_matrix * mat,
							const unsigned int * row_ids)
{
	if (mat == NULL || ! row_ids )
		return -1;
		
	unsigned int size = mat->size1;
	gsl_matrix_set_zero(mat);
	for ( unsigned int i = 0; i < size; ++ i )
	{
		if ( row_ids[i] >= mat->size2 )
			return 2;
		mat->data[ i * mat->tda + row_ids[i]] = 1;
	}
	return 0;
}

int gsl_matrix_projector_transpose(	gsl_matrix * mat,
									const unsigned int * row_ids )
{
	if (mat == NULL || ! row_ids)
		return -1;
		
	unsigned int size = mat->size2;
	gsl_matrix_set_zero(mat);
	for ( unsigned int i = 0; i < size; ++ i )
	{
		if ( row_ids[i] >= mat->size1 )
			return 2;
		mat->data[ row_ids[i] * mat->tda + i ] = 1;
	}
	return 0;
}
