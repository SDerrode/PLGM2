#ifndef _TKALMAN_Q_ESTIMATION_FREE_BLOCK_ESTIMATOR_HPP_
#define _TKALMAN_Q_ESTIMATION_FREE_BLOCK_ESTIMATOR_HPP_
#include "tkalman_q_estimation_free_block_workspace.hpp"
namespace tkalman
{
namespace q_estimation
{
namespace free_block
{

/**@class estimator
 * @brief
 * Estimator for free blocks
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
	 * @param[in] size : block size
	 * @param[in] size_t : \f$n_t\f$
	 * @brief
	 * constructor
	 * 
	 **/
	estimator (	unsigned int size_i,
				unsigned int size_t ) throw( exception &);
	
	/**@fn
	 * @param[in] size : block size
	 * @param[in] size_t : \f$n_t\f$
	 * @brief
	 * Setup
	 * 
	 **/
	int setup(	unsigned int size_i,
				unsigned int size_t ); 

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
	 * @return
	 * Block size
	 * 
	 **/
	inline unsigned int size_i() const
	{
		return _size_i;
	}

	/**@fn
	 * @return
	 * \f$n_t\f$
	 * 
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}


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

	unsigned int _size_i, _size_t;
	mutable free_block :: workspace * w;
};
	
	
};

};

};



#endif
