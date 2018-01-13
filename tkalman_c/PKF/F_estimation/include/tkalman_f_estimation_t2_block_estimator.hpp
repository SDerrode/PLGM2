#ifndef _TKALMAN_F_ESTIMATION_t2_block_ESTIMATOR_HPP_
#define _TKALMAN_F_ESTIMATION_t2_block_ESTIMATOR_HPP_
#include "tkalman_f_estimation_t2_block_workspace.hpp"
#include "tkalman_f_estimation_t2_block_parameters.hpp"
namespace tkalman
{
	namespace f_estimation
	{
		namespace t2_block
		{
			/**@class tkalman :: f_estimation :: t2_block :: estimator
			 * @brief
			 * Tensorial constraints on \f$F_i\f$
			 * 
			 **/
			class estimator
			{
			public:
				/**@fn tkalman :: f_estimation :: t2_block :: estimator :: estimator();
				 * @brief
				 * Constructor
				 *
				 **/
				estimator();

				/**@fn tkalman :: f_estimation :: t2_block :: estimator :: estimator( 	const t2_block :: parameters * params ) throw ( exception &);
				 * @param[in] params : estimator parameters
				 * @brief
				 * Constructor
				 *
				 **/
				estimator( 	const t2_block :: parameters * params ) throw ( exception &);
				
				/**@fn void tkalman :: f_estimation :: t2_block :: estimator :: reset();
				 * @brief
				 * Reset
				 **/
				void reset();

				/**@fn int tkalman :: f_estimation :: t2_block :: setup (	const t2_block :: parameters * params );
				 * @param[in] params : estimator parameters
				 * @brief
				 * Setup
				 **/
				int setup (	const t2_block :: parameters * params );

				/**@fn void tkalman :: f_estimation :: t2_block :: estimate( 	gsl_matrix * f_i,
																							const gsl_matrix * sqrt_c_i_view_00,
																							const gsl_matrix * sqrt_c_i_view_01 ) const;
				 * @param[out] f_i : \f$ F_i \f$, estimated parameter
				 * @param[in] sqrt_c_i_view_00 :\f$ [\tilde{C}_i^{0,0}]^{\frac{1}{2}} \f$
				 * @param[in] sqrt_c_i_view_01 :\f$ [\tilde{C}_i]^{\frac{1}{2}}(0,1) \f$
				 * @brief
				 * This function estimates $F_i$.
				 **/
				void estimate( 	gsl_matrix * f_i,
								const gsl_matrix * sqrt_c_i_view_00,
								const gsl_matrix * sqrt_c_i_view_01,
								const gsl_matrix * _sqrt_q ) const;

				/**@fn tkalman :: f_estimation :: t2_block :: estimator :: ~estimator();
				 * @brief
				 * Destructor
				 **/
				~estimator();
			//Accesseurs
				/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: estimator :: size_i() const
				 * @brief
				 * \f$n_i\f$
				 * 
				 **/
				inline unsigned int size_i() const
				{
					return p->size_i();
				}

				/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: estimator :: size_t() const
				 * @brief
				 * \f$n_t\f$
				 * 
				 **/
				inline unsigned int size_t() const
				{
					return p->size_t();
				}

				/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: estimator :: size_lambda() const
				 * @brief
				 * \f$n^{\lambda}_i\f$
				 * 
				 **/
				inline unsigned int size_lambda() const
				{
					return p->size_lambda();
				}

				/**@fn inline const gsl_matrix * const * tkalman :: f_estimation :: t2_block :: estimator :: m() const
				 * @brief
				 * \f$ M_i^j\f$
				 * 
				 **/
				inline const gsl_matrix * const * m() const
				{
					return p->m();
				}
				
			protected:
				/**@fn void tkalman :: f_estimation :: t2_block :: estimator ::  free();
				 * @brief
				 * Free memory
				 **/
				void free();

				/**@fn void tkalman :: f_estimation :: t2_block :: estimator ::  alloc();
				 * @brief
				 * memory allocation
				 **/
				void alloc();

				/**@fn void tkalman :: f_estimation :: t2_block :: estimator :: initialize();
				 * @brief
				 * Set object attributes to 0.
				 **/
				void initialize();

				const t2_block :: parameters * p;
				mutable t2_block :: workspace * w;
			};
	


		};
	};
};

#endif
