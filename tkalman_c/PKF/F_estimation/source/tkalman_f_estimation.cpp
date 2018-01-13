#include "tkalman_f_estimation.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include "gsl_triangle_matrix.hpp"
#include "gsl_matrix_projector.hpp"
#include "tkalman_f_estimation_t1_block.hpp"
#include "tkalman_f_estimation_t2_block.hpp"
#include "tkalman_f_estimation_known_block.hpp"
#include <cstring>
using namespace tkalman;
using namespace f_estimation;
estimator :: estimator ( void )
{
	initialize();
}

estimator :: estimator(	const gsl_matrix * f_0,
						const gsl_matrix * sqrt_q_0,
						unsigned int nb_blocks,
						const unsigned int * const * block_rows,
						const unsigned int * block_sizes,
						const unsigned int * block_hypotheses,
						const void * const * other_data ) throw (exception &)
{
	initialize();
	if ( setup(	f_0, 
				sqrt_q_0, 
				nb_blocks,
				block_rows,
				block_sizes,
				block_hypotheses,
				other_data ) )
		throw ( invalid_argument("Invalid argument(s) in f_estimation :: estimator") );
}


void estimator ::  reset ( void )
{
	free();
	initialize();
}


int estimator ::  setup(	const gsl_matrix * f_0,
							const gsl_matrix * sqrt_q_0,
							unsigned int nb_blocks,
							const unsigned int * const * block_rows,
							const unsigned int * block_sizes,
							const unsigned int * block_hypotheses,
							const void * const * other_data )
{
	reset();
	if (	! f_0 				|| 
			! sqrt_q_0 			|| 
			! nb_blocks 		||
			! block_rows		||
			! block_sizes		||
			! block_hypotheses	||
			! other_data		)
		return 1;
		
	_size_t = f_0->size1;
	
	
	_f_0 = f_0;
	_sqrt_q_0 = sqrt_q_0;
	_nb_blocks = nb_blocks;
	_block_rows = block_rows;
	_block_sizes = block_sizes;
	_block_hypotheses = block_hypotheses;
	_other_data = other_data;
	
	alloc();
	
	//Function sets
	for ( unsigned int i = 0; i < _nb_blocks; ++ i )
	{
		bool ok = true;
		if ( _block_sizes[i] == 0 )
			return 1;
		
		//Projecteur
		_projectors[i] = gsl_matrix_alloc( _block_sizes[i], _size_t );
		
		gsl_matrix_projector( 	_projectors[i],
								_block_rows[i] );
		
		switch(_block_hypotheses[i])
		{
			case(0): // Known block
			{
				//Function set
				_f_set[i] = known_block :: get_function_set();
				//Parameters allocation
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()(NULL);
				//Parameteers setting
				if ( _f_set[i]->parameters_setting_function()( _block_parameters[i], 
																NULL ) )
				{
			
					ok = false;
				}
			}
			break; 
			case(1): //F = M G
			{
				//Function set
				_f_set[i] = t1_block :: get_function_set();
				
				//Parameters allocation
				t1_block :: parameters_size sizes;
				sizes.size_i = _block_sizes[i];
				sizes.size_t = _size_t;
				sizes.size_g = ((const gsl_matrix*) other_data[i])->size1;
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()( (void*) &sizes );
				
				//Parameteers setting
				t1_block :: parameters_data data;
				data.m = (const gsl_matrix*) other_data[i];
				
				if ( _f_set[i]->parameters_setting_function()( 	_block_parameters[i], 
																(const void*) &data ) )
				{
					ok = false;
				}
			}
			break;
			case(2): //F= \sum_i \lambda_i M_i
			{
				//Function set
				_f_set[i] = t2_block :: get_function_set();
				
				//Parameters allocation
				t2_block :: parameters_size sizes;
				sizes.size_i = _block_sizes[i];
				sizes.size_t = _size_t;
				sizes.size_lambda = ((const t2_block :: file_data *) other_data[i])->size_lambda;
				_block_parameters[i] = _f_set[i]->parameters_allocation_function()( (void*) &sizes );
				
				//Parameteers setting
				t2_block :: parameters_data data;
				data.m = ( (const t2_block :: file_data *) other_data[i] )->m;
				if ( _f_set[i]->parameters_setting_function()(	 _block_parameters[i], 
																(const void*) &data ) )
					ok = false;

			}
			break;
			default:
				ok = false;
			break;
		}
		if ( !ok )
			return 1;
		//estimator allocation
		_estimators[i] = _f_set[i]->estimator_allocation_function()( _block_parameters[i] );
	}
	return 0;
	
}

