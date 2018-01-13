#ifndef _Q_DECORRELATION_WORKSPACE_HPP_
#define _Q_DECORRELATION_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h> 
namespace equivalence
{
	
class Q_decorrelation_workspace : public tkalman :: workspace
{
	public:
		/**@fn tkalman :: workspace :: workspace(	unsigned int size_x,
													unsigned int size_y);

		 * @param[in] size_x : size of x
		 * @param[in] size_y : size of y
		 * @brief
		 * Constructor
		 **/
		Q_decorrelation_workspace( 	unsigned int size_x, 
									unsigned int size_y );
										
		/**@fn tkalman :: ~workspace();
		 * @brief
		 * Destructor
		 **/
		virtual ~Q_decorrelation_workspace();
			
		/**@fn
		 * @return
		 * \f$(n_t by n_t)\f$-matrix, \f$\mat[M]{1}{}\f$
		 * 
		 **/
		inline gsl_matrix * mat_tt_1()
		{
			return _mat_tt_1;
		}	
						
		/**@fn
		 * @return
		 * view on \f$\mat[M]{1}{}\f$, from \f$(0, n_x)\f$ to \f$(n_x-1, n_t - 1)\f$
		 * 
		 **/
		inline gsl_matrix * mat_tt_1_xy()
		{
			return &_mat_tt_1_xy;
		}
		
		/**@fn
		 * @return
		 * \f$(n_t by n_t)\f$-matrix, \f$\mat[M]{2}{}\f$
		 * 
		 **/
		inline gsl_matrix * mat_tt_2() 
		{
			return _mat_tt_2;
		}
		
		/**@fn
		 * @return
		 * view on \f$\mat[M]{2}{}\f$, from \f$(0, 0)\f$ to \f$(n_x-1, n_x - 1)\f$
		 * 
		 **/
		inline gsl_matrix * mat_tt_2_xx()
		{
			return &_mat_tt_2_xx;
		}
		
		/**@fn
		 * @return
		 * \f$(n_x by n_x)\f$-matrix, \f$\mat[M]{3}{}\f$
		 * 
		 **/
		inline gsl_matrix * mat_xx_1()
		{
			return _mat_xx_1;
		}
		
		/**@fn
		 * @return
		 * \f$n_t\f$-vector, \f$\vect[V]{1}\f$
		 * 
		 **/
		inline gsl_vector * vect_t_1()
		{
			return _vect_t_1;
		}
		
		/**@fn
		 * @return
		 * \f$n_x\f$-permutation, \f$\perm[P]{1}\f$
		 * 
		 **/
		inline gsl_permutation * perm_x()
		{
			return _perm_x;
		}
		
		
	protected:
		/**@fn
		 * @brief
		 * This function sets object attributes to 0.
		 **/
		virtual void initialize();
		gsl_matrix 	* _mat_tt_1,
					_mat_tt_1_xy,
					* _mat_tt_2,
					_mat_tt_2_xx,
					* _mat_xx_1;
					
		gsl_vector  * _vect_t_1;
		
		gsl_permutation * _perm_x;
					
	
};
	
};


#endif
