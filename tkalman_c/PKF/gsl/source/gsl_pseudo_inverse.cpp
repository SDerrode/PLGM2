#include "gsl_pseudo_inverse.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

gsl_pseudo_inverse_workspace :: gsl_pseudo_inverse_workspace( unsigned int size ) throw ( exception & )
{
	initialize();
	if (!size)
		throw (invalid_argument( "Error: size == 0 in gsl_pseudo_inverse_workspace :: gsl_pseudo_inverse_workspace( unsigned int size )!") );
	_size = size;
	alloc();
}

gsl_pseudo_inverse_workspace ::  ~gsl_pseudo_inverse_workspace()
{
	free();
	initialize();
}

void gsl_pseudo_inverse_workspace :: initialize()
{
	_size = 0;
	_mat_1 = 0;
	_mat_2 = 0;
	_mat_3 = 0;
	_mat_4 = 0;
	_vect_1 = 0;
	_vect_2 = 0;
}

void gsl_pseudo_inverse_workspace :: free()
{
	if ( _mat_1 )
		gsl_matrix_free( _mat_1 );
	if ( _mat_2 )
		gsl_matrix_free( _mat_2 );
	if ( _mat_3 )
		gsl_matrix_free( _mat_3 );
	if ( _mat_4 )
		gsl_matrix_free( _mat_4 );
	if ( _vect_1 )
		gsl_vector_free( _vect_1 );
	if ( _vect_2 )
		gsl_vector_free( _vect_2 );
}

void gsl_pseudo_inverse_workspace :: alloc()
{
	_mat_1 = gsl_matrix_alloc( _size, _size );
	_mat_2 = gsl_matrix_alloc( _size, _size );
	_mat_3 = gsl_matrix_alloc( _size, _size );
	_mat_4 = gsl_matrix_alloc( _size, _size );
	
	_vect_1 = gsl_vector_alloc( _size );
	_vect_2 = gsl_vector_alloc( _size );
}

int gsl_pseudo_inverse( gsl_matrix * pseudo_inverse,
						const gsl_matrix * matrix,
						gsl_pseudo_inverse_workspace * w )
{
	gsl_pseudo_inverse_workspace * workspace;
	unsigned int size = 0;
	if ( !matrix || !pseudo_inverse )
		return -1;
		
	size = matrix->size1;
	if ( 	size != matrix->size2	||
			size != pseudo_inverse->size1	||
			size != pseudo_inverse->size2 )
		return 1;
	
	if ( !w )
		workspace = new gsl_pseudo_inverse_workspace( size );
	else
	{
		if ( w->size() != size )
			return 1;
		workspace = w;
	}
	
	gsl_matrix_memcpy( 	workspace->u(), 
						matrix );
	
	gsl_linalg_SV_decomp (workspace->u(), workspace->v(), workspace->sv(), workspace->vect_1());
	
	
	//Matrice des vp(i)^(-1) ou 0 si vp(i) == 0
	
	gsl_matrix_set_zero( workspace->inv_d() );
	for ( unsigned int i = 0; i < size; ++ i )
	{
		double vp = workspace->sv()->data[i * workspace->sv()->stride];
		if( vp != 0 )
			workspace->inv_d()->data[ workspace->inv_d()->tda * i + i ] = 1 / vp;
	}
	
	gsl_blas_dgemm( CblasTrans,
					CblasNoTrans,
					1.0,
					workspace->v(),
					workspace->inv_d(),
					0.0,
					workspace->mat_1() );
					
	gsl_blas_dgemm( CblasNoTrans,
					CblasTrans,
					1.0,
					workspace->inv_d(),
					workspace->u(),
					0.0,
					pseudo_inverse );
					
	if ( !w )
		delete workspace;
	
	return 0;
}
