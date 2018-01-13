#include "tkalman_f_estimation_t2_block_workspace.hpp"

tkalman :: f_estimation :: t2_block :: workspace :: workspace
	( 	unsigned int size_i,
		unsigned int size_t,
		unsigned int size_lambda )
: tkalman :: workspace( size_i, size_t - size_i)
{
	tkalman :: f_estimation :: t2_block :: workspace :: initialize();
	_size_lambda = size_lambda;
	_v_it = new gsl_matrix*[_size_lambda];
	
	for ( unsigned int i = 0; i < _size_lambda; ++ i )
	{
		_v_it[i] = gsl_matrix_alloc( 	_size_x, 
										_size_t );
	}
	
	_mat_it = gsl_matrix_alloc(	_size_x, 
								_size_t );
	
	_mat_ii = gsl_matrix_alloc(	_size_x, 
								_size_x );
	
	_mat_ii_2 = gsl_matrix_alloc( _size_x, _size_x );
	_perm_i	= gsl_permutation_alloc( _size_x);
	gsl_permutation_init(_perm_i);
	
	
	_mat_lambda_lambda = gsl_matrix_alloc( 	_size_lambda,
											_size_lambda );
											
	_vect_lambda = gsl_vector_alloc( _size_lambda );
	_lambda = gsl_vector_alloc( _size_lambda );
}

tkalman :: f_estimation :: t2_block :: workspace :: ~workspace()
{
	if ( _mat_it )
		gsl_matrix_free( _mat_it );
	if ( _mat_ii )
		gsl_matrix_free( _mat_ii );
	if ( _mat_ii_2 )
		gsl_matrix_free( _mat_ii_2 );
	if ( _perm_i )
		gsl_permutation_free( _perm_i );
	if ( _mat_lambda_lambda )
		gsl_matrix_free( _mat_lambda_lambda );
	if ( _vect_lambda )
		gsl_vector_free( _vect_lambda );
	if ( _lambda)
		gsl_vector_free( _lambda );
	if ( _v_it )
	{
		for ( unsigned int i = 0; i < _size_lambda; ++ i )
		{
			if ( _v_it[i] )
				gsl_matrix_free( _v_it[i] );
		}
		delete[] _v_it;
	}
	tkalman :: f_estimation :: t2_block :: workspace :: initialize();
}

void tkalman :: f_estimation :: t2_block :: workspace :: initialize()
{
	_size_lambda = 0;
	_v_it = 0; // V_i^j
	_mat_it = 0;
	_mat_ii = 0;
	_mat_ii_2 = 0;
	_perm_i = 0;
	_mat_lambda_lambda = 0; //A_i
	_vect_lambda = 0; // B
	_lambda = 0;
}
