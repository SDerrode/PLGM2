#ifndef MARKOV_CHAIN_SIMU_HPP
#define MARKOV_CHAIN_SIMU_HPP
	#include <gsl/gsl_matrix.h>
	#include <gsl/gsl_rng.h>
	#include "basic_simulation.hpp"






	/**@fn unsigned int regime_transition ( 	unsigned int _r,
												const gsl_matrix * pi,
												gsl_rng * rng  );
	 * @param _r : mode précédent
	 * @param pi_cum : matrice de transition cumulée
	 * @param rng : générateur de nombres aléatoires
	 **/
	inline unsigned int regime_transition ( 	unsigned int _r,
												const gsl_matrix * pi_cum,
												gsl_rng * rng )
	{
		return discrete_rand( 	pi_cum->data + _r * pi_cum->tda, 
								pi_cum->size1, 
								1, 
								rng );
		
	}
										
										
	/**@fn unsigned int regime_0 (	const gsl_vector * pi_0_cum,
									gsl_rng * rng );
	 * @param pi_0_cum : proba initiales des modes cumulées
	 * @param rng : générateur de nombres aléatoires
	 **/
	inline unsigned int regime_0 (	const gsl_vector * pi_0_cum,
									gsl_rng * rng )
	{
		return discrete_rand( 	pi_0_cum->data, 
								pi_0_cum->size, 
								pi_0_cum->stride, 
								rng );
	}

	/**@fn
	 * @param[out] process : Markov process
	 * @param[in] nb_samples : number of samples
	 * @param[in] transition_matrix : transition matrix for Markov process
	 * @param[in] initial_proba : Initiail proba for Markov process
	 * @param r : rng
	 * @brief
	 * This function simulates a Markov process
	 * 
	 * 
	 **/
	void simulate_Markov_process( 	unsigned int * process,
									unsigned int nb_samples,
									const gsl_matrix * pi_cum,
									const gsl_vector * pi_0_cum,
									gsl_rng * r );
	
	
	
	/**@class
	 * @brief
	 * Gestion de la simulation d'un processus markovien
	 * 
	 **/
	class markov_process_simulation
	{
		public:
			/**@fn
			 * @param[in] pi_cum : matrice de transition cumulée
			 * @param[in] pi_0_cum : proba initiales des modes cumulées
			 * @param rng : RNG
			 * @brief
			 * Constructeur
			 **/
			markov_process_simulation ( const gsl_matrix * pi_cum,
										const gsl_vector * pi_0_cum,
										gsl_rng * rng );
			
			/**@fn
			 * @param[in] pi_cum : matrice de transition cumulée
			 * @param[in] pi_0_cum : proba initiales des modes cumulées
			 * @param rng : RNG
			 * @brief
			 * Setup
			 **/
			int setup( 	const gsl_matrix * pi_cum,
						const gsl_vector * pi_0_cum,
						gsl_rng * rng );  
		
			
			/**@fn
			 * @return
			 * Process 0
			 * 
			 */
			inline unsigned int get_regime_0()
			{
				return regime_0 (	_pi_0_cum,
									_rng );
			}
			
			/**@fn
			 * @param[in] _r : \f$ r(n - 1) \f$ 
			 * 
			 * @return
			 * Regime \f$ r(n) \f$ 
			 * 
			 */
			inline unsigned int get_regime_transition( unsigned int _r )
			{
				return regime_transition ( 	_r,
											_pi_cum,
											_rng );
			}
			
			
			/**@fn
			 * @param[out] process : Markov process
			 * @param[in] nb_samples : number of samples
			 * @brief
			 * This function simulates a Markov process
			 **/
			inline void simulate_process( 	unsigned int * process,
											unsigned int nb_samples )
			{
				simulate_Markov_process(	process,
											nb_samples,
											_pi_cum,
											_pi_0_cum,
											_rng ); 
			}
		
		
		
			/**@fn
			 * @brief
			 * Destructeur
			 * 
			 **/
			~markov_process_simulation();
			
			/**@fn
			 * @return
			 * RNG
			 * 
			 **/
			inline gsl_rng * rng()
			{
				return _rng;
			}
			
			
			/**@fn
			 * @return
			 * matrice de transition cumulée
			 * 
			 **/
			inline const gsl_matrix * pi_cum() const
			{
				return _pi_cum;
			}
			
			
			/**@fn
			 * @return 
			 * proba initiales des modes cumulées
			 **/
			inline const gsl_vector * pi_0_cum() const
			{
				return _pi_0_cum;
			}
			
			/**@fn
			 * @return
			 * Nombre de modes.
			 * 
			 **/
			inline unsigned int nb_modes() const
			{
				return _nb_modes;
			}
			
			
		protected:
			/**@fn
			 * @brief
			 * Ini.
			 * 
			 **/
			void initialize();
			
			
		
			gsl_rng * _rng;
			unsigned int _nb_modes;
			const gsl_matrix * _pi_cum;
			const gsl_vector * _pi_0_cum;
	};



#endif
