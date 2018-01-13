#include "no_tkaman_simulation.hpp"
#include "basic_simulation.hpp"




/**@fn void do_no_tkalman_simulation(gsl_vector ** y,
									   const gsl_vector * const * x,
									   const gsl_matrix * sqrt_q_yy,
									   const unsigned int n,
									   gsl_vector * vect,
									   gsl_rng * r);
 * @param y : observations (x + b)
 * @param x : é"tats cachés
 * @param sqrt_q_yy : cov(b)
 * @param n : nombre d'observations
 * @param vect : ecteur de taille x alloué
 * @param r : gen. de nombre aléatoire
 * @brief
 * Simulateur de signaux bruité selon un bruit gaussien.
 */
void do_no_tkalman_simulation(	gsl_vector ** y,
								const gsl_vector * const * x,
								const gsl_matrix * sqrt_q_yy,
								const unsigned int n,
								gsl_vector * vect,
								gsl_rng * r)
{
	//Tirage des tn
	for ( unsigned int i = 0; i < n; ++ i)
		gaussian_rand( y[i], x[i], sqrt_q_yy, r, vect );
}
