#ifndef _TKALMAN_Q_ESTIMATION_T3_BLOCK_PARAMETERS_HPP_
#define _TKALMAN_Q_ESTIMATION_T3_BLOCK_PARAMETERS_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
namespace q_estimation
{
namespace t3_block
{
/**@class tkalman :: f_estimation :: t1_block :: parameters
 * @brief
 * Parameters for partial estimation of F.
 * 
 **/
class parameters
{
public:
	/**@fn tkalman :: f_estimation :: t1_block :: parameters :: parameters( 	unsigned int size_i, 
																				unsigned int size_t ) throw ( exception &);
	 * @param[in] size_i : \f$n_i\f$
	 * @param[in] size_t : \f$n_t\f$
	 * @brief
	 * Constructor
	 **/
	parameters( 	unsigned int size_i, 
					unsigned int size_t ) throw ( exception &);

	/**@fn int tkalman :: f_estimation :: t1_block :: parameters :: set( const gsl_matrix * m );
	 * @param[in] m : \f$ M_i \f$
	 * @brief
	 * Set parameters
	 * @return 
	 * - 1 if m == NULL <=> ? or rk(m) < size_g <=> :(
	 * - 0 <=> :) 
	 **/
	int set( const gsl_matrix * const * matrices,
			 const unsigned int * const * row_ids,
			 unsigned int nb_blocks,
			 unsigned int block_sizes );

	/**@fn tkalman :: f_estimation :: t1_block :: parameters :: ~parameters();
	 * @brief
	 * Destructor
	 * 
	 **/
	~parameters();
	
	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_t() const
	 * @brief
	 * \f$n_t\f$
	 * 
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}

	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_i() const
	 * @brief
	 * \f$n_i\f$
	 * 
	 **/
	inline unsigned int size_i() const
	{
		return _size_i;
	}
	
	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_i() const
	 * @brief
	 * Block sizes
	 * 
	 **/
	inline unsigned int size_block() const
	{
		return _size_block;
	}
	
	/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: parameters :: size_i() const
	 * @brief
	 * Number of blocks
	 * 
	 **/
	inline unsigned int nb_blocks() const
	{
		return _nb_blocks;
	}
	
	/**@fn
	 * @param[in] i : 
	 * @return
	 * matrix #i
	 * 
	 **/
	const gsl_matrix * matrices( unsigned int i ) const;
	
	/**@fn
	 * @param[in] i : 
	 * @return
	 * inverse of matrix #i
	 * 
	 **/
	const gsl_matrix * matrix_inverses( unsigned int i ) const;
	
	/**@fn
	 * @param[in] i : 
	 * @return
	 * Projector #i
	 * 
	 **/
	const gsl_matrix * projectors( unsigned int i ) const;
	
protected:
	/**@fn void tkalman :: f_estimation :: t1_block :: free();
	 * @brief
	 * Free memory
	 **/
	void free();

	/**@fn void tkalman :: f_estimation :: t1_block :: initialize();
	 * @brief
	 * Set object attributes to 0.
	 **/
	void initialize();

	unsigned int 	_size_i,
					_size_t,
					_size_block,
					_nb_blocks;
					
	const gsl_matrix * const * _matrices;
	gsl_matrix ** _inv_matrices;
	gsl_matrix ** _projectors;

};
};
};
};



#endif
