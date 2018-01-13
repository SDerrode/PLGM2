#ifndef _SWITCHING_TKALMAN_SIMULATION_HPP_
#define _SWITCHING_TKALMAN_SIMULATION_HPP_
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include "basic_simulation.hpp"
/**@fn
 * @param[out] t : \f$t_{n + 1}\f$
 * @param[in] _t : \f$t_{n}\f$
 * @param[in] _r : \f$r_{n}\f$
 * @param[in] r : \f$r_{n + 1}\f$
 * @param[in] f_xt : \f$ F^{x,t} \f$, matrice de l'équation d'état
 * @param[in] f_yt : \f$ F^{y,t} \f$, matrice de l'équation de mesure
 * @param[in] sqrt_q_xx : \f$ [Q^{x,x}]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit de process
 * @param[in] sqrt_q_yy : \f$ [Q^{y,y}]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit de mesure
 * @param[in] process : mode de transition
 * @param[in] n : nombre d'échantillons
 * @param tmp_f : matrice de taille \f$ (n_t, n_t) \f$ allouée pour stoker \f$F(k) = [F^{x,t}(r_k); F^{x,t}(r_{k-1})]\f$
 * @param tmp_sqrt_q : matrice de taille \f$ (n_t, n_t) \f$ allouée pour stoker \f$[Q(k)]^{\frac{1}{2}}\f$ 
 * @param vect_t_2 : vecteur de taille t alloué
 * @param rng : générateur de nombre (préalloué)
 * @brief
 * Simulation pour le filtre de Kalman couple à saut
 **/
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
									gsl_rng * rng );





/**@fn void do_switching_tkalman_simulation (	gsl_vector ** t,
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
												gsl_rng * rng );
 * @param[out] t : \f$t_n\f$
 * @param[in] t0 : \f$\hat{t}_0\f$, espérance de t_0
 * @param[in] sqrt_q0 : \f$[Q_0]^{\frac{1}{2}}\f$, racine de la matrice de covariance de t_0
 * @param[in] f_xt : \f$ F^{x,t} \f$, matrice de l'équation d'état
 * @param[in] f_yt : \f$ F^{y,t} \f$, matrice de l'équation de mesure
 * @param[in] sqrt_q_xx : \f$ [Q^{x,x}]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit de process
 * @param[in] sqrt_q_yy : \f$ [Q^{y,y}]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit de mesure
 * @param[in] process : mode de transition
 * @param[in] n : nombre d'échantillons
 * @param tmp_f : matrice de taille \f$ (n_t, n_t) \f$ allouée pour stoker \f$F(k) = [F^{x,t}(r_k); F^{x,t}(r_{k-1})]\f$
 * @param tmp_sqrt_q : matrice de taille \f$ (n_t, n_t) \f$ allouée pour stoker \f$[Q(k)]^{\frac{1}{2}}\f$ 
 * @param vect_t_2 : vecteur de taille t alloué
 * @param rng : générateur de nombre (préalloué)
 * @brief
 * Simulation pour le filtre de Kalman couple à saut
 **/
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
										gsl_rng * rng );




/**@class
 * @brief
 * Gestion de la simulation des filtres de Kalman couple à saut
 * 
 **/
class switching_tkalman_simulation
{
	public:
		/**@fn
		 * @param[in] t_0 : \f$\hat{t}_0\f$, espérance de t_0
		 * @param[in] sqrt_q_0 : \f$[Q_0]^{\frac{1}{2}}\f$, racine de la matrice de covariance de t_0
		 * @param[in] f : \f$ F \f$, matrice de transition
		 * @param[in] sqrt_q : \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
		 * @param[in] size_x : dimension de x
		 * @param[in] nb_modes : nombre de modes
		 * @param rng : RNG
		 * @brief
		 * Constructeur
		 * 
		 **/
		switching_tkalman_simulation( 	const gsl_vector * t_0,
										const gsl_matrix * sqrt_q_0,
										const gsl_matrix * const * f,
										const gsl_matrix * const * sqrt_q,
										unsigned int size_x,
										unsigned int nb_modes,
										gsl_rng * rng );
	
