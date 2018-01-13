#ifndef _TKALMAN_SUM_WORKSPACE_HPP_
#define _TKALMAN_SUM_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"

namespace tkalman
{

/**@class tkalman :: sum_workspace
 * @brief
 * Sum workspace
 * 
 **/
class sum_workspace : public workspace
{

public:

/**@fn tkalman :: sum_workspace :: sum_workspace(	unsigned int size_x,
													unsigned int size_y);

 * @param[in] size_x : size of x
 * @param[in] size_y : size of y
 * @brief
 * Constructor
 **/
sum_workspace (	unsigned int size_x,
				unsigned int size_y ) throw ( exception & );

/**@fn tkalman :: sum_workspace :: ~sum_workspace();
 * @brief
 * Destructor
 **/
~sum_workspace();

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt()
 * @return \f$M\f$, allocated \f$(2 n_x + n_t, 2 n_x + n_t) \f$-matrix
 **/
inline gsl_matrix * mat_2xpt_2xpt()
{
	return _mat_2xpt_2xpt;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt_view_00()
 * @return matrix view on \f$M\f$, starting at \f$(0,0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_2xpt_view_00()
{
	return &_mat_2xpt_2xpt_view_00;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt_view_10()
 * @return matrix view on \f$M\f$, starting at \f$(n_x,0)\f$, ending at \f$(n_x + n_t - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_2xpt_view_10()
{
	return &_mat_2xpt_2xpt_view_10;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt_view_11()
 * @return matrix view on \f$M\f$, starting at \f$(n_x,n_x)\f$, ending at \f$(n_x + n_t - 1, n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_2xpt_view_11()
{
	return &_mat_2xpt_2xpt_view_11;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt_view_11()
 * @return matrix view on \f$M\f$, starting at \f$(n_x,n_x)\f$, ending at \f$(n_x + n_t - 1, n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_2xpt_view_12()
{
	return &_mat_2xpt_2xpt_view_12;
}


/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt_view_21()
 * @return matrix view on \f$M\f$, starting at \f$(n_x + n_t,n_x)\f$, ending at \f$(2n_x + n_t - 1, n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_2xpt_view_21()
{
	return &_mat_2xpt_2xpt_view_21;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2xpt_2xpt_view_22()
 * @return matrix view on \f$M\f$, starting at \f$(n_x + n_t,n_x + n_t)\f$, ending at \f$(2n_x + n_t - 1, 2 n_x + n_t - 1)\f$
 **/
inline gsl_matrix * mat_2xpt_2xpt_view_22()
{
	return &_mat_2xpt_2xpt_view_22;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x()
 * @return \f$M\f$, allocated \f$(3 n_x, 3 n_x)\f$-matrix
 **/
inline gsl_matrix * mat_3x3x()
{
	return &_mat_3x3x;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x_view_00()
 * @return matrix view on \f$M\f$, starting at \f$(0,0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x3x_view_00()
{
	return &_mat_3x3x_view_00;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x_view_10()
 * @return matrix view on \f$M\f$, starting at \f$(n_x,0)\f$, ending at \f$(2 n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x3x_view_10()
{
	return &_mat_3x3x_view_10;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x_view_11()
 * @return  matrix view on \f$M\f$, starting at \f$(n_x,n_x)\f$, ending at \f$(2 n_x - 1, 2 n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x3x_view_11()
{
	return &_mat_3x3x_view_11;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x_view_12()
 * @return  matrix view on \f$M\f$, starting at \f$(n_x,2 n_x)\f$, ending at \f$(2 n_x - 1, 3n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x3x_view_12()
{
	return &_mat_3x3x_view_12;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x_view_21()
 * @return matrix view on \f$M\f$, starting at \f$(2 n_x,n_x)\f$, ending at \f$(3 n_x - 1, 2n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x3x_view_21()
{
	return &_mat_3x3x_view_21;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_3x3x_view_22()
 * @return matrix view on \f$M\f$, starting at \f$(2 n_x,2 n_x)\f$, ending at \f$(3 n_x - 1, 3n_x - 1)\f$
 **/
inline gsl_matrix * mat_3x3x_view_22()
{
	return &_mat_3x3x_view_22;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_4tp1_2t()
 * @return \f$M\f$, allocated \f$(4 n_t + 1, 2 n_t)\f$-matrix
 **/
inline gsl_matrix * mat_4tp1_2t()
{
	return _mat_4tp1_2t;
}
/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_4t2t_view_sum()
 * @return View on \f$M\f$
 **/
inline gsl_matrix * mat_4t2t_view_sum()
{
	return &_mat_4t2t_view_sum;
}
/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_4t2t()
 * @return \f$M\f$, allocated \f$(4 n_t, 2 n_t)\f$-matrix
 **/
inline gsl_matrix * mat_4t2t()
{
	return &_mat_4t2t;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2tp1_2t()
 * @return matrix view on \f$M\f$, starting at \f$(2 n_t, 0)\f$, ending at \f$(4 n_t, n_t - 1)\f$
 **/
inline gsl_matrix * mat_2tp1_2t()
{
	return &_mat_2tp1_2t;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2tp1_2t_view_00()
 * @return matrix view on \f$M\f$, starting at \f$(0, 0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2tp1_2t_view_00()
{
	return &_mat_2tp1_2t_view_00;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2tp1_2t_view_00_bis()
 * @return matrix view on \f$M\f$, starting at \f$(0, 0)\f$, ending at \f$(n_t - 1, n_t - 1)\f$
 **/
inline gsl_matrix * mat_2tp1_2t_view_00_bis()
{
	return &_mat_2tp1_2t_view_00_bis;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2tp1_2t_view_02()
 * @return matrix view on \f$M\f$, starting at \f$(0, n_t)\f$, ending at \f$(n_x - 1, n_t + n_x - 1)\f$
 **/
inline gsl_matrix * mat_2tp1_2t_view_02()
{
	return &_mat_2tp1_2t_view_02;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2tp1_2t_view_02_bis()
 * @return matrix view on \f$M\f$, starting at \f$(0, n_t)\f$, ending at \f$(n_t - 1, n_t + n_x - 1)\f$
 **/
inline gsl_matrix * mat_2tp1_2t_view_02_bis()
{
	return &_mat_2tp1_2t_view_02_bis;
}

/**@fn inline gsl_matrix * tkalman :: sum_workspace :: mat_2tp1_2t_view_22()
 * @return matrix view on \f$M\f$, starting at \f$(n_t, n_t)\f$, ending at \f$(n_t + n_x - 1, n_t + n_x - 1)\f$
 **/
inline gsl_matrix * mat_2tp1_2t_view_22()
{
	return &_mat_2tp1_2t_view_22;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: mat_2tp1_2t_view_30()
 * @return matrix view on \f$M\f$ (vect. view):
 * - starting at \f$(2 n_t, 0)\f$, ending at \f$(2 n_t, n_x - 1)\f$
 **/
inline gsl_vector * mat_2tp1_2t_view_30()
{
	return &_mat_2tp1_2t_view_30;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: mat_2tp1_2t_view_30_bis()
 * @return matrix view on \f$M\f$ (vect. view):
 * - starting at \f$(2 n_t, 0)\f$, ending at \f$(2 n_t, n_t - 1)\f$
 **/
inline gsl_vector * mat_2tp1_2t_view_30_bis()
{
	return &_mat_2tp1_2t_view_30_bis;
}


/**@fn inline gsl_vector * tkalman :: sum_workspace :: mat_2tp1_2t_view_31()
 * @return matrix view on \f$M\f$ (vect. view):
 *  - starting at \f$(2 n_t, n_x)\f$, ending at \f$(2 n_t, n_t - 1)\f$
 **/
inline gsl_vector * mat_2tp1_2t_view_31()
{
	return &_mat_2tp1_2t_view_31;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: mat_2tp1_2t_view_32()
 * @return matrix view on \f$M\f$ (vect. view):
 * - starting at \f$(2 n_t, n_t)\f$, ending at \f$(2 n_t, n_t + n_x - 1)\f$
 **/
inline gsl_vector * mat_2tp1_2t_view_32()
{
	return &_mat_2tp1_2t_view_32;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: mat_2tp1_2t_view_33()
 * @return matrix view on \f$M\f$ (vect. view):
 * - starting at \f$(2 n_t, n_t + n_x)\f$, ending at \f$(2 n_t, 2 n_t -1 )\f$
 **/
inline gsl_vector * mat_2tp1_2t_view_33()
{
	return &_mat_2tp1_2t_view_33;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: vect_2xpt()
 * @return allocated \$(2 n_x + n_t)\f$-vector
 **/
inline gsl_vector * vect_2xpt()
{
	return _vect_2xpt;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: vect_2t()
 * @return allocated \$(2 n_t)\f$-vector
 **/
inline gsl_vector * vect_2t()
{
	return _vect_2t;
}

/**@fn inline gsl_vector * tkalman :: sum_workspace :: vect_3x()
 * @return allocated \$(3 n_x)\f$-vector
 **/
inline gsl_vector * vect_3x()
{
	return &_vect_3x;
}


protected:
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
gsl_matrix	*_mat_2xpt_2xpt,
			_mat_2xpt_2xpt_view_00,
			_mat_2xpt_2xpt_view_10,
			_mat_2xpt_2xpt_view_11,
			_mat_2xpt_2xpt_view_12,
			_mat_2xpt_2xpt_view_21,
			_mat_2xpt_2xpt_view_22,
			_mat_3x3x, // View on _mat_2xpt_2xpt
			_mat_3x3x_view_00,
			_mat_3x3x_view_10,
			_mat_3x3x_view_11,
			_mat_3x3x_view_12,
			_mat_3x3x_view_21,
			_mat_3x3x_view_22,
			*_mat_4tp1_2t,
			_mat_4t2t_view_sum,
			_mat_4t2t, // Vue de (0,0) à (4 n_t - 1, 2 n_t - 1)
			_mat_4tp1_2t_view_00, // Vue de (0,0) à (n_t - 1, n_t - 1)
			_mat_4tp1_2t_view_01,	// Vue de (0, n_t) à (n_t - 1, 2 n_t - 1)
			_mat_4tp1_2t_view_11, // Vue de (n_t, n_t) à (2 n_t - 1, 2 n_t - 1)
			_mat_2tp1_2t,			// Vue de (2 n_t ,0) à (4 n_t, 2 n_t - 1)
			_mat_2tp1_2t_view_00, // Vue de (2 n_t ,0) à (2 n_t + n_x - 1, n_x - 1)
			_mat_2tp1_2t_view_00_bis, // Vue de (2 n_t ,0) à (3 n_t - 1, n_t - 1)
			_mat_2tp1_2t_view_02,
			_mat_2tp1_2t_view_02_bis,
			_mat_2tp1_2t_view_22;
			
gsl_vector 	_mat_2tp1_2t_view_30,
			_mat_2tp1_2t_view_30_bis,
			_mat_2tp1_2t_view_31,
			_mat_2tp1_2t_view_32,
			_mat_2tp1_2t_view_33,
			*_vect_2xpt,
			*_vect_2t,
			_vect_3x; // View on vect_2xpt
};


	
	
	
};


#endif