void estimator :: estimate(	gsl_matrix * f,
							const gsl_matrix * sqrt_sum,
							const gsl_matrix * _sqrt_q ) const
{
	//1. F' = F - F0
	// C -> Cb
	gsl_matrix_set_identity( w->mat_2t_2t_1() );
	gsl_matrix_transpose_memcpy( w->mat_2t_2t_1_view_01(),
								 _f_0 );
	gsl_matrix_scale( w->mat_2t_2t_1_view_01(), -1);
	gsl_blas_dgemm(	CblasNoTrans,
					CblasNoTrans,
					1.0,
					sqrt_sum,
					w->mat_2t_2t_1(),
					0.0,
					w->sqrt_c_bis() );
	gsl_linalg_QR_decomp(	w->sqrt_c_bis(),
							w->vect_2t() );
	gsl_triangle_matrix(w->sqrt_c_bis());


	for ( unsigned int i = 0; i < _nb_blocks; ++ i )
	{

		gsl_matrix sq_cb = w->sqrt_sum(_block_sizes[i]),
				   sq_cb_2t_tpi = w->sqrt_sum_mat_2t_tpi(_block_sizes[i]),
				   *sq_cb_00 = w->sqrt_sum_00(),
				   sq_cb_01 = w->sqrt_sum_01(_block_sizes[i]);
		//2. F' -> Fi
		// Cb -> Cb(i)
		gsl_matrix 	m = w->m(_block_sizes[i]),
					*m_00 = w->mat_2t_2t_1_view_00(),
					m_11 = w->m_view_11(_block_sizes[i]);
					
			//Construction de M
				gsl_matrix_set_zero( &m );
				gsl_matrix_set_identity( m_00 );
		
				//Construction du projecteur
				gsl_matrix_projector_transpose( &m_11, 
												_block_rows[i]);
		
			//Produit + QR
			{
				gsl_blas_dgemm(	CblasNoTrans,
								CblasNoTrans,
								1.0,
								w->sqrt_c_bis(),
								&m,
								0.0,
								&sq_cb_2t_tpi );
				gsl_vector v = w->vect(_block_sizes[i]);
				gsl_linalg_QR_decomp(	&sq_cb_2t_tpi,
										&v );
				gsl_triangle_matrix(&sq_cb);

			}
		

		//2.bis Q_i //Hypothèse 2 dans le cadre d'un GEM
		gsl_matrix	mat_ti = w->mat_ti(_block_sizes[i]),
					sqrt_q_i = w->sqrt_q_i(_block_sizes[i]);
		gsl_vector  vect_i = w->s_vect(_block_sizes[i]);
		
		
		gsl_blas_dgemm( CblasNoTrans,
						CblasNoTrans,
						1.0,
						_sqrt_q,
						&m_11,
						0.0,
						&mat_ti );
		gsl_linalg_QR_decomp(	&mat_ti,
								&vect_i );
		gsl_triangle_matrix(&mat_ti);
		
		//3. F_i
		gsl_matrix _f_i = w->f(_block_sizes[i]);
		_f_set[i]->f_estimation_function()( 	&_f_i, 
												sq_cb_00,
												&sq_cb_01,
												_estimators[i],
												&sqrt_q_i );
		//4. Stockage
		for ( unsigned int j = 0; j < _block_sizes[i]; ++ j )
		{
			memcpy(	f->data + _block_rows[i][j] * f->tda,
					_f_i.data + j * _f_i.tda,
					sizeof( double ) * _size_t );
		}
	}
	//5. F = F' + F0
	gsl_matrix_add(	f, 
					_f_0 );
}



estimator :: ~estimator ( void )
{
	free();
	initialize();
}


void estimator :: initialize()
{
	_size_t = 0;
	_f_0 = 0;
	_sqrt_q_0 = 0;
	_nb_blocks = 0;
	_block_rows = 0;
	_block_sizes = 0;
	_block_hypotheses = 0;
	_other_data = 0;
	_block_parameters = 0;
	_f_set = 0;
	_estimators = 0;
	w = 0;
	_projectors = 0;
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
			
	w = new f_estimation :: workspace( _size_t );
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

