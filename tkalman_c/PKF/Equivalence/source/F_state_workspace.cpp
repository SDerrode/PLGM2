#include "F_state_workspace.hpp"
using namespace equivalence;
f_state_workspace :: f_state_workspace( 	unsigned int size_x, 
											unsigned int size_y )
: tkalman::workspace( size_x, size_y )
{
	initialize();
	_mat_tt_1 = gsl_matrix_alloc( _size_t, _size_t );
	_mat_xx_1 = gsl_matrix_alloc( _size_x, _size_x );
	_mat_tx_tx_1 = gsl_matrix_alloc( _size_x * _size_t, _size_x * _size_t );
	_mat_tx_tx_2 = gsl_matrix_alloc( _size_x * _size_t, _size_x * _size_t );
	_mat_xt_1 = gsl_matrix_alloc( _size_x, _size_t );
	_mat_xt_1_xy = gsl_matrix_submatrix( _mat_xt_1, 0, _size_x, _size_x, _size_y).matrix;
	_vect_xt_1 = gsl_vector_alloc( _size_x * _size_t );
	_vect_xt_2 = gsl_vector_alloc( _size_x * _size_t );
	_perm_xt = gsl_permutation_alloc( _size_x * _size_t );
	
}

f_state_workspace :: ~f_state_workspace()
{
	if ( _mat_tt_1 )
		gsl_matrix_free( _mat_tt_1 );
	if ( _mat_xx_1 )
		gsl_matrix_free( _mat_xx_1 );
	if ( _mat_tx_tx_1 )
		gsl_matrix_free( _mat_tx_tx_1 );
	if ( _mat_tx_tx_2 )
		gsl_matrix_free( _mat_tx_tx_2 );
	if ( _mat_xt_1 )
		gsl_matrix_free( _mat_xt_1 );
	if ( _vect_xt_1 )
		gsl_vector_free( _vect_xt_1 );
	if ( _vect_xt_2 )
		gsl_vector_free( _vect_xt_2 );
	if ( _perm_xt )
		gsl_permutation_free( _perm_xt );
	initialize();
}

void f_state_workspace :: initialize()
{
	_mat_tt_1 = 0;
	_mat_xx_1 = 0;
	_mat_tx_tx_1 = 0;
	_mat_tx_tx_2 = 0;
	_mat_xt_1 = 0;
	_vect_xt_1 = 0;
	_vect_xt_2 = 0;
	_perm_xt = 0;
	
}
