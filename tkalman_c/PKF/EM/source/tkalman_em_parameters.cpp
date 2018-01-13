#include "tkalman_em_parameters.hpp"
#include <gsl/gsl_blas.h>
#include <cstring>
namespace tkalman
{
namespace EM
{
parameters :: parameters( void )
{
	initialize();
}

parameters :: parameters(	const gsl_matrix * f_0,
							const gsl_matrix * sqrt_q_0,
							const gsl_matrix * p,
							unsigned int size_x,
							unsigned int nb_f_blocks,
							unsigned int nb_q_blocks,
							const unsigned int * f_block_sizes,
							const unsigned int * q_block_sizes,
							const unsigned int * const * f_block_row_ids,
							const unsigned int * const * q_block_row_ids,
							const unsigned int * f_block_hypotheses,
							const unsigned int * q_block_hypotheses,
							const void * const * f_other_data,
							const void * const * q_other_data,
							bool first_state_estimation )
{
	initialize();
	setup( 	f_0, 
			sqrt_q_0, 
			p, 
			size_x,
			nb_f_blocks, 
			nb_q_blocks, 
			f_block_sizes, 
			q_block_sizes,
			f_block_row_ids,
			q_block_row_ids,
			f_block_hypotheses,
			q_block_hypotheses,
			f_other_data,
			q_other_data,
			first_state_estimation );
}
	
void parameters :: reset()
{
	initialize();
}

int parameters :: setup(	const gsl_matrix * f_0,
							const gsl_matrix * sqrt_q_0,
							const gsl_matrix * p,
							unsigned int size_x,
							unsigned int nb_f_blocks,
							unsigned int nb_q_blocks,
							const unsigned int * f_block_sizes,
							const unsigned int * q_block_sizes,
							const unsigned int * const * f_block_row_ids,
							const unsigned int * const * q_block_row_ids,
							const unsigned int * f_block_hypotheses,
							const unsigned int * q_block_hypotheses,
							const void * const * f_other_data,
							const void * const * q_other_data,
							bool first_state_estimation )
{
	initialize();
	
	if ( 	!f_0 					|| 
			!sqrt_q_0 				|| 
			!p 						|| 
			!size_x					||
			!nb_f_blocks 			||
			!nb_q_blocks			||
			!f_block_sizes			||
			!q_block_sizes			||
			!f_block_row_ids		||
			!q_block_row_ids		||
			!f_block_hypotheses		||
			!q_block_hypotheses		||
			!f_other_data			||
			!q_other_data			)
		return 1;
		
	unsigned int size_t = f_0->size1;
	
	if ( 	f_0->size2 		!= size_t	||
			sqrt_q_0->size1	!= size_t	||
			sqrt_q_0->size2 != size_t	||
			p->size1		!= size_t	||
			p->size2		!= size_t	)
		return 1;

	//Somme des dimensions des blokcs
	{
		unsigned int s = 0;
		for ( unsigned int i = 0; i < nb_f_blocks; ++ i )
		{
			s += f_block_sizes[i];
		}
		if ( s != size_t )
			return 1;
	}
	{
		unsigned int s = 0;
		for ( unsigned int i = 0; i < nb_q_blocks; ++ i )
		{
			s += q_block_sizes[i];
		}
		if ( s != size_t )
			return 1;
	}

	//Vérif des row_ids
	{
		for ( unsigned int i = 0; i < nb_f_blocks; ++ i )
		{
			for ( unsigned int j = 0; j < f_block_sizes[i]; ++ j)
			{
				if ( f_block_row_ids[i][j] >= size_t )
					return 1;
			}
		}
	}
	{
		for ( unsigned int i = 0; i < nb_q_blocks; ++ i )
		{
			for ( unsigned int j = 0; j < q_block_sizes[i]; ++ j)
			{
				if ( q_block_row_ids[i][j] >= size_t )
					return 1;
			}
		}
	}

	
	_size_t = size_t;
	_size_x = size_x;
	_size_y = size_t - size_x;
	_f_0 = f_0;
	_sqrt_q_0 = sqrt_q_0;
	_p = p;
	_size_x = size_x;
	_nb_f_blocks = nb_f_blocks;
	_nb_q_blocks = nb_q_blocks;
	_f_block_sizes = f_block_sizes;
	_q_block_sizes = q_block_sizes;
	_f_block_row_ids = f_block_row_ids;
	_q_block_row_ids = q_block_row_ids;
	_f_block_hypotheses = f_block_hypotheses;
	_q_block_hypotheses = q_block_hypotheses;
	_f_other_data = f_other_data;
	_q_other_data = q_other_data;
	_first_state_estimation	= first_state_estimation;
	safe = true;
	return 0;
}

parameters :: ~parameters()
{
	initialize();
}
	
void parameters :: initialize()
{
	_size_t = 0;
	_size_x = 0;
	_size_y = 0;
	_f_0 = 0;
	_sqrt_q_0 = 0;
	_p = 0;
	_size_x = 0;
	_nb_f_blocks = 0;
	_nb_q_blocks = 0;
	_f_block_sizes = 0;
	_q_block_sizes = 0;
	_f_block_row_ids = 0;
	_q_block_row_ids = 0;
	_f_block_hypotheses = 0;
	_q_block_hypotheses = 0;
	_f_other_data = 0;
	_first_state_estimation = false;
	_q_other_data = 0;
	safe = false;
}
	
	
};
};


