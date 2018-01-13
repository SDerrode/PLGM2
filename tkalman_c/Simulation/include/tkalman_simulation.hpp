
#ifndef _TKALMAN_SIMULATION_HPP_
#define _TKALMAN_SIMULATION_HPP_
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include "basic_simulation.hpp"

/**@fn
 * @param[out] t : \f$ t_{n + 1} = (x_{n + 1}; y_{n}) \f$
 * @param[in] _t : \f$ t_{n} = (x_{n}; y_{n - 1}) \f$
 * @param[in] f : \f$ F \f$, matrice de transition
 * @param[in] sqrt_q : \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
 * @param rng : RNG
 * @param vect_t_2 : vecteur de taille t alloué
 * @brief
 * Simulation de la transition dans le filtre de Kalman couple
 **/
void tkalman_transition( 	gsl_vector * t,
							const gsl_vector * _t,
							const gsl_matrix * f,
							const gsl_matrix * sqrt_q,
							gsl_rng * rng,
							gsl_vector * vect_t_2  );
							
							

/**@fn void tkalman_simulation(gsl_vector ** t,
								 const gsl_vector * t0,
								 const gsl_matrix * sqrt_q0,
								 const gsl_matrix * f,
								 const gsl_matrix * sqrt_q,
								 const unsigned int n,
								 gsl_vector * vect_t_2,
								 gsl_rng * rng)
 * @param[out] t : \f$t_n\f$
 * @param[in] t0 : \f$\hat{t}_0\f$, espérance de t_0
 * @param[in] sqrt_q0 : \f$[Q_0]^{\frac{1}{2}}\f$, racine de la matrice de covariance de t_0
 * @param[in] f : \f$ F \f$, matrice de transition
 * @param[in] sqrt_q : \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
 * @param[in] n : nombre d'observations
 * @param vect_t_2 : vecteur de taille t alloué
 * @param rng : générateur de nombre (préalloué)
 * @brief
 * Cette fonction simule des données selon le modèle du filtre de Kalman couple.
**/
void do_tkalman_simulation(	gsl_vector **  t,
							const gsl_vector * t0,
							const gsl_matrix * sqrt_q0,
							const gsl_matrix * f,
							const gsl_matrix * sqrt_q,
							const unsigned int n,
							gsl_vector * vect_t_2,
							gsl_rng * rng);



/**@class
 * @brief
 * Gestion de la simulation des données suivant un modèle du filtre de Kalman couple.
 * 
 **/
class tkalman_simualtion
{
	public:
		/**@fn
		 * @param[in] t0 : \f$\hat{t}_0\f$, espérance de t_0
		 * @param[in] sqrt_q0 : \f$[Q_0]^{\frac{1}{2}}\f$, racine de la matrice de covariance de t_0
		 * @param[in] f : \f$ F \f$, matrice de transition
		 * @param[in] sqrt_q : \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
		 * @param rng : RNG
		 * @brief
		 * Constructeur
		 **/
		tkalman_simualtion( const gsl_vector * t0,
							const gsl_matrix * q0,
							const gsl_matrix * f,
							const gsl_matrix * q,
							gsl_rng * rng );
		/**@fn
		 * @param[in] t0 : \f$\hat{t}_0\f$, espérance de t_0
		 * @param[in] sqrt_q0 : \f$[Q_0]^{\frac{1}{2}}\f$, racine de la matrice de covariance de t_0
		 * @param[in] f : \f$ F \f$, matrice de transition
		 * @param[in] sqrt_q : \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
		 * @param rng : RNG
		 * @brief
		 * Setup
		 **/
		int setup( 	const gsl_vector * t0,
					const gsl_matrix * q0,
					const gsl_matrix * f,
					const gsl_matrix * q,
					gsl_rng * rng );
		
		/**@fn
		 * @param[out] t_0 : \f$ t_0\f$
		 * @brief
		 * Simulation de \f$ t_0\f$
		 * 
		 **/
		inline void simulate_t_0( gsl_vector * t_0 )
		{
			gaussian_rand (	t_0,
							_t_0,
							_sqrt_q_0,
							_rng,
							vect_t_2 ); 
				
		}
		
		/**@fn
		 * @param[out] t : \f$ t_n\f$
		 * @param[in] _t : \f$ t_{n-1}\f$
		 * @brief
		 * Simulation de \f$ t_n\f$
		 */
		inline void simulation_transition(	gsl_vector * t,
											const gsl_vector * _t )
		{
			tkalman_transition( 	t,
									_t,
									_f,
									_sqrt_q,
									_rng,
									vect_t_2  );
		}
	
		/**@fn
		 * @param[out] t : \f$t_n\f$
		 * @param[in] nb_samples : nombre d'observations
		 * @brief
		 * Simulation de données Kalman couple
		 **/
		inline void simulate_tkalman_data( 	gsl_vector **  t,
											unsigned int nb_samples )
		{
			do_tkalman_simulation(	t,
									_t_0,
									_sqrt_q_0,
									_f,
									_sqrt_q,
									nb_samples,
									vect_t_2,
									_rng);
		}
		
		/**@fn
		 * @return
		 * Dim. de t
		 * 
		 * 
		 **/
		inline unsigned int size_t() const
		{
			return _size_t;
		}
	
		/**@fn
		 * @return
		 * \f$ \hat{t}_0 \f$, espérance de l'état initial
		 * 
		 **/
		inline const gsl_vector * t_0() const
		{
			return _t_0;
		}
	
		/**@fn
		 * @return
		 * \f$ [Q_0]^{\frac{1}{2}} \f$, racine de la matrice de covariance de l'état initial
		 * 
		 **/
		inline const gsl_matrix * sqrt_q_0() const
		{
			return _sqrt_q_0;
		}
	
		/**@fn
		 * @return
		 * \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
		 * 
		 **/
		inline const gsl_matrix * sqrt_q() const
		{
			return _sqrt_q;
		}
	
		/**@fn
		 * @return
		 * \f$ F \f$, matrice de transition
		 * 
		 **/
		inline const gsl_matrix * f() const
		{
			return _f;
		}
	
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
		 * @brief
		 * Update sqrts
		 * 
		 **/
		int update_sqrts();
	
	
		/**@fn
		 * @brief
		 * Destructeur
		 * 
		 **/
		~tkalman_simualtion();
	protected:

		
		/**@fn
		 * @brief
		 * Ini.
		 * 
		 **/
		void initialize();
	
		/**@fn
		 * @brief
		 * Alloc mémoire
		 * 
		 **/
		void alloc();
		 
		 
		 /**@fn
		  * @brief
		  * Lib. mémoire
		  * 
		  **/
		void free();
		 
		const gsl_vector * _t_0;
		const gsl_matrix * _q;
		const gsl_matrix * _f;
		const gsl_matrix * _q_0;
		
		gsl_matrix * _sqrt_q;
		gsl_matrix * _sqrt_q_0;
		
		
		gsl_rng * _rng;
		
		gsl_vector * vect_t_2 ;
		unsigned int _size_t;
		
};





							 

								



#endif
