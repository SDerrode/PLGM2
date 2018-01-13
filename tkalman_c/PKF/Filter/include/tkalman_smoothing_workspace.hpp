#ifndef _TKALMAN_SMOOTHING_WORKSPACE_HPP_
#define _TKALMAN_SMOOTHING_WORKSPACE_HPP_
#include "tkalman_workspace.hpp"
#include <gsl/gsl_permutation.h>
#include "../../gsl/lib_PKF_gsl.hpp"
namespace tkalman
{
/**@class tkalman :: smoothing_workspace
 * @brief
 * PK smoothing workspace 
 **/
class smoothing_workspace : public workspace
{
public:

/**@fn tkalman :: smoothing_workspace :: smoothing_workspace( 	unsigned int size_x, 
																unsigned int size_y );

 * @param : size_x : size of x
 * @param : size_y : size of y
 * @brief
 * Constructor
 **/
smoothing_workspace( 	unsigned int size_x, 
						unsigned int size_y ) throw ( exception & ); 
/**@fn tkalman :: smoothing_workspace :: ~smoothing_workspace( );
 * @brief
 * Destructor
 **/
~smoothing_workspace( );
//Accesseurs
/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x () 
 * @return
 * \f$M\f$, allocated \f$(3 n_x, 2 n_x)\f$-matrix
 **/
inline gsl_matrix * mat_3x2x () 
{
	return &_mat_3x2x;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x_view_00 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(0,0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x2x_view_00 () 
{
	return &_mat_3x2x_view_00;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x_view_01 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(0,n_x)\f$, ending at \f$(n_x - 1, 2n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x2x_view_01 () 
{
	return &_mat_3x2x_view_01;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x_view_10 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(n_x,0)\f$, ending at \f$(2 n_x - 1, n_x - 1)\f$ if
 **/
inline gsl_matrix * mat_3x2x_view_10 () 
{
	return &_mat_3x2x_view_10;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x_view_11 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(n_x,n_x)\f$, ending at \f$(2 n_x - 1, 2 n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x2x_view_11 () 
{
	return &_mat_3x2x_view_11;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x_view_20 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(2 n_x,0)\f$, ending at \f$(3 n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x2x_view_20 () 
{
	return &_mat_3x2x_view_20;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_3x2x_view_21 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(2 n_x,n_x)\f$, ending at \f$(3 n_x - 1, 2n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x2x_view_21 () 
{
	return &_mat_3x2x_view_21;
}

/**@fn inline gsl_vector * tkalman :: smoothing_workspace ::vect_2x() 
 * @return
 * allocated \f$(2 n_x)\f$-vector.
 **/
inline gsl_vector * vect_2x() 
{
	return &_vect_2x;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_xx () 
 * @return
 * allocated \f$(n_x, n_x)\f$-matrix.
 **/
inline gsl_matrix * mat_xx () 
{
	return &_mat_xx;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt () 
 * @return
 * \f$M\f$, allocated \f$(2 n_x + n_t, n_x + n_t)\f$-matrix
 **/
inline gsl_matrix * mat_2xpt_xpt () 
{
	return _mat_2xpt_xpt;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt_view_00 ()
 * @return
 * matrix view on \f$M\f$, starting at \f$(0,0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_xpt_view_00 () 
{
	return &_mat_2xpt_xpt_view_00;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt_view_01 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(0,n_x)\f$, ending at \f$(n_x - 1, n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_xpt_view_01 () 
{
	return &_mat_2xpt_xpt_view_01;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt_view_10 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(n_x,0)\f$, ending at \f$(n_x + n_t - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_xpt_view_10 () 
{
	return &_mat_2xpt_xpt_view_10;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt_view_11 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(n_x,n_x)\f$, ending at \f$(n_x + n_t - 1, n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_xpt_view_11 () 
{
	return &_mat_2xpt_xpt_view_11;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt_view_20 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(n_x + n_t,0)\f$, ending at \f$(2n_x + n_t - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_xpt_view_20 () 
{
	return &_mat_2xpt_xpt_view_20;
}

/**@fn inline gsl_matrix * tkalman :: smoothing_workspace ::mat_2xpt_xpt_view_21 () 
 * @return
 * matrix view on \f$M\f$, starting at \f$(n_x + n_t,n_x)\f$, ending at \f$(2n_x + n_t - 1, n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_xpt_view_21 () 
{
	return &_mat_2xpt_xpt_view_21;
}

inline gsl_pseudo_inverse_workspace * psi_workspace()
{
	return _psi_workspace;
}

/**@fn inline gsl_permutation * perm_x()
 * @return
 *  allocated \f$n_x\f$-permutation
 **/
inline gsl_permutation * perm_x()
{
	return _perm_x;
}

/**@fn inline gsl_vector * vect_xpt() 
 * @return
 * allocated \f$(n_x + n_t)\f$-vector.
 **/
inline gsl_vector * vect_xpt() 
{
	return _vect_xpt;
}

/**@fn inline gsl_matrix * mat_tx () 
 * @return
 * allocated \f$(n_t, n_x)\f$-matrix.
 **/
inline gsl_matrix * mat_tx () 
{
	return _mat_tx;
}

protected:

/**@fn void tkalman :: smoothing_workspace :: free();
 * @brief
 * This function frees memory.
 */
void free();
/**@fn void tkalman :: smoothing_workspace :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();
/**@fn void tkalman :: smoothing_workspace :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

gsl_matrix _mat_3x2x;
gsl_matrix _mat_3x2x_view_00;
gsl_matrix _mat_3x2x_view_01;
gsl_matrix _mat_3x2x_view_10;
gsl_matrix _mat_3x2x_view_11;
gsl_matrix _mat_3x2x_view_20;
gsl_matrix _mat_3x2x_view_21;
gsl_vector _vect_2x;
gsl_matrix _mat_xx;
gsl_matrix _mat_2xpt_xpt_view_00;
gsl_matrix _mat_2xpt_xpt_view_01;
gsl_matrix _mat_2xpt_xpt_view_10;
gsl_matrix _mat_2xpt_xpt_view_11;
gsl_matrix _mat_2xpt_xpt_view_20;
gsl_matrix _mat_2xpt_xpt_view_21;


gsl_permutation * _perm_x;
gsl_vector * _vect_xpt;
gsl_matrix * _mat_tx;
gsl_matrix * _mat_2xpt_xpt;
gsl_pseudo_inverse_workspace * _psi_workspace;
};



};

#endif
