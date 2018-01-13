#include "tkalman_q_estimation.hpp"
#include "gsl_triangle_matrix.hpp"
#include "gsl_matrix_projector.hpp"
#include "gsl_matrix_rank.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <cstring>
#include "tkalman_q_estimation_free_block.hpp"
#include "tkalman_q_estimation_known_block.hpp"
#include "tkalman_q_estimation_t2_block.hpp"
#include "tkalman_q_estimation_t3_block.hpp"
namespace tkalman
{
namespace q_estimation
{
	
estimator :: estimator ( void )
{
	initialize();
}

estimator :: estimator(	const gsl_matrix * sqrt_q_0,
						const gsl_matrix * p,
						unsigned int nb_blocks,
						const unsigned int * const * block_rows,
						const unsigned int * block_sizes,
						const unsigned int * block_hypotheses,
						const void * const * other_data ) throw (exception &)
{
	initialize();
	if ( setup (	sqrt_q_0,
					p,
					nb_blocks,
					block_rows,
					block_sizes,
					block_hypotheses,
					other_data ) )
		throw ( invalid_argument( "toto" ) ) ;
}

void estimator :: reset ( void )
{
	free();
	initialize();
}

int estimator :: setup (	const gsl_matrix * sqrt_q_0,
							const gsl_matrix * p,
							unsigned int nb_blocks,
							const unsigned int * const * block_rows,
							const unsigned int * block_sizes,
							const unsigned int * block_hypotheses,
							const void * const * other_data )
{
	reset();
	if ( 		! sqrt_q_0			||
				! p					||
				! nb_blocks			||
				! block_rows		||
				! block_sizes		||
				! block_hypotheses	||
				! other_data		)
		return -1;
	
	_sqrt_q_0 = sqrt_q_0;
	_p = p;
	_nb_blocks = nb_blocks;
	_block_rows = block_rows;
	_block_sizes = block_sizes;
	_block_hypotheses = block_hypotheses;
	_other_data = other_data;
	_size_t = _sqrt_q_0->size1;
	
	alloc();
	
	
	//Construction des objets
	for ( unsigned int i = 0; i < _nb_blocks; ++ i )
	{

		bool ok = true;
		if ( _block_sizes[i] == 0 )
			return 1;
		
		//Projecteur
		_projectors[i] = gsl_matrix_alloc( _block_sizes[i], _size_t );
		
		gsl_matrix_projector( 	_projectors[i],
								_block_rows[i] );
		//Sous matrice de bruit
		gsl_matrix 	*view_q = 
				gsl_matrix_alloc(	_block_sizes[i], 
									_block_sizes[i] );
									
		{
			gsl_matrix 	*tmp_mat = 
					gsl_matrix_alloc( 	_size_t,
										_block_sizes[i] );
			
			gsl_blas_dgemm( CblasNoTrans,
							CblasTrans,
							1.0,
							_sqrt_q_0,
							_projectors[i],
							0.0,
							tmp_mat );
							
			gsl_blas_dgemm( CblasNoTrans,
							CblasNoTrans,
							1.0,
							_projectors[i],
							tmp_mat,
							0.0,
							view_q );
							
			gsl_matrix_free( tmp_mat );
		}
		
		//Construction des paramètres
		switch(_block_hypotheses[i])
		{
			case(0): // Known block
			{
				//Function set
				_f_set[i] = known_block :: get_function_set();
				//Parameters allocation
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()( (const void*) ( _block_sizes + i ) );
				//Parameters setting
				if ( _f_set[i]->parameters_setting_function()( 	_block_parameters[i], 
																(const void*) view_q ) )
					ok = false;
					
			}
			break; 
			case(1): // Free block
			{
				free_block :: parameters_size p_size;
				//Function set
				_f_set[i] = free_block :: get_function_set();
				//Parameters allocation
				p_size.size_i = _block_sizes[i];
				p_size.size_t = _size_t;
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()( (void*) &p_size );
				//Parameters setting
				if ( _f_set[i]->parameters_setting_function()( 	_block_parameters[i], 
																NULL ) )
					ok = false;
				
			}
			break;
			case(2): // Q_i = \lambda S
			{
				t2_block :: parameters_size p_size;
				//Function set
				_f_set[i] = t2_block :: get_function_set();
				//Parameters allocation
				p_size.size_i = _block_sizes[i];
				p_size.size_t = _size_t;
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()( (void*) &p_size );
				//Parameters setting
				if ( _f_set[i]->parameters_setting_function()( 	_block_parameters[i], 
																(const void*) view_q ) )
					ok = false;
				
			}
			break;
			case(3): // ...
			{
				t3_block :: parameters_size p_size;
				//Function set
				_f_set[i] = t3_block :: get_function_set();
				//Parameters allocation
				p_size.size_i = _block_sizes[i];
				p_size.size_t = _size_t;
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()( &p_size );

				//Parameters setting
				if ( _f_set[i]->parameters_setting_function()( 	_block_parameters[i], 
																(const void*) other_data[i] ) )
					ok = false;

				
			}
			break;
			default:
				ok = false;
			break;

		}
		//Free
		gsl_matrix_free (view_q);
		
		if ( !ok )
			return 1;

		//estimator allocation
		_estimators[i] = _f_set[i]->estimator_allocation_function()( _block_parameters[i] );
		

	}
	

	return 0;
}

void estimator :: estimate(	gsl_matrix * sqrt_q,
							const gsl_matrix * f,
							const gsl_matrix * sqrt_sum,
							unsigned int nb_observations ) const
{
	//Calcul de F' = P^T F
	{
		gsl_blas_dgemm(	CblasTrans,
						CblasNoTrans,
						1.0,
						_p,
						f,
						0.0,
						w->f_eq() );
	}

	//Calcul de sq(C') = sq(C) [	I 	0
	//								0	P]
	{
		gsl_matrix_set_identity( w->mat_2t_2t_1() );
		gsl_matrix_memcpy(	w->mat_2t_2t_1_view_11(),
							_p );

		gsl_blas_dgemm(	CblasNoTrans,
						CblasNoTrans,
						1.0,
						sqrt_sum,
						w->mat_2t_2t_1(),
						0.0,
						w->sqrt_c_eq() );
		gsl_linalg_QR_decomp(	w->sqrt_c_eq(),
								w->vect_2t() );
		gsl_triangle_matrix( w->sqrt_c_eq() );
	}
	// sqrt_q = 0
	{
		gsl_matrix_set_zero( w->sqrt_q_eq() );
	}
	for ( unsigned int i = 0; i < _nb_blocks; ++ i )
	{
		gsl_matrix 	f_i = w->f_i( _block_sizes[i] ),
					sqrt_q_i = w->sqrt_q_i( _block_sizes[i] ),
					sqrt_c_i = w->sqrt_c_i( _block_sizes[i] );

		//F_i = P_i F_{eq}
		{
			gsl_blas_dgemm( CblasNoTrans,
							CblasNoTrans,
							1.0,
							_projectors[i],
							w->f_eq(),
							0.0,
							&f_i );
		}

		//sq(C_i)
		{
			gsl_matrix 	mat_2t_tpi_1 = w->mat_2t_tpi_1(_block_sizes[i]),
						mat_2t_tpi_1_view_00 = w->mat_2t_tpi_1_view_00(_block_sizes[i]),
						mat_2t_tpi_1_view_11 = w->mat_2t_tpi_1_view_11(_block_sizes[i]),
						sqrt_c_i_2t_tpi = w->sqrt_c_i_2t_tpi(_block_sizes[i]);
			gsl_vector vect_tpi = w->vect_tpi( _block_sizes[i] );
			//M
			gsl_matrix_set_zero
				( &mat_2t_tpi_1 );
			gsl_matrix_set_identity
				( &mat_2t_tpi_1_view_00 );
			gsl_matrix_transpose_memcpy
				( 	&mat_2t_tpi_1_view_11,
					_projectors[i] );
				
			//Product
			gsl_blas_dgemm( CblasNoTrans,
							CblasNoTrans,
							1.0,
							w->sqrt_c_eq(),
							&mat_2t_tpi_1,
							0.0,
							&sqrt_c_i_2t_tpi );
			
			//QR
			gsl_linalg_QR_decomp
				(	&sqrt_c_i_2t_tpi,
					&vect_tpi );
			gsl_triangle_matrix
				(&sqrt_c_i);

		}
		
		//Estimation
		{	
			_f_set[i]->f_estimation_function()( 	&sqrt_q_i,
													&f_i, 
													&sqrt_c_i,
													nb_observations,
													_estimators[i] );
		}
		//Ajout de Q
		{
			gsl_blas_dgemm( CblasNoTrans,
							CblasNoTrans,
							1.0,
							&sqrt_q_i,
							_projectors[i],
							0.0,
							&f_i );
			gsl_blas_dgemm( CblasTrans,
							CblasNoTrans,
							1.0,
							_projectors[i],
							&f_i,
							1.0,
							w->sqrt_q_eq() );
		}
	}
	{
		gsl_blas_dgemm(	CblasNoTrans,
						CblasTrans,
						1.0,
						w->sqrt_q_eq(),
						_p,
						0.0,
						sqrt_q );
		
		gsl_vector vect_t = w->vect_tpi(0);
		gsl_linalg_QR_decomp(	sqrt_q,
								&vect_t );
		gsl_triangle_matrix( sqrt_q );
	}
}

estimator :: ~estimator ( void )
{
	reset();
}

void estimator :: initialize()
{
	_size_t = 0;
	_sqrt_q_0 = 0;
	_p = 0;
	_nb_blocks = 0;
	_block_rows = 0;
	_block_sizes = 0;
	_block_hypotheses = 0;
	_other_data = 0;
	
	_block_parameters = 0;
	_f_set = 0;
	_estimators = 0;
	 _projectors = 0;

	w = 0;
	
}

void estimator :: free()
{
	if ( w ) 
		delete w;
	if ( _block_parameters )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _block_parameters[i] )
				_f_set[i]->parameters_freeing_function()( _block_parameters[i] );
		}
		delete[] _block_parameters;
	}
	

	if ( _estimators )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _estimators[i] )
				_f_set[i]->estimator_freeing_function()( _estimators[i] );
		}
		delete[] _estimators;
	}
	if ( _projectors )
	{
		for ( unsigned int i = 0; i < _nb_blocks; ++ i )
		{
			if ( _projectors[i] )
				gsl_matrix_free( _projectors[i] );
		}
		delete[] _projectors;
	}
	
	if ( _f_set )
	{
		delete[] _f_set;
	}
	
}

void estimator :: alloc()
{
	_block_parameters = new void*[_nb_blocks];
	memset(	_block_parameters, 
			0, 
			_nb_blocks * sizeof(void*));
	
	_f_set = new function_set*[_nb_blocks];
	memset(	_f_set, 
			0, 
			_nb_blocks * sizeof(function_set*));
	
	_estimators = new void*[_nb_blocks];
	memset(	_estimators, 
			0, 
			_nb_blocks * sizeof(void*));
	_projectors = new gsl_matrix*[_nb_blocks];
	memset(	_projectors, 
			0, 
			_nb_blocks * sizeof(gsl_matrix*));
			
	w = new q_estimation :: workspace( _size_t );
}


};

};
