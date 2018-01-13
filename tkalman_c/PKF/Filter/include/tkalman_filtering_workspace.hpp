#ifndef TKALMAN_FILTERING_WORKSPACE_HPP
#define TKALMAN_FILTERING_WORKSPACE_HPP
#include "tkalman_workspace.hpp"
#include <gsl/gsl_permutation.h>
#include "../../gsl/lib_PKF_gsl.hpp"
namespace tkalman
{

/**@class tkalman :: filtering_workspace 
 * filtering workspace
 * 
 **/
class filtering_workspace : public workspace
{
public:

/**@fn tkalman :: filtering_workspace :: filtering_workspace ( 	unsigned int size_x, 
																unsigned int size_y );
 * @param size_x : size of x
 * @param size_y : size of y
 * @brief
 * Constructor
 **/
filtering_workspace ( 	unsigned int size_x, 
						unsigned int size_y ) throw( exception & );

/**@fn tkalman :: filtering_workspace :: ~filtering_workspace();
 * @brief
 * Destructor
 **/
~filtering_workspace();

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tpy_tpy()
 * @return
\f$M\f$, allocated \f$ ( n_t + n_y, n_t + n_y ) \f$-matrix
 **/
inline gsl_matrix * mat_tpy_tpy()
{
	return _mat_tpy_tpy;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tpy_tpy_view_00()
 * @return
	 \f$M^{y,y}\f$, matrix view on \f$M\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_y -1, n_y - 1) \f$
 **/
inline gsl_matrix * mat_tpy_tpy_view_00()
{
	return  &_mat_tpy_tpy_view_00;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tpy_tpy_view_01()
 * @return
	 \f$M^{y,t}\f$, matrix view on \f$M\f$,  starting at \f$ (0,n_y) \f$, ending at \f$ (n_y -1, n_y + n_t - 1) \f$
 **/
inline gsl_matrix * mat_tpy_tpy_view_01()
{
	return  &_mat_tpy_tpy_view_01;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tpy_tpy_view_10()
 * @return
	 \f$M^{t,y}\f$, matrix view on \f$M\f$,  starting at \f$ (n_y, 0) \f$, ending at \f$ (n_y + n_t - 1, n_y - 1) \f$
 **/
inline gsl_matrix * mat_tpy_tpy_view_10()
{
	return  &_mat_tpy_tpy_view_10;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tpy_tpy_view_11()
 * @return
	 \f$M^{t,t}\f$, matrix view on \f$M\f$,  starting at \f$ (n_y, n_y) \f$, ending at \f$ (n_y + n_t - 1, n_y + n_t - 1) \f$
 **/
inline gsl_matrix * mat_tpy_tpy_view_11()
{
	return  &_mat_tpy_tpy_view_11;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_xy()
 * @return
	\f$M\f$, allocated \f$ ( n_x, n_y ) \f$-matrix
 **/
inline gsl_matrix * mat_xy()
{
	return &_mat_xy;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tt()
 * @return
\f$M\f$, allocated \f$ ( n_t, n_t ) \f$-matrix
 **/
inline gsl_matrix * mat_tt()
{
	return &_mat_tt;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tt_view_00()
 * @return
	 \f$M^{y,y}\f$, matrix view on \f$M\f$,  starting at \f$ (0,0) \f$, ending at \f$ (n_y -1, n_y - 1) \f$
 **/
inline gsl_matrix * mat_tt_view_00()
{
	return  &_mat_tt_view_00;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tt_view_01()
 * @return
	 \f$M^{y,x}\f$, matrix view on \f$M\f$,  starting at \f$ (0, n_y) \f$, ending at \f$ (n_y -1, n_t - 1) \f$
 **/
inline gsl_matrix * mat_tt_view_01()
{
	return  &_mat_tt_view_01;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tt_view_10()
 * @return
	 \f$M^{x,y}\f$, matrix view on \f$M\f$,  starting at \f$ (n_y, 0) \f$, ending at \f$ (n_t - 1, n_y - 1) \f$
 **/
inline gsl_matrix * mat_tt_view_10()
{
	return  &_mat_tt_view_10;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_tt_view_11()
 * @return
	 \f$M^{x,x}\f$, matrix view on \f$M\f$,  starting at \f$ (n_y, n_y) \f$, ending at \f$ (n_t - 1, n_t - 1) \f$
 **/
inline gsl_matrix * mat_tt_view_11()
{
	return  &_mat_tt_view_11;
}

/**@fn inline gsl_matrix * tkalman :: filtering_workspace :: mat_ty()
 * @return
\f$M\f$, allocated \f$ ( n_t, n_y ) \f$-matrix
 **/
inline gsl_matrix * mat_ty()
{
	return _mat_ty;
}

/**@fn inline gsl_permutation * tkalman :: filtering_workspace :: perm_y() 
 * @return
 * \f$(n_y)\f$-permutation
 **/
inline gsl_permutation *  perm_y() 
{
	return _perm_y;
}

/**@fn inline gsl_vector * tkalman :: filtering_workspace :: vect_tpy()
 * @return
 * \f$(n_t + n_y)\f$-vector
 * 
 **/
inline gsl_vector * vect_tpy()
{
	return _vect_tpy;
}

/**@fn inline gsl_vector * tkalman :: filtering_workspace :: vect_t()
 * @return
 * \f$(n_t)\f$-vector
 * 
 **/
inline gsl_vector * vect_t()
{
	return &_vect_t;
}

inline gsl_pseudo_inverse_workspace * psi_workspace()
{
	return _psi_workspace;
}


protected:
/**@fn void tkalman :: filtering_workspace :: free();
 * @brief
 * This function frees memory.
 */
void free();
/**@fn void tkalman :: filtering_workspace :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();
/**@fn void tkalman :: filtering_workspace :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

gsl_matrix * _mat_tpy_tpy;
gsl_matrix * _mat_ty;
gsl_permutation * _perm_y;
gsl_vector * _vect_tpy;

			
gsl_matrix _mat_tt;
gsl_matrix _mat_tt_view_00;
gsl_matrix _mat_tt_view_01;
gsl_matrix _mat_tt_view_10;
gsl_matrix _mat_tt_view_11;

gsl_matrix _mat_tpy_tpy_view_00;
gsl_matrix _mat_tpy_tpy_view_01;
gsl_matrix _mat_tpy_tpy_view_10;
gsl_matrix _mat_tpy_tpy_view_11;
gsl_matrix _mat_xy;

gsl_vector _vect_t;
gsl_pseudo_inverse_workspace * _psi_workspace;

};

};

#endif
