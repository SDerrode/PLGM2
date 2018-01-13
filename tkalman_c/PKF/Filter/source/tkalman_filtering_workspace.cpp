#include "tkalman_filtering_workspace.hpp"
using namespace tkalman;
filtering_workspace :: filtering_workspace ( 	unsigned int size_x, 
												unsigned int size_y ) throw( exception & )
: workspace ( size_x, size_y )
{
	initialize();
	alloc();
	gsl_matrix_view view;
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								0,
								0,
								_size_t,
								_size_t);
	_mat_tt = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								0,
								0,
								_size_y,
								_size_y);
	_mat_tt_view_00 = view.matrix;
	_mat_tpy_tpy_view_00 = view.matrix;
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								_size_y,
								0,
								_size_t,
								_size_y);
	_mat_tpy_tpy_view_10 = view.matrix;
	
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								0,
								_size_y,
								_size_y,
								_size_t);
	_mat_tpy_tpy_view_01 = view.matrix;
	
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								_size_y,
								_size_y,
								_size_t,
								_size_t);
	_mat_tpy_tpy_view_11 = view.matrix;
	
	
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								_size_y,
								0,
								_size_x,
								_size_y);
	_mat_tt_view_10 = view.matrix;
	
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								0,
								_size_y,
								_size_y,
								_size_x);
	_mat_tt_view_01 = view.matrix;
	
	
	view = gsl_matrix_submatrix(_mat_tpy_tpy,
								_size_y,
								_size_y,
								_size_x,
								_size_x);
	_mat_tt_view_11 = view.matrix;
	
	
	view = gsl_matrix_submatrix(_mat_ty,
								0,
								0,
								_size_x,
								_size_y);
	_mat_xy = view.matrix;
	
	
	gsl_vector_view view2 = gsl_vector_subvector(_vect_tpy, 0, _size_t);
	
	_vect_t = view2.vector;
	
}

filtering_workspace :: ~filtering_workspace()
{
	free();
	initialize();
}

void filtering_workspace :: free()
{
	if ( _mat_tpy_tpy ) 
		gsl_matrix_free(_mat_tpy_tpy);
	if ( _mat_ty )
		gsl_matrix_free( _mat_ty );
	if ( _perm_y )
		gsl_permutation_free ( _perm_y );
	if ( _vect_tpy )
		gsl_vector_free ( _vect_tpy );
	if (  _psi_workspace )
		delete  _psi_workspace ;
}

void filtering_workspace :: initialize()
{

	_mat_tpy_tpy = 0;
	_mat_ty = 0;
	_perm_y = 0;
	_vect_tpy = 0;
	 _psi_workspace = 0;
}

void filtering_workspace :: alloc()
{
	_mat_tpy_tpy = gsl_matrix_alloc( 	_size_t + _size_y, 
										_size_t + _size_y );
	_mat_ty = gsl_matrix_alloc(	_size_t, 
								_size_y );
	_perm_y = gsl_permutation_alloc( _size_y );
	_vect_tpy = gsl_vector_alloc( _size_t + _size_y );
	_psi_workspace = new gsl_pseudo_inverse_workspace( _size_y );
}
