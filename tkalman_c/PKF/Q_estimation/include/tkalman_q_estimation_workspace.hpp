#ifndef _TKALMAN_Q_ESTIMATION_WORKSPACE_HPP_
#define _TKALMAN_Q_ESTIMATION_WORKSPACE_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
namespace q_estimation
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
	
	protected: 
		gsl_matrix * _mat_tt_1;
	public: 
		/**@fn
		 * @return
		 * allocated \f$(n_t by n_t)\f$-matrix for \f$F' = PF\f$.
		 * 
		 **/
		inline gsl_matrix * f_eq()
		{
			return _mat_tt_1;
		}
		
	protected:
		gsl_matrix * _mat_2t_2t_1;
		
	public:
		/**@fn
		 * @return
		 * allocated \f$(2n_t by 2n_t)\f$-matrix for \f$sq(C_P)\f$.
		 * 
		 **/
		inline gsl_matrix * sqrt_c_eq()
		{
			return _mat_2t_2t_1;
		}
		
	protected: 
		gsl_matrix * _mat_tt_2;
	public: 
		/**@fn
		 * @return
		 * allocated \f$(n_t by n_t)\f$-matrix for \f$sq(Q')\f$.
		 * 
		 **/
		inline gsl_matrix * sqrt_q_eq()
		{
			return _mat_tt_2;
		}
		
	protected: 
		gsl_matrix * _mat_tt_3;
	public: 
		/**@fn
		 * @param[in] size_i : size of block
		 * @return
		 * allocated \f$(n_t by n_t)\f$-matrix for \f$F'_i\f$.
		 * 
		 **/
		gsl_matrix f_i( unsigned int size_i);
		
	protected: 
		gsl_matrix * _mat_tt_4;
	public: 
		/**@fn
		 * @return
		 * allocated \f$(n_t by n_t)\f$-matrix for \f$sq(Q_i')\f$.
		 * 
		 **/
		gsl_matrix sqrt_q_i( unsigned int size_i);
		
	protected:
		gsl_matrix * _mat_2t_2t_2;
		
	public:
		/**@fn
		 * @return
		 * allocated \f$(2n_t by 2n_t)\f$-matrix for \f$sq(C_i^P)\f$.
		 * 
		 **/
		gsl_matrix sqrt_c_i( unsigned int size_i);
		
		/**@fn
		 * @return
		 * allocated \f$(2n_t by 2n_t)\f$-matrix for \f$sq(C_i^P)\f$.
		 * 
		 **/
		gsl_matrix sqrt_c_i_2t_tpi( unsigned int size_i);

	protected:
		gsl_matrix 	*_mat_2t_2t_3,
					_mat_2t_2t_3_view_11;
		
	public:
		/**@fn
		 * @return
		 * allocated \f$(2n_t by 2n_t)\f$-matrix for \f$sq(C_i^P)\f$.
		 * 
		 **/
		gsl_matrix mat_2t_tpi_1( unsigned int size_i );
		gsl_matrix mat_2t_tpi_1_view_00( unsigned int size_i );
		gsl_matrix mat_2t_tpi_1_view_11( unsigned int size_i );
		inline gsl_matrix * mat_2t_2t_1()
		{
			return _mat_2t_2t_3;
		}

		inline gsl_matrix * mat_2t_2t_1_view_11()
		{
			return &_mat_2t_2t_3_view_11;
		}

	protected:
		gsl_vector * _vect_2t;
		
	public:
		inline gsl_vector * vect_2t()
		{
			return _vect_2t;
		}
		
		gsl_vector vect_tpi(unsigned int i);
		
};
	
};
};







#endif
