#ifndef _TKALMAN_CONSTANTS_WORKSPACE_HPP_
#define _TKALMAN_CONSTANTS_WORKSPACE_HPP_
#include "tkalman_workspace.hpp"
#include <gsl/gsl_permutation.h> 
#include "../../gsl/lib_PKF_gsl.hpp"
namespace tkalman
{
/**@class tkalman :: constants_workspace 
 * @brief
 * Workspace for constant computing.
 * 
**/
class constants_workspace : public workspace
{
public:
/**@fn tkalman :: constants_workspace :: constants_workspace(	unsigned int size_x,
																unsigned int size_y ); 
 * @param size_x : size of x
 * @param size_y : size of y
 * @brief
 * Constructor
 **/
constants_workspace( 	unsigned int size_x,
						unsigned int size_y ) throw( exception & );
/**tkalman :: constants_workspace :: ~constants_workspace( ); 
 * @brief
 * Destructor
 * 
 **/
~constants_workspace();

/**@fn gsl_matrix * tkalman :: constants_workspace :: mat_tt()
 * @return
 \f$M\f$, allocated \f$ ( n_t, n_t) \f$-matrix
 **/
inline gsl_matrix * mat_tt()
{
	return _mat_tt;
}

/**@fn gsl_matrix * tkalman :: constants_workspace :: mat_tt_yy()
 * @return
 \f$M^{y,y}\f$, matrix view on \f$M\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_y -1, n_y - 1) \f$
 **/
inline gsl_matrix * mat_tt_yy()
{
	return &_mat_tt_yy;
}

/**@fn gsl_matrix * tkalman :: constants_workspace :: mat_tt_xy()
 * @return
 \f$M^{x,y}\f$, matrix view on \f$M\f$,  starting at \f$ (n_y, 0) \f$, ending at \f$ (n_t - 1, n_y - 1) \f$
 **/
inline gsl_matrix * mat_tt_xy()
{
	return &_mat_tt_xy;
}

/**@fn gsl_matrix * tkalman :: constants_workspace :: mat_tt_yx()
 * @return
 \f$M^{y,x}\f$, matrix view on \f$M\f$,  starting at \f$ (0, n_y) \f$, ending at \f$ (n_y -1, n_t - 1) \f$
 **/
inline gsl_matrix * mat_tt_yx()
{
	return &_mat_tt_yx;
}

/**@fn gsl_matrix * tkalman :: constants_workspace :: mat_tt_xx()
 * @return
 \f$M^{x,x}\f$, matrix view on \f$M\f$,  starting at \f$ (n_y, n_y) \f$, ending at \f$ (n_t - 1, n_t - 1) \f$
 **/
inline gsl_matrix * mat_tt_xx()
{
	return &_mat_tt_xx;
}

/**@fn gsl_vector * tkalman :: constants_workspace :: vect_t()
 * @return 
 * allocated \f$ n_t-\f$vector.
 **/
inline gsl_vector * vect_t()
{
	return _vect_t;
}

/**@fn gsl_permutation * tkalman :: constants_workspace :: perm_y()
 * @return 
 * allocated \f$ n_y-\f$ permutation.
 **/
inline gsl_permutation * perm_y()
{
	return _perm_y;
}

inline gsl_pseudo_inverse_workspace * psi_workspace()
{
	return _psi_workspace;
}

protected:
/**@fn void tkalman_constants :: free();
 * @brief
 * This function frees memory.
 */
void free();
/**@fn void tkalman_constants :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();
/**@fn void tkalman_constants :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();


gsl_matrix 	*_mat_tt,
			_mat_tt_yy,
			_mat_tt_yx,
			_mat_tt_xy,
			_mat_tt_xx;
gsl_vector * _vect_t;
gsl_permutation * _perm_y;
gsl_pseudo_inverse_workspace * _psi_workspace;
};

};
	


#endif
