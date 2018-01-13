#include "tkalman_filter.hpp"
#include "tkalman_likelihood.hpp"
#include "gsl_triangle_matrix.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
//

using namespace tkalman;
filter :: filter (	const parameters * params ) throw ( exception & )
{

	initialize();

	if ( setup ( params ) )
		throw ( invalid_argument(" filter :: filter => Envoi de madeleines dans le service info!"));
	
}

filter :: filter (void)
{
	initialize();
}

void filter :: reset()
{
	free();
	initialize();
}

int filter :: setup(	const parameters * _params )
{

	reset();
	if ( ! _params )
		return 1;
	params = _params;
	//Alloc mémoire
	alloc();
	
	//Setup constants
	if ( constants_obj.setup(	params->get_f_xt(),
								params->get_f_yt(),
								params->get_sqrt_q_xx(),
								params->get_sqrt_q_view_xy(),
								params->get_sqrt_q_view_yy() ) )
		return 1;

	//Setup prediction
	if ( prediction_obj.setup (	w->f2_xt(),
								w->sqrt_q2_xx(),
								w->q2_xy() ) )
		return 1;
	
	//Setup filtrage
	if ( filtering_obj.setup(	params->get_f_yt(),
								w->sqrt_q_yy() ) )
		return 1;

	//Setup lissage
	if ( smoothing_obj.setup(	w->f2_xt(), 
								w->sqrt_q2_xx() ) )
		return 1;

	return 0;
}

filter :: ~filter()
{
	reset();
}

void filter :: initialize()
{

	params = 0;
	constants_obj.reset();
	prediction_obj.reset();
	filtering_obj.reset();
	smoothing_obj.reset();
	w = 0;
}

void filter :: free()
{
	if ( w )
		delete w;
}

void filter :: alloc()
{
	w = new filter_workspace( 	params->size_x(), 
								params->size_y() );
}


double filter :: filter_data (	moments & m,
								const gsl_vector * const * y,
								unsigned int nb_observations ) const
{
	m.set_nb_moments( nb_observations + 1 );
	
	//Constantes
	constants_obj.compute( 	w->f2_xt(), 
							w->sqrt_q2_xx(), 
							w->q2_xy(), 
							w->sqrt_q_yy() );
							

	//Prédiction 0

	gsl_vector_memcpy(	m.x_p(0), 
						params->get_t_0() );

	gsl_matrix_memcpy(	m.sqrt_p_p(0), 
						params->get_sqrt_q_0() );

	//Filtrage 0
	filtering_obj.compute_0(	m.x_f(0),
								m.sqrt_p_f(0),
								m.y_p( 0 ),
								m.sqrt_s_p( 0 ),
								m.x_p(0),
								m.sqrt_p_p(0),
								y[0] );	
	//Prédiction 1
	prediction_obj.compute_1 (	m.x_p(1),
								m.sqrt_p_p(1),
								m.x_f(0),
								m.sqrt_p_f(0),
								y[0] );
	for ( unsigned int i = 1; i < nb_observations; ++ i )
	{
		//Filtrage i
		filtering_obj.compute(	m.x_f(i),
								m.sqrt_p_f(i),
								m.y_p( i ),
								m.sqrt_s_p( i ),
								m.x_p(i),
								m.sqrt_p_p(i),
								y[i],
								y[i - 1] );
								
		//Prediction i+1
		prediction_obj.compute ( 	m.x_p(i + 1),
									m.sqrt_p_p(i + 1),
									m.x_f(i),
									m.sqrt_p_f(i),
									y[i - 1],
									y[i] );
	}
	return compute_likelihood( m );
}

double filter :: smooth_data (	moments & m,
								const gsl_vector * const * y,
								unsigned int nb_observations ) const
{
	double l = filter_data( m, y , nb_observations );

	//Dernier lissage
	gsl_vector_memcpy(	m.x_s(nb_observations), 
						m.x_p(nb_observations) );

	gsl_matrix_memcpy(	m.sqrt_p_s(nb_observations), 
						m.sqrt_p_p(nb_observations) );

	for (unsigned int i = nb_observations - 1; i > 0; -- i)	
	{
		smoothing_obj.compute (	m.x_s(i),
								m.sqrt_p_s(i),
								m.c_s(i),
								m.x_f(i),
								m.sqrt_p_f(i),
								m.x_p(i + 1),
								m.sqrt_p_p(i + 1),
								m.x_s( i + 1 ),
								m.sqrt_p_s( i + 1 ) );
	}
	
	smoothing_obj.compute_0( 	m.x_s(0),
								m.sqrt_p_s(0),
								m.c_s(0),
								m.x_f(0),
								m.sqrt_p_f(0),
								m.x_p(1),
								m.sqrt_p_p(1),
								m.x_s( 1 ),
								m.sqrt_p_s( 1 ) );
	return l;
}

double filter :: compute_likelihood(	moments & m ) const
{
	double l = 0;
	unsigned int nb_obs = m.nb_moments() - 1;
	for ( unsigned int n = 0; n < nb_obs; ++ n )
	{
		l += log_likelihood( 	m.get_innovation( n ), 
								m.sqrt_s_p( n ), 
								w->vect_y() );
	}
	return l;
	
}

