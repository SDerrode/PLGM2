#include "tkalman_q_estimation_t3_block_parameters.hpp"
#include "gsl_matrix_rank.hpp"
#include "gsl_matrix_projector.hpp"
#include <gsl/gsl_linalg.h>
using namespace tkalman;
using namespace q_estimation;
using namespace t3_block;

parameters :: parameters 
	( 	unsigned int size_i, 
		unsigned int size_t ) throw ( exception &)
{
	initialize();
	if ( 	size_i > size_t || 
			size_i == 0 	)
		throw ( invalid_argument("Invalid argument in tkalman :: q_estimation :: t2_block :: parameters :: parameters ( unsigned int size_i, unsigned int size_t)") );
	_size_i = size_i;
	_size_t = size_t;
}

int parameters :: set( 	const gsl_matrix * const * matrices,
						const unsigned int * const * row_ids,
						unsigned int nb_blocks,
						unsigned int block_sizes )
{

	if ( 	! matrices 		|| 
			! row_ids 		|| 
			!nb_blocks 		|| 
			!block_sizes )
		return -1;
	
	if ( nb_blocks * block_sizes != _size_i )
			return 1;
	
	//Verif des matrices
	for ( unsigned int i = 0; i < nb_blocks; ++ i )
	{
		//Verif de la dim
		if ( 	matrices[i]->size1 != block_sizes	||
				matrices[i]->size1 != block_sizes	)
			return 2;
		//Vérif du rang ( inversibilité)
		if ( gsl_matrix_rank ( matrices[i] ) != block_sizes )
			return 3;
	}
	
	//Pas de vérif sur les row ids ( construction inviolable si automatique sinon tu te démerdes! )
	
	//Lib mémorie
	if ( _inv_matrices )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _inv_matrices[i] )
				gsl_matrix_free ( _inv_matrices[i] );
		}
		delete[] _inv_matrices;
	}
	
	if ( _projectors )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _projectors[i] )
				gsl_matrix_free ( _projectors[i] );
		}
		delete[] _projectors;
	}
	

	_nb_blocks = nb_blocks;
	_size_block = block_sizes;
	_matrices = matrices;
	//Alloc mémoire
	_inv_matrices = new gsl_matrix*[_nb_blocks];
	_projectors = new gsl_matrix*[_nb_blocks];
	for (unsigned int i = 0; i < _nb_blocks; ++ i )
	{

		_inv_matrices[i] = gsl_matrix_alloc( _size_block, _size_block );
		{
			int Morpheus;
			gsl_matrix * mat_tmp = gsl_matrix_alloc( _size_block, _size_block );
			gsl_permutation * perm = gsl_permutation_alloc( _size_block );
			gsl_matrix_memcpy( 	mat_tmp, 
								_matrices[i] );  
								
			gsl_linalg_LU_decomp (	mat_tmp, 
									perm, 
									&Morpheus );
			gsl_linalg_LU_invert (	mat_tmp, 
									perm, 
									_inv_matrices[i] );
			gsl_matrix_free( mat_tmp );
			gsl_permutation_free( perm );
		}

		_projectors[i] = gsl_matrix_alloc( 	_size_block, 
											_size_t );
		gsl_matrix_projector(	_projectors[i],
								row_ids[i]);
	
	}

	return 0;
}

parameters :: ~parameters()
{
	free();
	initialize();
}

void parameters :: free()
{
	//Lib mémorie
	if ( _inv_matrices )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _inv_matrices[i] )
				gsl_matrix_free ( _inv_matrices[i] );
		}
		delete[] _inv_matrices;
	}
	
	if ( _projectors )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _projectors[i] )
				gsl_matrix_free ( _projectors[i] );
		}
		delete[] _projectors;
	}
	
	
}

void parameters :: initialize()
{
	_size_i = 0;
	_size_t = 0;
	_size_block = 0;
	_nb_blocks = 0;
	_matrices = 0;
	_inv_matrices = 0;
	_projectors = 0;
}
/**@fn
 * @param[in] i : 
 * @return
 * matrix #i
 * 
 **/
const gsl_matrix * parameters :: matrices( unsigned int i ) const
{
	if (i >_nb_blocks )
		return NULL;
		
	return _matrices[i];
}

/**@fn
 * @param[in] i : 
 * @return
 * inverse of matrix #i
 * 
 **/
const gsl_matrix *  parameters ::matrix_inverses( unsigned int i ) const
{
	if (i >_nb_blocks )
		return NULL;
		
	return _inv_matrices[i];
}

/**@fn
 * @param[in] i : 
 * @return
 * Projector #i
 * 
 **/
const gsl_matrix *  parameters ::projectors( unsigned int i ) const
{
	if (i >_nb_blocks )
		return NULL;
		
	return _projectors[i];
}
	
