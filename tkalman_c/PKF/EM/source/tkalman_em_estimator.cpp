#include "tkalman_em_estimator.hpp"
#include <iostream>
#include <gsl/gsl_linalg.h>
#include <cmath>
#include "gsl_triangle_matrix.hpp"
using namespace std;
using namespace tkalman;
EM :: estimator :: estimator( void )
{
	initialize();
}

EM :: estimator :: estimator( const EM :: parameters * params ) throw (exception&)
{
	initialize();
	if ( setup( params ) )
		throw (invalid_argument("Invalid argument in tkalman :: EM :: estimator :: estimator( const EM :: parameters * params )"));
}

int EM :: estimator :: setup ( const EM :: parameters * params )
{
	reset();

	if ( !params )
		return 1;

	if ( ! (*params) )
		return 2;

	p = params;
	alloc();
	if ( pkf_filter.setup( &(w->pkf_parameters() ) ) )
		return 4;

	if ( pkf_sum.setup(	pkf_filter.f2_xt(),
	                    pkf_filter.sqrt_q2_xx() ) )
		return 5;

	if ( f_estimator.setup(	p->f_0(),
	                        p->sqrt_q_0(),
	                        p->nb_f_blocks(),
	                        p->f_block_row_ids(),
	                        p->f_block_sizes(),
	                        p->f_block_hypotheses(),
	                        p->f_other_data() ) )
		return 6;

	if ( q_estimator.setup(	p->sqrt_q_0(),
	                        p->p(),
	                        p->nb_q_blocks(),
	                        p->q_block_row_ids(),
	                        p->q_block_sizes(),
	                        p->q_block_hypotheses(),
	                        p->q_other_data() ) )
		return 6;
	_first_state_estimation = params->first_state_estimation();
	return 0;
}

void EM :: estimator :: reset()
{
	free();
	initialize();
}

EM :: estimator :: ~estimator()
{
	reset();
}

int  EM :: estimator ::  estimate( 	tkalman :: moments & m,
                                    tkalman :: parameters & p,
                                    const gsl_vector * const * y,
                                    unsigned int nb_observations,
                                    unsigned int nb_iterations,
                                    double * likelihood ) const
{
	return ( estimate( 	&m, p, &y, &nb_observations, 1, nb_iterations, likelihood ) );
}

