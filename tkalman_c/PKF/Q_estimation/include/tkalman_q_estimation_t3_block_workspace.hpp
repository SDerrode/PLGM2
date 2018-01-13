#ifndef _TKALMAN_Q_ESTIMATION_T3_BLOCK_WORKSPACE_HPP_
#define _TKALMAN_Q_ESTIMATION_T3_BLOCK_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
namespace tkalman
{
namespace q_estimation
{
namespace t3_block
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
	 * @param[in] size_i : block size
	 * @param[in] size_t : \f$ n_t \f$
	 * @param[in] size_b : \f$ n_b \f$
	 * @brief
	 * Constructor
	 * 
	 **/
	workspace ( unsigned int size_i,
				unsigned int size_t,
				unsigned int size_b) throw ( exception & );
 
	/**@fn
	 * @brief
	 * Return size of block.
	 * 
	 **/
	inline unsigned int size_i() const
	{
		return _size_x;
	}

	/**@fn
	 * @brief
	 * Size of subblock
	 * 
	 **/
	inline unsigned int size_b() const
	{
		return _size_b;
	}





	/**@fn
	 * @brief
	 * Destructor
	 *
	 **/
	~workspace();
	
	/**@fn
	 * @brief
	 * \f$(n_i by n_t + n_i)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_i_tpi()
	{
		return _mat_i_tpi;
	}
	
	
	/**@fn
	 * @brief
	 * F view on \f$(n_i by n_t + n_i)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_i_tpi_view_F()
	{
		return &_mat_i_tpi_view_F;
	}
	
	/**@fn
	 * @brief
	 * \f$(n_t + n_i by n_i)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_tpi_i_1()
	{
		return _mat_tpi_i_1;
	}

	/**@fn
	 * @brief
	 * \f$(n_t + n_i by n_b)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_tpi_b_1()
	{
		return _mat_tpi_b_1;
	}

	/**@fn
	 * @return 
	 * \f$( n_b + n_t + n_i by n_b)\f$-matrix
	 **/
	inline gsl_matrix * mat_tpipb_b()
	{
		return _mat_tpipb_b;
	}
		
	/**@fn
	 * @return
	 * View on \f$( n_b + n_t + n_i by n_b)\f$-matrix starting at \f$(0,0)\f$ ending at \f$(n_b - 1, n_b - 1)\f$
	 * 
	 **/
	inline gsl_matrix * mat_tpipb_b_view_00()
	{
		return &_mat_tpipb_b_view_00;
	}
	
	
	/**@fn
	 * @return
	 * View on \f$( n_b + n_t + n_i by n_b)\f$-matrix starting at \f$(n_b, 0)\f$
	 * 
	 **/
	inline gsl_matrix * mat_tpipb_b_view_10()
	{
		return &_mat_tpipb_b_view_10;
	}
	
	/**@fn
	 * @brief
	 * \f$(n_b by n_b)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_bb()
	{
		return _mat_bb;
	}

	/**@fn
	 * @brief
	 * \f$(n_i by n_b)\f$-matrix
	 * 
	 **/
	inline gsl_matrix * mat_bi()
	{
		return _mat_bi;
	}
	
	/**@fn
	 * @return 
	 * \f$(n_b)\f$-vector
	 **/
	inline gsl_vector * vect_b()
	{
		return _vect_b;
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

	unsigned int _size_b;
	gsl_matrix 	*_mat_i_tpi,
				_mat_i_tpi_view_F,
				*_mat_tpi_i_1,
				*_mat_tpi_b_1,
				*_mat_tpipb_b,
				_mat_tpipb_b_view_00,
				_mat_tpipb_b_view_10,
				*_mat_bb,
				*_mat_bi;
				
	gsl_vector * _vect_b;
	
};
	
};
	
};

};

















#endif
