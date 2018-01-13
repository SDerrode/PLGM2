#ifndef _TKALMAN_F_ESTIMATION_WORKSPACE_HPP_
#define _TKALMAN_F_ESTIMATION_WORKSPACE_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
namespace f_estimation
{
/**@class tkalman :: f_estimation_workspace
 * @brief
 * workspace for F estimation in Pairwise Kalman EM algorithm with linear constraints
 * 
 * 
 **/
class workspace
{
public:
	/**@fn tkalman :: f_estimation_workspace :: f_estimation_workspace( unsigned int size_t );
	 * @param[in] size_t : dim. of t
	 * @brief
	 * Constructor
	 **/
	workspace( unsigned int size_t ) throw ( exception & );

	/**@fn tkalman :: f_estimation_workspace :: ~f_estimation_workspace()
	 * @brief
	 * Destructor
	 * 
	 **/
	~workspace();

	/**@fn inline unsigned int tkalman :: f_estimation_workspace :: size_t() const
	 * @return
	 * Size of t
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}
	
	/**@fn
	 * @return
	 * \f$(2n_t by 2n_t) matrix\f$
	 * 
	 **/
	inline gsl_matrix * mat_2t_2t_1()
	{
		return _mat_2t_2t_1;
	}
	
	/**@fn
	 * @return
	 * View starting at \f$(0, 0)\f$ to \f$(n_t-1, n_t -1)\f$ on mat_2t_2t_1
	 * 
	 **/
	inline gsl_matrix * mat_2t_2t_1_view_00()
	{
		return &_mat_2t_2t_1_view_00;
	}
	
	/**@fn
	 * @return
	 * View starting at \f$(0, n_t)\f$ to \f$(n_t-1, 2n_t -1)\f$ on mat_2t_2t_1
	 * 
	 **/
	inline gsl_matrix * mat_2t_2t_1_view_01()
	{
		return &_mat_2t_2t_1_view_01;
	}
	
	/**@fn
	 * @return
	 * \f$(2n_t by 2n_t) matrix\f$
	 * 
	 **/
	inline gsl_matrix * sqrt_c_bis()
	{
		return _mat_2t_2t_2;
	}
	
	/**@fn
	 * @return
	 * \f$ (2n_t) \f$-vector
	 * 
	 **/
	inline gsl_vector * vect_2t()
	{
		return _vect_2t;
	}
	
	/**@fn gsl_matrix * m( unsigned int size_i );
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(2n_t, n_t + n_i)-matrix\f$
	 **/
	gsl_matrix m( unsigned int size_i );
	
	/**@fn gsl_matrix * m_view_11( unsigned int size_i );
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * View on mat_2t_2t_1 starting at \f$(n_t, n_t)\f$ to \f$(n_t + n_i - 1, n_t + n_i - 1)\f$ on mat_2t_2t_1
	 **/
	gsl_matrix m_view_11( unsigned int size_i );
	
	/**@fn gsl_matrix * sqrt_sum( unsigned int size_i );
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_t + n_i, n_t + n_i)-matrix\f$
	 **/
	gsl_matrix sqrt_sum( unsigned int size_i );
	
	/**@fn gsl_matrix * sqrt_sum( unsigned int size_i );
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_t + n_i, n_t + n_i)-matrix\f$
	 **/
	gsl_matrix sqrt_sum_mat_2t_tpi( unsigned int size_i );
	
	
	/**@fn gsl_matrix * sqrt_sum_00( );
	 * @return
	 * Matrix view on sqrt_sum starting at \f$(0,0)\f$ ending at \f$(n_t - 1,n_t - 1)\f$
	 **/
	inline gsl_matrix * sqrt_sum_00( )
	{
		return &_mat_2t_2t_3_view_00;
	}
	
	/**@fn gsl_matrix * sqrt_sum_01( unsigned int size_i );
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * Matrix view on sqrt_sum starting at \f$(0,n_t)\f$ ending at \f$(n_t - 1,n_t + n_i - 1)\f$
	 **/
	gsl_matrix sqrt_sum_01( unsigned int size_i );
	
	/**
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_i by n_t)-matrix\f$
	 **/
	gsl_matrix f( unsigned int size_i );
	
	/**
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_i + n_t)\f$-vector
	 **/
	gsl_vector vect( unsigned int size_i );
	
	
	/**
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_i)\f$-vector
	 **/
	gsl_vector s_vect( unsigned int size_i );
	
	
	/**
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_t \times n_i)\f$-matrix
	 * 
	 **/
	gsl_matrix mat_ti( unsigned size_i );
	
	/**
	 * @param size_i : \f$ n_i \f$
	 * @return
	 * \f$(n_t \times n_i)\f$-matrix
	 * 
	 **/
	gsl_matrix sqrt_q_i( unsigned size_i );
	
	
protected:
	/**@fn void  tkalman :: f_estimation_workspace :: initialize();
	 * @brief
	 * Object initialization
	 **/
	void initialize();
	
	/**@fn void  tkalman :: f_estimation_workspace :: free();
	 * @brief
	 * Frees object memory.
	 **/
	void free();
	
	/**@fn void  tkalman :: f_estimation_workspace :: alloc();
	 * @brief
	 * Allocates object memory.
	 **/
	void alloc();
	
	
	unsigned int _size_t;
	
	gsl_matrix 	*_mat_2t_2t_1,//M
				_mat_2t_2t_1_view_00,
				_mat_2t_2t_1_view_01,
				*_mat_2t_2t_2,//sq(Cb)
				*_mat_2t_2t_3,
				_mat_2t_2t_3_view_00,
				*_mat_tt_1, //projector & F
				*_mat_tt_2;
	
	gsl_vector * _vect_2t;
	
	
	

};
	
};
};



#endif
