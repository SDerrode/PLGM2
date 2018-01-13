#include "Markov_chain_simulation.hpp"
markov_process_simulation :: markov_process_simulation (	const gsl_matrix * pi_cum,
															const gsl_vector * pi_0_cum,
															gsl_rng * rng )
{
	initialize();
	setup( pi_cum, pi_0_cum, rng );
}
			
int markov_process_simulation :: setup( 	const gsl_matrix * pi_cum,
											const gsl_vector * pi_0_cum,
											gsl_rng * rng )
{
	initialize();
	if ( ! pi_cum || ! pi_0_cum || !rng )
		return 1;
	
	_nb_modes = pi_0_cum->size;
	if ( pi_cum->size1 != _nb_modes ||
		 pi_cum->size2 != _nb_modes )
	{
		initialize();
		return 1;
	}
	
	_pi_0_cum = pi_0_cum;
	_pi_cum = pi_cum;
	_rng = rng;
		
	return 0;
}
		

markov_process_simulation :: ~markov_process_simulation()
{
	initialize();
}

void markov_process_simulation :: initialize()
{
	_rng = 0;
	_nb_modes = 0;
	_pi_cum = 0;
	_pi_0_cum = 0;
}

		
			


void simulate_Markov_process( 	unsigned int * process,
								unsigned int nb_samples,
								const gsl_matrix * pi_cum,
								const gsl_vector * pi_0_cum,
								gsl_rng * rng )
{
	process[0] = regime_0 ( pi_0_cum, rng );
	for ( unsigned int i = 1 ; i < nb_samples; ++ i )
		process[i] = regime_transition ( process[i - 1], pi_cum, rng );
}
