#include "tkalman_constants_workspace.hpp"
using namespace tkalman;
constants_workspace :: constants_workspace( unsigned int size_x,
											unsigned int size_y ) throw( exception & )
: workspace ( size_x, size_y )
{
	initialize();
	alloc();
	//Création des vues
	gsl_matrix_view view;
	view = gsl_matrix_submatrix(_mat_tt,
								0,
								0,
								_size_y,
								_size_y);
	_mat_tt_yy = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_tt,
								0,
								_size_y,
								_size_y,
								_size_x);
	_mat_tt_yx = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_tt,
								_size_y,
								0,
								_size_x,
								_size_y);
	_mat_tt_xy = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_tt,
								_size_y,
								_size_y,
								_size_x,
								_size_x);
	_mat_tt_xx = view.matrix;
}

constants_workspace :: ~constants_workspace()
{
	free();
	initialize();
}

void constants_workspace :: free()
{
	if ( _mat_tt )
		gsl_matrix_free( _mat_tt );
	if ( _vect_t )
		gsl_vector_free( _vect_t );
	if ( _perm_y )
		gsl_permutation_free( _perm_y );
	if (  _psi_workspace )
		delete  _psi_workspace ;
}

void constants_workspace :: initialize()
{
	_mat_tt = 0;
	_vect_t = 0;
	_perm_y = 0;
	 _psi_workspace = 0;
}

void constants_workspace :: alloc()
{
	_mat_tt = gsl_matrix_alloc( _size_t, _size_t );
	_vect_t = gsl_vector_alloc( _size_t );
	_perm_y = gsl_permutation_alloc( _size_y );
	 _psi_workspace = new gsl_pseudo_inverse_workspace( _size_y );
}
