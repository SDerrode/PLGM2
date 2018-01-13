#ifndef _TKALMAN_FILTER_HPP_
#define _TKALMAN_FILTER_HPP_
#include "tkalman_constants.hpp"
#include "tkalman_filtering.hpp"
#include "tkalman_filter_workspace.hpp"
#include "tkalman_moments.hpp"
#include "tkalman_parameters.hpp"
#include "tkalman_prediction.hpp"
#include "tkalman_smoothing.hpp"

namespace tkalman
{
/**@class tkalman :: filter
 * @brief
 * TK filter + smoother
 *
 **/
class filter
{
	public:
		/**@fn tkalman :: filter :: filter (	const parameters * params );
		 * @param[in] params : PKF parameters
		 * @brief
		 * Constructor
		 **/
		filter (	const parameters * params ) throw ( exception &);

		/**@fn tkalman :: filter :: filter (void);
		 *
		 **/
		filter (void);

		/**@fn void tkalman :: filter ::reset();
		 * @brief Reset
		 **/
		void reset();

		/**@fn int tkalman :: filter :: setup(	const parameters * params );
		 * @param[in] params : PKF parameters
		 * @brief
		 * Setup.
		 *
		 **/
		int setup(	const parameters * params );

		/**@fn tkalman :: filter :: ~filter (void);
		 * @brief
		 * Destructor
		 **/
		~filter();

		/**@fn double tkalman :: filter :: filter_data (	moments & moments,
															const gsl_vector * const * y,
															unsigned int nb_observations ) const;
		 * @param[out] moments : moments
		 * @param[in] y : observations
		 * @param[in] nb_observations : nb of observations
		 * @return
		 * Likelihood
		 * @brief
		 * filters data.
		 **/
		double filter_data (	moments & m,
		                        const gsl_vector * const * y,
		                        unsigned int nb_observations ) const;

		/**@fn double tkalman :: filter :: smooth_data (	moments & moments,
															const gsl_vector * const * y,
															unsigned int nb_observations ) const;
		 * @param[out] moments : moments
		 * @param[in] y : observations
		 * @param[in] nb_observations : nb of observations
		 * @return
		 * Likelihood
		 * @brief
		 * smooths data.
		 **/
		double smooth_data (	moments & m,
		                        const gsl_vector * const * y,
		                        unsigned int nb_observations ) const;

//Accesseurs
		/**@fn inline const gsl_vector *  filter :: t_0() const
		 * @return
		 * \f$ \hat{t}_0\f$, initial state expectation!
		 **/
		inline const gsl_vector * get_t_0() const
		{
			return params->get_t_0();
		}

		/**@fn inline const gsl_matrix * filter :: f() const
		 * @return
		 * \f$ F\f$, transition matrix
		 **/
		inline const gsl_matrix * get_f() const
		{
			return params->get_f();
		}

		/**@fn void filter :: get_q( gsl_matrix * q ) const;
		 * @param[out] q : \f$ Q \f$, noise covariance matrix
		 **/
		inline const gsl_matrix * q_0() const
		{
			return params->q_0();
		}

		/**@fn void filter :: get_q_0( gsl_matrix * q_0 ) const;
		 * @param[out] q_0 : \f$ Q_0 \f$, noise covariance matrix
		 **/
		inline const gsl_matrix * q() const
		{
			return params->q();
		}

		/**@fn inline unsigned int tkalman :: filter :: size_x() const
		 * @return
		 * Size of x
		 **/
		inline unsigned int size_x() const
		{
			return params->size_x();
		}

		/**@fn inline unsigned int tkalman :: filter :: size_y() const
		 * @return
		 * Size of y
		 **/
		inline unsigned int size_y() const
		{
			return params->size_y();
		}

		/**@fn inline unsigned int tkalman :: filter :: size_t() const
		 * @return
		 * Size of t
		 **/
		inline unsigned int size_t() const
		{
			return params->size_t();
		}

		/**@fn inline const gsl_matrix * tkalman :: filter :: sqrt_q2_xx() const
		 *
		 **/
		inline const gsl_matrix * sqrt_q2_xx() const
		{
			return w->sqrt_q2_xx();
		}
		/**@fn inline const gsl_matrix * tkalman :: filter :: f2_xt() const
		 *
		 **/
		inline const gsl_matrix * f2_xt() const
		{
			return w->f2_xt();
		}


		/**@fn inline const gsl_matrix * tkalman :: filter :: q2_xy() const
		 *
		 **/
		inline const gsl_matrix * q2_xy() const
		{
			return w->q2_xy();
		}

		/**@fn double tkalman :: filter ::compute_likelihood( unsigned int nb_observations );
		 * @param[in] nb_observation : number of observations
		 * @return
		 * likelihood.
		 **/
		double compute_likelihood(	moments & m ) const;

	protected:
		/**@fn void tkalman :: filter :: initialize();
		 * @brief
		 * This function sets object attributes to 0.
		 */
		void initialize();
		/**@fn void tkalman :: filter :: free();
		 * @brief
		 * This function frees memory.
		 */
		void free();
		/**@fn void tkalman :: filter :: alloc();
		 * @brief
		 * This function allocates attributes.
		 */
		void alloc();



//Paramètres
		const parameters * params;

//Objets
		constants constants_obj;
		prediction prediction_obj;
		filtering filtering_obj;
		smoothing smoothing_obj;

		mutable filter_workspace * w;
};


};


#endif
