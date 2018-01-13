#ifndef _TKALMAN_Q_ESTIMATION_T2_BLOCK_ESTIMATOR_HPP_
#define _TKALMAN_Q_ESTIMATION_T2_BLOCK_ESTIMATOR_HPP_
#include "tkalman_q_estimation_t2_block_workspace.hpp"
#include "tkalman_q_estimation_t2_block_parameters.hpp"

namespace tkalman
{
namespace q_estimation
{
namespace t2_block
{

/**@class estimator
 * @brief
 * Estimator for t2-blocks
 * \f$ Q^{\frac{1}{2}} = \lambda Q^{\frac{1}{2}}_0\f$
 *
 **/
class estimator
{
	
public:
	/**@fn
	 * @brief
	 * Default constructor
	 * 
	 **/
	estimator ( void );
	
	/**@fn
	 * @param[in] sqrt_q_0 : \f$ Q^{\frac{1}{2}}\f$
	 * @brief
	 * constructor
	 * 
	 **/
	estimator ( const parameters * params ) throw( exception &);
	
	/**@fn
	 * @param[in] sqrt_q_0 : \f$ Q^{\frac{1}{2}}\f$
	 * @brief
	 * Setup
	 * 
	 **/
	int setup( const parameters * params );

	/**@fn
	 * @brief
	 * Reset.
	 **/
	void reset();

	/**@fn
	 * @param[out] sqrt_q : \f$Q^{\frac{1}{2}}\f$
	 * @param[in] f : \f$F\f$
	 * @param[in] sqrt_c :  \f$\tilde{C}^{\frac{1}{2}}\f$
	 * @param[in] nb_observations : number of observations
	 * @brief
	 * Estimates a free block.
	 * 
	 **/
	void estimate ( gsl_matrix * sqrt_q,
					const gsl_matrix * f,
					const gsl_matrix * sqrt_c,
					unsigned int nb_observations ) const;

	/**@fn
	 * @brief
	 * Destructor
	 **/
	~estimator();
protected:
	/**@fn void tkalman :: f_estimation :: tensorial_constraints :: estimator ::  free();
	 * @brief
	 * Free memory
	 **/
	void free();

	/**@fn void tkalman :: f_estimation :: tensorial_constraints :: estimator ::  alloc();
	 * @brief
	 * memory allocation
	 **/
	void alloc();

	/**@fn void tkalman :: f_estimation :: tensorial_constraints :: estimator :: initialize();
	 * @brief
	 * Set object attributes to 0.
	 **/
	void initialize();

	mutable t2_block :: workspace * w;
	const parameters * p;
};

};
	
	
};
	
	
};




#endif
