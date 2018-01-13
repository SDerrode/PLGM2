#ifndef _F_STATE_WORKSPACE_HPP_
#define _F_STATE_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h> 
namespace equivalence
{
	
class f_state_workspace : public tkalman::workspace
{

public:
/**@fn tkalman :: workspace :: workspace(	unsigned int size_x,
											unsigned int size_y);

 * @param[in] size_x : size of x
 * @param[in] size_y : size of y
 * @brief
 * Constructor
 **/
f_state_workspace( 	unsigned int size_x, 
						unsigned int size_y );
						
						
/**@fn tkalman :: ~workspace();
 * @brief
 * Destructor
 **/
virtual ~f_state_workspace();


/**@fn
 * @return
 * \f$\mat[M]{t,t}{1}\f$, \f$(n_t by n_t)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_tt_1()
{
	return _mat_tt_1;
}


/**@fn
 * @return
 * \f$\mat[M]{x,x}{1}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_1()
{
	return _mat_xx_1;
}


/**@fn
 * @return
 * \f$\mat[M]{tx,tx}{1}\f$, \f$(n_x n_t by n_x n_t)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_tx_tx_1()
{
	return _mat_tx_tx_1;
}

/**@fn
 * @return
 * \f$\mat[M]{tx,tx}{2}\f$, \f$(n_x n_t by n_x n_t)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_tx_tx_2()
{
	return _mat_tx_tx_2;
}


/**@fn
 * @return
 * \f$\mat[M]{x,t}{1}\f$, \f$(n_x by n_t)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xt_1()
{
	return _mat_xt_1;
}


/**@fn
 * @return
 * view on \f$\mat[M]{x,t}{1}\f$, from \f$ (0, n_x) \f$ to \f$ (n_x -1, n_t -1) \f$
 * 
 **/
inline gsl_matrix * mat_xt_1_xy()
{
	return &_mat_xt_1_xy;
}

/**@fn
 * @return 
 * \f$\vect[V]{n_x n_t}\f$, \f$(n_x n_t)\f$-vector
 **/
inline gsl_vector * vect_xt_1()
{
	return _vect_xt_1;
}


/**@fn
 * @return 
 * \f$\vect[V]{n_x n_t}\f$, \f$(n_x n_t)\f$-vector
 **/
inline gsl_vector * vect_xt_2()
{
	return _vect_xt_2;
}

/**@fn
 * @return
 * \f$n_xn_t\f$-permutation
 **/
inline gsl_permutation * perm_xt()
{
	return _perm_xt;
}



protected:
/**@fn
 * @brief
 * This function sets object attributes to 0.
 **/
virtual void initialize();

gsl_matrix 	*_mat_tt_1,
			*_mat_xx_1,
			*_mat_tx_tx_1,
			*_mat_tx_tx_2,
			*_mat_xt_1,
			_mat_xt_1_xy;

gsl_vector 	*_vect_xt_1,
			*_vect_xt_2;
			
gsl_permutation *_perm_xt;

};
	
	
};

#endif
