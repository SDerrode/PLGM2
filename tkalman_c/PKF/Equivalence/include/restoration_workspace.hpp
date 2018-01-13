#ifndef _RESTORATION_WORKSPACE_HPP_
#define _RESTORATION_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h> 
namespace equivalence
{

class restoration_workspace : public tkalman :: workspace
{
public:

/**@fn tkalman :: workspace :: workspace(	unsigned int size_x,
											unsigned int size_y);

 * @param[in] size_x : size of x
 * @param[in] size_y : size of y
 * @brief
 * Constructor
 **/
restoration_workspace( 	unsigned int size_x, 
						unsigned int size_y );
						
						
/**@fn tkalman :: ~workspace();
 * @brief
 * Destructor
 **/
virtual ~restoration_workspace();
	
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
 * \f$\mat[M]{x,x}{2}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_2()
{
	return _mat_xx_2;
}

/**@fn
 * @return
 * \f$\mat[M]{x,x}{3}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_3()
{
	return _mat_xx_3;
}

/**@fn
 * @return
 * \f$\mat[M]{x,x}{4}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_4()
{
	return _mat_xx_4;
}

/**@fn
 * @return
 * \f$\mat[M]{x,x}{5}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_5()
{
	return _mat_xx_5;
}

/**@fn
 * @return
 * \f$\mat[M]{x,x}{6}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_6()
{
	return _mat_xx_6;
}

/**@fn
 * @return
 * \f$\mat[M]{x,x}{7}\f$, \f$(n_x by n_x)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xx_7()
{
	return _mat_xx_7;
}

/**@fn
 * @return
 * \f$\mat[M]{y,y}{1}\f$, \f$(n_y by n_y)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_yy_1()
{
	return &_mat_yy_1;
}

/**@fn
 * @return
 * \f$\mat[M]{y,y}{1}\f$, \f$(n_y by n_y)\f$-matrix
 * 
 **/
inline gsl_matrix * mat_xy_1()
{
	return _mat_xy_1;
}

/**@fn
 * @return
 * view on \f$\mat[M]{x,x}{1}\f$, from \f$(0,n_x)\f$ to \f$(n_x - 1, n_t - 1)\f$
 * 
 **/
inline gsl_matrix * mat_xx_1_xy()
{
	return &_mat_xx_1_xy;
}

/**@fn
 * @return
 * view on \f$\mat[M]{x,x}{2}\f$, from \f$(0,n_x)\f$ to \f$(n_x - 1, n_t - 1)\f$
 * 
 **/
inline gsl_matrix * mat_xx_2_xy()
{
	return &_mat_xx_2_xy;
}

/**@fn
 * @return
 * \f$n_x\f$-vector
 * 
 **/
inline gsl_vector * vect_y_1()
{
	return _vect_y_1;
}

/**@fn
 * @return
 * \f$n_x\f$-permutation
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
	
gsl_matrix * _mat_xx_1,
		   _mat_xx_1_xy,
		   * _mat_xx_2,
		   _mat_xx_2_xy,
		   * _mat_xx_3,
		   * _mat_xx_4,
		   * _mat_xx_5,
		   * _mat_xx_6,
		   * _mat_xx_7,
		   _mat_yy_1,
		   * _mat_xy_1;
		   
gsl_vector * _vect_y_1;
gsl_permutation * _perm_x;
	
	
	
};
	
	
};

#endif