int EM :: estimator ::  estimate( 	tkalman :: moments * m,
                                    tkalman :: parameters & p,
                                    const gsl_vector * const * const * y,
                                    const unsigned int * nb_observations,
                                    unsigned int nb_signals,
                                    unsigned int nb_iterations,
                                    double * likelihood ) const
{
	//Cas de dimensions différentes. Ne marche pas
	if ( 	p.size_x() != w->pkf_parameters().size_x()	||
	        p.size_t() != w->pkf_parameters().size_t()	)
		return 1;

	w->pkf_parameters() = p;

	//Moments
	for ( unsigned int i = 0; i < nb_signals; ++ i )
	{
		m[i].setup(	pkf_filter.size_x(),
		            pkf_filter.size_y(),
		            nb_observations[i] + 1 );
	}

	for ( unsigned int j = 0; j < nb_iterations; ++ j )
	{
		unsigned int n = 0;
		gsl_matrix_set_zero( w->mat_4t2t() );
		if (likelihood != NULL )
			likelihood[j] = 0;
		//Pour chaque signal
		for ( unsigned int i = 0; i < nb_signals; ++ i )
		{

			//Filtrage - Lissage
			pkf_filter.smooth_data( m[i],
			                        y[i],
			                        nb_observations[i] );
			if (likelihood != NULL )
				likelihood[j] += pkf_filter.compute_likelihood( m[i] ) / nb_observations[i];

			//Sum
			pkf_sum.compute(	w->mat_4t2t_view_1(),
			                    m[i].all_sqrt_p_f(),
			                    m[i].all_x_s(),
			                    m[i].all_sqrt_p_s(),
			                    m[i].all_c_s(),
			                    y[i],
			                    nb_observations[i] );


			//MAJ somme globale
			gsl_linalg_QR_decomp(	w->mat_4t2t(),
			                        w->vect_2t() );

			gsl_triangle_matrix(w->mat_4t2t());
			n += nb_observations[i];
		}

		//Estimation de F
		f_estimator.estimate( 	w->pkf_parameters().f(),
		                        w->mat_4t2t_view_0(),
		                        w->pkf_parameters().sqrt_q() ); //Dernière hypo. uniquement pour le GEM sinon, elle ne sert à rien.

		//Estimation de Q
		q_estimator.estimate( 	w->pkf_parameters().sqrt_q(),
		                        w->pkf_parameters().f(),
		                        w->mat_4t2t_view_0() ,
		                        n );
		//Paramètres initiaux
		if ( _first_state_estimation )
		{
			gsl_vector_set_zero( w->pkf_parameters().t_0() );
			for ( unsigned int i = 0; i < nb_signals; ++ i )
			{

				//T0
				gsl_vector_memcpy( 	w->vect_t(),
				                    m[i].all_x_s()[0] );

				gsl_vector_scale( w->vect_t(), 1 / ( (double) nb_signals ) );

				gsl_vector_add( w->pkf_parameters().t_0(), w->vect_t() );
			}


			gsl_matrix_set_zero( w->mat_2tp1_t() );
			for ( unsigned int i = 0; i < nb_signals; ++ i )
			{
				double sq = sqrt( 1 / ( (double) nb_signals  ) );
				//T0 - t0_i
				gsl_vector_memcpy( 	w->mat_2tp1_t_view_2(),
				                    m[i].all_x_s()[0] );
				gsl_vector_sub( 	w->mat_2tp1_t_view_2(),
				                    w->pkf_parameters().t_0() );
				gsl_vector_scale( w->mat_2tp1_t_view_2(), sq );


				gsl_matrix_memcpy( 	w->mat_2tp1_t_view_1(),
				                    m[i].all_sqrt_p_s()[0] );
				gsl_matrix_scale( w->mat_2tp1_t_view_1(), sq );

				gsl_linalg_QR_decomp(	w->mat_2tp1_t(),
				                        w->vect_t() );
				gsl_triangle_matrix(w->mat_2tp1_t_view_0());
			}
			gsl_matrix_memcpy( 	w->pkf_parameters().sqrt_q_0(),
			                    w->mat_2tp1_t_view_0() );
		}
		w->pkf_parameters().update_q_0_and_q();

		if ( j > 0 && likelihood )
		{
			if (  (likelihood[j] - likelihood[j - 1]) / (likelihood[j] + likelihood[j - 1])  > 1e-3 )
			{
				cout << "Warning : likelihood[" << j << "] - likelihood[" << j - 1 << "] < -1e-6" << endl;
				if ( j == 1 )
				{
					cout << "You must check your EM initial parameters." << endl;
					cout << "Because they have to take account of constraints!" << endl;
					cout << endl;
				}

			}
		}


	}

	//Filtrage final
	if (likelihood != NULL )
		likelihood[nb_iterations] = 0;
	for ( unsigned int i = 0; i < nb_signals; ++ i )
	{
		//Filtrage - Lissage
		pkf_filter.smooth_data( m[i],
		                        y[i],
		                        nb_observations[i] );
		if (likelihood != NULL )
			likelihood[nb_iterations] += pkf_filter.compute_likelihood( m[i] ) / nb_observations[i];
	}


	p = w->pkf_parameters();
}


void EM :: estimator ::  initialize()
{
	p = 0;
	pkf_filter.reset();
	pkf_sum.reset();
	f_estimator.reset();
	q_estimator.reset();
	w = 0;
	_first_state_estimation = 0;
}

void  EM :: estimator :: free()
{
	if ( w )
		delete w;

}

void EM :: estimator :: alloc()
{
	w = new tkalman :: EM :: estimator_workspace( p->size_x(), p->size_y() );
}