		/**@fn
		 * @param[in] t_0 : \f$\hat{t}_0\f$, espérance de t_0
		 * @param[in] sqrt_q_0 : \f$[Q_0]^{\frac{1}{2}}\f$, racine de la matrice de covariance de t_0
		 * @param[in] f : \f$ F \f$, matrice de transition
		 * @param[in] sqrt_q : \f$ [Q]^{\frac{1}{2}} \f$, racine de la matrice de covariance du bruit
		 * @param[in] size_x : dimension de x
		 * @param[in] nb_modes : nombre de modes
		 * @param rng : RNG
		 * @brief
		 * Setup
		 * 
		 **/
		int setup( 	const gsl_vector * t_0,
					const gsl_matrix * sqrt_q_0,
					const gsl_matrix * const * f,
					const gsl_matrix * const * sqrt_q,
					unsigned int size_x,
					unsigned int nb_modes,
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
		 * @param[in] _r : \f$r_{n}\f$
		 * @param[in] r : \f$r_{n + 1}\f$
		 * @brief
		 * Simulation de \f$ t_n\f$
		 */
		inline void simulation_transition(	gsl_vector * t,
											const gsl_vector * _t,
											unsigned int _r,
											unsigned int r )
		{
			switching_tkalman_transition (	t,
											_t,
											_r,
											r,
											p_f_xt,
											p_f_yt,
											p_sqrt_q_xx,
											p_sqrt_q_yy,
											tmp_f,
											&tmp_f_xt,
											&tmp_f_yt,
											tmp_sqrt_q,
											&tmp_sqrt_q_xx,
											&tmp_sqrt_q_yy,
											vect_t_2,
											_rng );
		}
	
		/**@fn
		 * @param[out] t : \f$t_n\f$
		 * @param[in] nb_samples : nombre d'observations
		 * @brief
		 * Simulation de données Kalman couple
		 **/
		inline void simulate_tkalman_data( 	gsl_vector **  t,
											unsigned int * process,
											unsigned int nb_samples )
		{
			do_switching_tkalman_simulation (	t,
												_t_0,
												_sqrt_q_0,
												p_f_xt,
												p_f_yt,
												p_sqrt_q_xx,
												p_sqrt_q_yy,
												process,
												nb_samples,
												tmp_f,
												&tmp_f_xt,
												&tmp_f_yt,
												tmp_sqrt_q,
												&tmp_sqrt_q_xx,
												&tmp_sqrt_q_yy,
												vect_t_2,
												_rng  );
		}
		
		/**@fn
		 * @brief
		 * Destructeur
		 * 
		 **/
		~switching_tkalman_simulation();
		
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
		 * Dim. de x
		 * 
		 * 
		 **/
		inline unsigned int size_x() const
		{
			return _size_x;
		}
		
		/**@fn
		 * @return
		 * Dim. de y
		 * 
		 * 
		 **/
		inline unsigned int size_y() const
		{
			return _size_y;
		}
		
		/**@fn
		 * @return
		 * Nombre de modes
		 * 
		 * 
		 **/
		inline unsigned int nb_modes() const
		{
			return _nb_modes;
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
		inline const gsl_matrix * const * sqrt_q() const
		{
			return _sqrt_q;
		}
	
		/**@fn
		 * @return
		 * \f$ F \f$, matrice de transition
		 * 
		 **/
		inline const gsl_matrix * const * f() const
		{
			return _f;
		}
		
		
		
		
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
		 
		 /**@fn
		  * @brief
		  * Création des vues
		  * 
		  **/
		void create_views();
		 
		 
		 
		 
		const gsl_vector * _t_0;
		const gsl_matrix * _sqrt_q_0;
		const gsl_matrix * const * _f;
		gsl_matrix * f_xt;
		gsl_matrix ** p_f_xt; 
		gsl_matrix * f_yt;
		gsl_matrix ** p_f_yt; 
		
		const gsl_matrix * const * _sqrt_q; 
		gsl_matrix * sqrt_q_xx;
		gsl_matrix ** p_sqrt_q_xx; 
		gsl_matrix * sqrt_q_yy;
		gsl_matrix ** p_sqrt_q_yy; 
		
		unsigned int _nb_modes,
					 _size_x,
					 _size_y,
					 _size_t;
		
		
		gsl_matrix 	*tmp_f,
					tmp_f_xt,
					tmp_f_yt,
					*tmp_sqrt_q,
					tmp_sqrt_q_xx,
					tmp_sqrt_q_yy;
		gsl_vector * vect_t_2;
		gsl_rng * _rng;
	
};




#endif
