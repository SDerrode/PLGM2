#ifndef TKALMAN_EM_ESTIMATOR_WORKSPACE_HPP
#define TKALMAN_EM_ESTIMATOR_WORKSPACE_HPP
#include "../../Filter/lib_PKF_filter.hpp"

namespace tkalman
{
namespace EM
{
class estimator_workspace : public workspace
{
	public:
	/**@fn tkalman :: estimator_workspace :: estimator_workspace(	unsigned int size_x,
																	unsigned int size_y);

	 * @param[in] size_x : size of x
	 * @param[in] size_y : size of y
	 * @brief
	 * Constructor
	 **/
	estimator_workspace (	unsigned int size_x,
							unsigned int size_y ) throw ( exception & );

	/**@fn tkalman :: sum_workspace :: ~sum_workspace();
	 * @brief
	 * Destructor
	 **/
	~estimator_workspace();
	
	inline gsl_matrix * mat_4t2t()
	{
		return _mat_4t2t;
	}
	
	inline gsl_matrix * mat_4t2t_view_1()
	{
		return &_mat_4t2t_view_1;
	}
	
	inline gsl_matrix * mat_4t2t_view_0()
	{
		return &_mat_4t2t_view_0;
	}
	
	inline gsl_matrix * mat_2tp1_t()
	{
		return _mat_2tp1_t;
	}
	
	inline gsl_matrix * mat_2tp1_t_view_0()
	{
		return &_mat_2tp1_t_view_0;
	}
	
	inline gsl_matrix * mat_2tp1_t_view_1()
	{
		return &_mat_2tp1_t_view_1;
	}
	
	inline gsl_vector * vect_2t()
	{
		return _vect_2t;
	}
	
	inline gsl_vector * vect_t()
	{
		return _vect_t;
	}
	
	inline gsl_vector * mat_2tp1_t_view_2()
	{
		return &_mat_2tp1_t_view_2;
	}
	inline tkalman :: parameters & pkf_parameters()
	{
		return *_pkf_parameters;
	}
	
	protected:
		gsl_matrix 	*_mat_4t2t,
					_mat_4t2t_view_1,
					_mat_4t2t_view_0,
					*_mat_2tp1_t,
					_mat_2tp1_t_view_0,
					_mat_2tp1_t_view_1;	
						
		gsl_vector 	*_vect_2t,
					*_vect_t,
					_mat_2tp1_t_view_2;
					
		tkalman :: parameters * _pkf_parameters;
		/**@fn void tkalman :: sum_workspace  :: free( );
		 * @brief
		 * This function frees memory.
		 */
		void free();

		/**@fn void tkalman :: sum_workspace  :: alloc();
		 * @brief
		 * This function allocates attributes.
		 */
		void alloc();

		/**@fn void tkalman :: sum_workspace  :: initialize();
		 * @brief
		 * This function sets object attributes to 0.
		 */
		void initialize();
};

	
	
	
	
	
};


};

#endif
