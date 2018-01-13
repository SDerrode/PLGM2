#include "Q_decorrelation_workspace.hpp"
using namespace equivalence;
Q_decorrelation_workspace :: Q_decorrelation_workspace( 	unsigned int size_x, 
															unsigned int size_y ) : tkalman :: workspace( size_x, size_y )
{
	Q_decorrelation_workspace :: initialize();
	
	//Alloc
	_mat_tt_1 = gsl_matrix_alloc( _size_t, _size_t );
	_mat_tt_2 = gsl_matrix_alloc( _size_t, _size_t );
	_mat_xx_1 = gsl_matrix_alloc( _size_x, _size_x );
	
	_vect_t_1 = gsl_vector_alloc( _size_t );
	_perm_x = gsl_permutation_alloc( _size_x );
	
	
	//Vues
	_mat_tt_1_xy = gsl_matrix_submatrix( _mat_tt_1, 0, _size_x, _size_x, _size_y ).matrix;
	_mat_tt_2_xx = gsl_matrix_submatrix( _mat_tt_2, 0, 0, _size_x, _size_x ).matrix;
	

}
Q_decorrelation_workspace :: ~Q_decorrelation_workspace()
{
	if ( _mat_tt_1 )	
		gsl_matrix_free( _mat_tt_1 );
		
	if ( _mat_tt_2 )
		gsl_matrix_free( _mat_tt_2 );
		
	if ( _mat_xx_1 )
		gsl_matrix_free( _mat_xx_1 );
		
	if ( _vect_t_1 )
		gsl_vector_free( _vect_t_1 );
	
	if ( _perm_x )
		gsl_permutation_free( _perm_x );

	Q_decorrelation_workspace :: initialize();
}

void Q_decorrelation_workspace :: initialize()
{
	_mat_tt_1 = 0;
	_mat_tt_2 = 0;
	_mat_xx_1 = 0;
	_vect_t_1 = 0;
	_perm_x = 0;
}


