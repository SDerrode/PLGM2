#ifndef _TKALMAN_Q_ESTIMATION_HPP_
#define _TKALMAN_Q_ESTIMATION_HPP_
#include "tkalman_q_estimation_workspace.hpp"
#include "tkalman_q_estimation_typedef.hpp"

namespace tkalman
{
namespace q_estimation
{
/**@class estimator
 * @brief
 * Q estimation
 * 
 **/
class estimator
{
public:
	/**@fn
	 * @brief
	 * Default constructor
	 **/
	estimator ( void );

	/**@fn
	 * @param[in] sqrt_q_0 : \f$ [Q^0]^{\frac{1}{2}}\f$
	 * @param[in] nb_blocks : number of blocks
	 * @param[in] block_sizes : sizes of blocks
	 * @param[in] block_rows : row ids of blocks
	 * @param[in] block_hypotheses : hypotheses on block
	 * @param[in] other_data : other parameters
	 * @brief
	 * Constructor
	 **/
	estimator(	const gsl_matrix * sqrt_q_0,
				const gsl_matrix * p,
				unsigned int nb_blocks,
				const unsigned int * const * block_rows,
				const unsigned int * block_sizes,
				const unsigned int * block_hypotheses,
				const void * const * other_data ) throw (exception &);
	
	/**@fn
	 * @brief
	 * Resets the object.
	 **/
	void reset ( void );

	/**@fn
	 * @param[in] sqrt_q_0 : \f$ [Q^0]^{\frac{1}{2}}\f$
	 * @param[in] nb_blocks : number of blocks
	 * @param[in] block_sizes : sizes of blocks
	 * @param[in] block_rows : row ids of blocks
	 * @param[in] block_hypotheses : hypotheses on block
	 * @param[in] other_data : other parameters
	 * @brief
	 * Setup
	 **/
	int setup (	const gsl_matrix * sqrt_q_0,
				const gsl_matrix * p,
				unsigned int nb_blocks,
				const unsigned int * const * block_rows,
				const unsigned int * block_sizes,
				const unsigned int * block_hypotheses,
				const void * const * other_data );
	
	/**@fn
	 * @param[out] sqrt_q : estimation of sq(Q)
	 * @param[in] f : estimated F
	 * @param[in] sqrt_sum_ :
	 * @brief
	 * Estimate F
	 * 
	 **/
	void estimate(	gsl_matrix * sqrt_q,
					const gsl_matrix * f,
					const gsl_matrix * sqrt_sum,
					unsigned int nb_observations  ) const;
	
	/**@fn
	 * @brief
	 * Destructor.
	 **/
	~estimator ( void );
	
	/**@fn
	 * @return
	 * \f$n_t\f$
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}
	
	/**@fn
	 * @return
	 * \f$ [Q_0]^{\frac{1}{2}} \f$
	 * 
	 **/
	inline const gsl_matrix * sqrt_q_0() const
	{
		return _sqrt_q_0;
	}
	
	/**@fn
	 * @return
	 * Nb of blocks
	 **/
	inline unsigned int nb_blocks() const
	{
		return _nb_blocks;
	}
	
	/**@fn
	 * @return
	 * row ids of blocks
	 **/
	inline const unsigned int * const * block_rows() const
	{
		return _block_rows;
	}
	
	/**@fn
	 * @return
	 *  sizes of blocks
	 **/
	inline const unsigned int * block_sizes() const
	{
		return _block_sizes;
	}
	
	/**@fn
	 * @return
	 * hypotheses on block
	 **/
	inline const unsigned int * block_hypotheses() const
	{
		return _block_hypotheses;
	}

	/**@fn
	 * @return
	 * other parameters
	 **/
	inline const void * const * other_data() const
	{
		return _other_data;
	}
	
protected:
	/**@fn void  tkalman :: f_estimation :: initialize();
	 * @brief
	 * Object initialization
	 **/
	void initialize();
	
	/**@fn void  tkalman :: f_estimation :: free();
	 * @brief
	 * Frees object memory.
	 **/
	void free();
	
	/**@fn void  tkalman :: f_estimation :: alloc();
	 * @brief
	 * Allocates object memory.
	 **/
	void alloc();

	unsigned int _size_t;
	const gsl_matrix * _sqrt_q_0;
	const gsl_matrix * _p;

	unsigned int _nb_blocks;
	const unsigned int * const * _block_rows;
	const unsigned int * _block_sizes;
	const unsigned int * _block_hypotheses;
	const void * const * _other_data;
	
	void ** _block_parameters;
	function_set ** _f_set;
	void ** _estimators;
	gsl_matrix ** _projectors;

	mutable q_estimation :: workspace * w;


};



};

};


#endif
