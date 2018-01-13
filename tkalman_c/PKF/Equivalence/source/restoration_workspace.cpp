#include "restoration_workspace.hpp"
using namespace equivalence;

restoration_workspace :: restoration_workspace( 	unsigned int size_x, 
						unsigned int size_y ) 
:tkalman::workspace(size_x, size_y)
{
	restoration_workspace :: initialize();
	
	_mat_xx_1 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_xx_2 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_xx_3 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_xx_4 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_xx_5 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_xx_6 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_xx_7 = gsl_matrix_alloc( _size_x, _size_x );

	_mat_xy_1 = gsl_matrix_alloc( _size_x, _size_y );
	_vect_y_1 = gsl_vector_alloc( _size_y );
	_perm_x = gsl_permutation_alloc( _size_x );
	
	_mat_xx_1_xy = gsl_matrix_submatrix( _mat_xx_1, 0, 0, _size_x, _size_y ).matrix;
	_mat_xx_2_xy = gsl_matrix_submatrix( _mat_xx_2, 0, 0, _size_x, _size_y ).matrix;
	_mat_yy_1 = gsl_matrix_submatrix( _mat_xy_1, 0, 0, _size_y, _size_y ).matrix;
}

restoration_workspace :: ~restoration_workspace()
{
	if ( _mat_xx_1 )
		gsl_matrix_free( _mat_xx_1 );
	if ( _mat_xx_2 )
		gsl_matrix_free( _mat_xx_2 );		
	if ( _mat_xx_3 )
		gsl_matrix_free( _mat_xx_3 );		
	if ( _mat_xx_4 )
		gsl_matrix_free( _mat_xx_4 );	
	if ( _mat_xx_5 )
		gsl_matrix_free( _mat_xx_5 );
	if ( _mat_xx_6 )
		gsl_matrix_free( _mat_xx_6 );
	if ( _mat_xx_7 )
		gsl_matrix_free( _mat_xx_7 );
	if ( _mat_xy_1 )
		gsl_matrix_free( _mat_xy_1 );
		
	if ( _vect_y_1 )
		gsl_vector_free ( _vect_y_1 );
	if ( _perm_x )
		gsl_permutation_free ( _perm_x );
	restoration_workspace :: initialize();
}

void restoration_workspace :: initialize()
{
	_mat_xx_1 = 0;
	_mat_xx_2 = 0;
	_mat_xx_3 = 0;
	_mat_xx_4 = 0;
	_mat_xx_5 = 0;
	_mat_xx_6 = 0;
	_mat_xx_7 = 0;
	_mat_xy_1 = 0;
	_vect_y_1 = 0;
	_perm_x = 0;
	
}
