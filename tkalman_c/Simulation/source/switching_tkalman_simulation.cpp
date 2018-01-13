#include "switching_tkalman_simulation.hpp"
#include "tkalman_simulation.hpp"

switching_tkalman_simulation :: switching_tkalman_simulation( 	const gsl_vector * t_0,
																const gsl_matrix * sqrt_q_0,
																const gsl_matrix * const * f,
																const gsl_matrix * const * sqrt_q,
																unsigned int size_x,
																unsigned int nb_modes,
																gsl_rng * rng )
{
	initialize();
	setup(	t_0,
			sqrt_q_0,
			f,
			sqrt_q,
			size_x,
			nb_modes,
			rng );
}

int switching_tkalman_simulation :: setup( 	const gsl_vector * t_0,
											const gsl_matrix * sqrt_q_0,
											const gsl_matrix * const * f,
											const gsl_matrix * const * sqrt_q,
											unsigned int size_x,
											unsigned int nb_modes,
											gsl_rng * rng )
{
	free();
	initialize();
	
	if ( ! t_0 || ! sqrt_q_0 || ! sqrt_q || ! f || ! size_x || ! nb_modes || ! rng )
		return 1;
	
	_size_t = t_0->size;
	_size_x = size_x;
	if ( _size_x >= _size_t )
	{
		initialize();
		return 1;
	}
	_size_y = _size_t - _size_x;
	_nb_modes = nb_modes;
	_rng = rng;
	
	//Controle des dimensions
	if ( 	sqrt_q_0->size1 != _size_t	||
			sqrt_q_0->size2 != _size_t )
	{
		initialize();
		return 1;
	}
		
	for ( unsigned int i = 0; i < _nb_modes; ++ i )
	{
		if ( ! f[i] || ! sqrt_q[i] )
		{
			initialize();
			return 1;
		}
		if ( 	f[i]->size1 != _size_t			||
				f[i]->size2 != _size_t			||
				sqrt_q[i]->size1 != _size_t		||
				sqrt_q[i]->size2 != _size_t		)
		{
			initialize();
			return 1;
		}
		
	}
	
	_sqrt_q_0 = sqrt_q_0;
	_t_0 = t_0;
	_f = f;
	_sqrt_q = sqrt_q;
	
	alloc();
	create_views();
	
	
	
	return 0;
}

switching_tkalman_simulation :: ~switching_tkalman_simulation()
{
	free();
	initialize();
}

void switching_tkalman_simulation :: initialize()
{
	_t_0 = 0;
	_sqrt_q_0 = 0;
	_f = 0;
	f_xt = 0;
	p_f_xt = 0;
	f_yt = 0;
	p_f_yt = 0; 
	_sqrt_q = 0; 
	sqrt_q_xx = 0;
	p_sqrt_q_xx = 0; 
	sqrt_q_yy = 0;
	p_sqrt_q_yy = 0; 
	_nb_modes = 0;
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
	tmp_f = 0;
	tmp_sqrt_q = 0;
	vect_t_2 = 0;
	_rng = 0;
}

void switching_tkalman_simulation :: alloc()
{
	f_xt = new gsl_matrix[_nb_modes];
	p_f_xt = new gsl_matrix*[_nb_modes];
	f_yt = new gsl_matrix[_nb_modes];
	p_f_yt = new gsl_matrix*[_nb_modes];
	
	sqrt_q_xx = new gsl_matrix[_nb_modes];
	p_sqrt_q_xx = new gsl_matrix*[_nb_modes];
	sqrt_q_yy = new gsl_matrix[_nb_modes];
	p_sqrt_q_yy = new gsl_matrix*[_nb_modes];
	
	tmp_f = gsl_matrix_alloc( _size_t, _size_t );
	tmp_sqrt_q = gsl_matrix_alloc( _size_t, _size_t );
	vect_t_2 = gsl_vector_alloc( _size_t );
}

void switching_tkalman_simulation :: free()
{
	if ( f_xt )
		delete[] f_xt;
	
	if ( p_f_xt )
		delete[] p_f_xt;
		
	if ( f_yt )
		delete[] f_yt;
	
	if ( p_f_yt )
		delete[] p_f_yt;
		
	if ( sqrt_q_xx )
		delete[] sqrt_q_xx;
	
	if ( p_sqrt_q_xx )
		delete[] p_sqrt_q_xx;
		
	if ( sqrt_q_yy )
		delete[] sqrt_q_yy;
	
	if ( p_sqrt_q_yy )
		delete[] p_sqrt_q_yy;
		
	if ( tmp_f )
		gsl_matrix_free( tmp_f );
	if ( tmp_sqrt_q )
		gsl_matrix_free( tmp_sqrt_q );
	if ( vect_t_2 )
		gsl_vector_free( vect_t_2 );

}

