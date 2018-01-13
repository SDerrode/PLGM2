#ifndef _TKALMAN_Q_ESTIMATION_T2_BLOCK_WORKSPACE_HPP_
#define _TKALMAN_Q_ESTIMATION_T2_BLOCK_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
namespace tkalman
{
namespace q_estimation
{
namespace t2_block
{
/**@class
 * @brief
 * Workspace prototype for Q estimation
 * 
 **/
class workspace : public tkalman :: workspace
{
public:
	/**@fn
	 * @param[in] size : block size
	 * @brief
	 * Constructor
	 * 
	 **/
	workspace ( unsigned int size,
				unsigned int size_t ) throw ( exception & );
 
	/**@fn
	 * @brief
	 * Return size of block.
	 * 
	 **/
	inline unsigned int size() const
	{
		return _size_x;
	}

	/**@fn
	 * @brief
	 * Destructor
	 *
	 **/
	~workspace();
	
	/**@fn
	 * @brief
	 * \f$(n_t by 2 n_t)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_i_tpi()
	{
		return _mat_i_tpi;
	}
	
	
	/**@fn
	 * @brief
	 * F view on \f$(n_t by 2 n_t)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_i_tpi_view_F()
	{
		return &_mat_i_tpi_view_F;
	}
	
	/**@fn
	 * @brief
	 * \f$(2n_t by n_t)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_tpi_i_1()
	{
		return _mat_tpi_i_1;
	}

	/**@fn
	 * @brief
	 * \f$(2n_t by n_t)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_tpi_i_2()
	{
		return _mat_tpi_i_2;
	}

	/**@fn
	 * @brief
	 * \f$(n_i by n_i)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_ii()
	{
		return _mat_ii;
	}


	
protected:

	/**@fn
	 * @brief
	 * This function sets object attributes to 0.
	 **/
	void initialize();
	/**@fn void tkalman :: f_estimation :: tensorial_constraints :: estimator ::  alloc();
	 * @brief
	 * memory allocation
	 **/
	void alloc();

	/**@fn void tkalman :: f_estimation :: tensorial_constraints :: estimator :: free();
	 * @brief
	 * Set object attributes to 0.
	 **/
	void free();

	gsl_matrix 	*_mat_i_tpi,
				_mat_i_tpi_view_F,
				*_mat_tpi_i_1,
				*_mat_tpi_i_2,
				*_mat_ii;

};
	
};
	
};

};

#endif
