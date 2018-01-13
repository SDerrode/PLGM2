#ifndef _TKALMAN_PREDICTION_WORKSPACE_HPP_
#define _TKALMAN_PREDICTION_WORKSPACE_HPP_
#include "tkalman_workspace.hpp"

namespace tkalman
{
/**@class tkalman :: prediction_workspace 
 * @brief
 * Workspace for prediction computing.
 * 
**/
class prediction_workspace : public workspace
{
public:
/**@fn tkalman :: prediction_workspace :: prediction_workspace(	unsigned int size_x, unsigned int size_y );
 * @param size_x : size of x
 * @param size_y : size of y
 * @brief
 * Constructor
 **/
prediction_workspace(	unsigned int size_x, 
						unsigned int size_y ) throw( exception & );

/**@fn tkalman :: prediction_workspace :: ~prediction_workspace();
 * @brief
 * Destructor
 **/
~prediction_workspace();


//Accesseurs
/**@fn inline gsl_matrix * tkalman :: prediction_workspace :: mat_xpt_x()
 * @return
	 \f$ M\f$,allocated \f$(n_x + n_t, n_x)\f$-matrix
 **/
inline gsl_matrix * mat_xpt_x()
{
	return _mat_xpt_x;
}

/**@fn inline gsl_matrix * tkalman :: prediction_workspace :: mat_xpt_x_view_00()
 * @return
	 * view on the matrix \f$ M\f$, starting at \f$(0,0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_xpt_x_view_00()
{
	return &_mat_xpt_x_view_00;
}

/**@fn inline gsl_matrix * tkalman :: prediction_workspace :: mat_xpt_x_view_10()
 * @return
	 * view on the matrix \f$ M\f$, starting at \f$(n_x,0)\f$, ending at \f$(n_x + n_t - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_xpt_x_view_10()
{
	return &_mat_xpt_x_view_10;
}

/**@fn inline gsl_matrix * tkalman :: prediction_workspace :: mat_2xx()
 * @return
	 \f$ M\f$,allocated \f$(2n_x, n_x)\f$-matrix
 **/
inline gsl_matrix * mat_2xx()
{
	return &_mat_2xx;
}

/**@fn inline gsl_matrix * tkalman :: prediction_workspace :: mat_2xx_view_00()
 * @return
	 * view on the matrix \f$ M\f$, starting at \f$(0,0)\f$, ending at \f$(n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xx_view_00()
{
	return &_mat_2xx_view_00;
}

/**@fn inline gsl_matrix * tkalman :: prediction_workspace :: mat_2xx_10()
 * @return
	 * view on the matrix \f$ M\f$, starting at \f$(n_x,0)\f$, ending at \f$(2 n_x - 1, n_x - 1)\f$
 **/
inline gsl_matrix * mat_2xx_view_10()
{
	return &_mat_2xx_view_10;
}

/**@fn inline gsl_vector * tkalman :: prediction_workspace :: vect_x()
 * @return
	allocated \f$(n_x)\f$-vector
 **/
inline gsl_vector * vect_x()
{
	return _vect_x;
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


gsl_matrix	*_mat_xpt_x,
			_mat_xpt_x_view_00,
			_mat_xpt_x_view_10;
gsl_matrix 	_mat_2xx,
			_mat_2xx_view_00,
			_mat_2xx_view_10;
gsl_vector * _vect_x;

	
};
	
	
};




#endif