void switching_tkalman_simulation :: create_views()
{
	//Fxt
	gsl_matrix_view sdfjkdfn = gsl_matrix_submatrix (	tmp_f, 
														0,
														0,
														_size_x,
														_size_t );
	tmp_f_xt = sdfjkdfn.matrix;
	//Fyt
	sdfjkdfn = gsl_matrix_submatrix (	tmp_f, 
										_size_x,
										0,
										_size_y,
										_size_t );
	tmp_f_yt = sdfjkdfn.matrix;
	
	//Qxx
	sdfjkdfn = gsl_matrix_submatrix (	tmp_sqrt_q, 
										0,
										0,
										_size_x,
										_size_x );
	tmp_sqrt_q_xx = sdfjkdfn.matrix;
	//Qyy
	sdfjkdfn = gsl_matrix_submatrix (	tmp_sqrt_q,
										_size_x,
										_size_x,
										_size_y,
										_size_y );
	tmp_sqrt_q_yy = sdfjkdfn.matrix;
	
	for ( unsigned int i = 0; i < _nb_modes; ++ i )
	{
		//Fxt
		gsl_matrix_const_view dtc1 
			= gsl_matrix_const_submatrix (	_f[i], 
											0,
											0,
											_size_x,
											_size_t );
		f_xt[i] = dtc1.matrix;
		p_f_xt[i] = f_xt + i;
		
		//Fyt
		gsl_matrix_const_view dtc2
			= gsl_matrix_const_submatrix (	_f[i], 
											_size_x,
											0,
											_size_y,
											_size_t );
		f_yt[i] = dtc2.matrix;
		p_f_yt[i] = f_yt + i;
		
		//Qxx
		gsl_matrix_const_view dtc3
			= gsl_matrix_const_submatrix (	_sqrt_q[i], 
											0,
											0,
											_size_x,
											_size_x );
		sqrt_q_xx[i] = dtc3.matrix;
		p_sqrt_q_xx[i] = sqrt_q_xx + i;
		
		//Qyy
		gsl_matrix_const_view dtc4
			= gsl_matrix_const_submatrix (	_sqrt_q[i], 
											_size_x,
											_size_x,
											_size_y,
											_size_y );
		sqrt_q_yy[i] = dtc4.matrix;
		p_sqrt_q_yy[i] = sqrt_q_yy + i;
		
	}
}



void switching_tkalman_transition (	gsl_vector * t,
									const gsl_vector * _t,
									unsigned int _r,
									unsigned int r,
									const gsl_matrix * const * f_xt,
									const gsl_matrix * const * f_yt,
									const gsl_matrix * const * sqrt_q_xx,
									const gsl_matrix * const * sqrt_q_yy,
									gsl_matrix * tmp_f,
									gsl_matrix * tmp_f_xt,
									gsl_matrix * tmp_f_yt,
									gsl_matrix * tmp_sqrt_q,
									gsl_matrix * tmp_sqrt_q_xx,
									gsl_matrix * tmp_sqrt_q_yy,
									gsl_vector * vect_t_2,
									gsl_rng * rng )
{
		//Construction de F
		gsl_matrix_memcpy( tmp_f_xt, f_xt[r] );
		gsl_matrix_memcpy( tmp_f_yt, f_yt[_r] );
		
		//Construction de Q
		gsl_matrix_set_zero( tmp_sqrt_q );
		gsl_matrix_memcpy( tmp_sqrt_q_xx, sqrt_q_xx[r] );
		gsl_matrix_memcpy( tmp_sqrt_q_yy, sqrt_q_yy[_r] );
		
		tkalman_transition(	t,
							_t,
							tmp_f,
							tmp_sqrt_q,
							rng,
							vect_t_2  );
	
}




void do_switching_tkalman_simulation (	gsl_vector ** t,
										const gsl_vector * t0,
										const gsl_matrix * sqrt_q0,
										const gsl_matrix * const * f_xt,
										const gsl_matrix * const * f_yt,
										const gsl_matrix * const * sqrt_q_xx,
										const gsl_matrix * const * sqrt_q_yy,
										const unsigned int * process,
										const unsigned int n,
										gsl_matrix * tmp_f,
										gsl_matrix * tmp_f_xt,
										gsl_matrix * tmp_f_yt,
										gsl_matrix * tmp_sqrt_q,
										gsl_matrix * tmp_sqrt_q_xx,
										gsl_matrix * tmp_sqrt_q_yy,
										gsl_vector * vect_t_2,
										gsl_rng * rng )
{
	//t0
	gaussian_rand (	t[0],
					t0,
					sqrt_q0,
					rng,
					vect_t_2 );
	
	//
	for ( unsigned int i = 1; i <= n; ++ i )
	{
		switching_tkalman_transition( 	t[i],
										t[i - 1],
										process[i - 1],
										process[i],
										f_xt,
										f_yt,
										sqrt_q_xx,
										sqrt_q_yy,
										tmp_f,
										tmp_f_xt,
										tmp_f_yt,
										tmp_sqrt_q,
										tmp_sqrt_q_xx,
										tmp_sqrt_q_yy,
										vect_t_2,
										rng );
		
	}	
}




