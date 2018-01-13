#ifndef _BASIC_SIMULATION_HPP_
#define _BASIC_SIMULATION_HPP_
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
/**@fn unsigned int discrete_rand (	const double * p_cum,
									unsigned int nb_modes,
									unsigned int stride,
									gsl_rng * rng );
 * @param p_cum : probabilité cumulées
 * @param nb_modes : nombre de modes 
 * @param rng : gén. de nombre aléatoire
 * @brief
 * Tir une V.A. discrète
 **/
unsigned int discrete_rand (	const double * p_cum,
								unsigned int nb_modes,
								unsigned int stride,
								gsl_rng * rng );

/**@fn
 * @param[out] x : résultat du tir aléatoire
 * @param[in] mean : moyenne
 * @param[in] sqrt_var : racine de la matrice de covariance
 * @param vect_x : vecteur de taille \f$ n_x \f$ alloué pour le calcul
 * @param rng : RNG
 * @brief
 * Tir un vecteur gaussien de moyenne mean et de covariance var.
 * 
 **/
void gaussian_rand ( 	gsl_vector * x,
						const gsl_vector * mean,
						const gsl_matrix * sqrt_var,
						gsl_rng * rng,
						gsl_vector * vect_x
						 );

/**@fn void MM_rand( 	gsl_vector * x,
								const double * weight_cum,
								const gsl_vector * const * _x,
								const gsl_matrix * const * _sqrt_p,
								gsl_rng * r );
 * @param x : x simulé
 * @param weight_cum : poids cumulés
 * @param _x : espérances de x
 * @param _sqrt_p : racine des cov. de x
 * @param r : rng
 * 
 **/
void MM_rand ( 	gsl_vector * x,
				const double * weight_cum,
				const gsl_vector * const * _x,
				const gsl_matrix * const * _sqrt_p,
				unsigned int nb_modes,
				unsigned int stride,
				gsl_rng * rng,
				gsl_vector * tmp_x );



#endif
