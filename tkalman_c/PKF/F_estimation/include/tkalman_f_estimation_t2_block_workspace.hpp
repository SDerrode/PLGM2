#ifndef _TKALMAN_F_ESTIMATION_t2_block_WORKSPACE_HPP_
#define _TKALMAN_F_ESTIMATION_t2_block_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
#include <gsl/gsl_permutation.h>
namespace tkalman
{
namespace f_estimation
{
namespace t2_block
{
	
/**@class tkalman :: f_estimation :: t2_block :: workspace
 * @brief
 * Workspace for tensorial constraint
 * 
 **/
class workspace : public tkalman :: workspace
{
public:
/**@fn tkalman :: f_estimation :: t2_block :: workspace :: workspace( 	unsigned int size_i,
																		unsigned int size_t,
																		unsigned int size_lambda );
 * @param[in] size_i : \f$n_i\f$
 * @param[in] size_t : \f$n_t\f$
 * @param[in] size_lambda : \f$ n_i^{\lambda}\f$
 * @brief
 * Constructor
 **/
workspace( 	unsigned int size_i,
			unsigned int size_t,
			unsigned int size_lambda );

/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: workspace ::  size_i() const
 * @return
 * Size of i
 **/
inline unsigned int size_i() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: f_estimation :: t2_block :: workspace ::  size_lambda() const
 * @return
 * Size of \f$\Lambda_i\f$
 **/
inline unsigned int size_lambda() const
{
	return _size_lambda;
}

/**@fn inline gsl_matrix * tkalman :: f_estimation :: t2_block :: workspace :: v_it( unsigned int i )
 * @param[in] i : matrix number
 * @return
 * Allocated \f$(n_i by n_t)\f$ - matrix
 **/
inline gsl_matrix * v_it( unsigned int i )
{
	return _v_it[i];
}
/**@fn inline gsl_matrix * tkalman :: f_estimation :: t2_block :: workspace :: mat_it()
 * @return
 * Allocated \f$(n_i by n_t)\f$ - matrix
 **/
inline gsl_matrix * mat_it()
{
	return _mat_it;
}
/**@fn inline gsl_matrix * tkalman :: f_estimation :: t2_block :: workspace :: mat_ii()
 * @return
 * Allocated \f$(n_i by n_i)\f$ - matrix
 **/
inline gsl_matrix * mat_ii()
{
	return _mat_ii;
}

/**@fn inline gsl_matrix * tkalman :: f_estimation :: t2_block :: workspace :: mat_lambda_lambda()
 * @return
 * Allocated \f$(n_i^{\lambda} by n_i^{\lambda})\f$ - matrix
 **/
inline gsl_matrix * mat_lambda_lambda()
{
	return _mat_lambda_lambda;
}
/**@fn inline gsl_vector *  tkalman :: f_estimation :: t2_block :: workspace :: vect_lambda()
 * @return
 * Allocated \f$n_i^{\lambda}\f$ - vector
 **/
inline gsl_vector * vect_lambda()
{
	return _vect_lambda;
}
/**@fn inline gsl_vector *  tkalman :: f_estimation :: t2_block :: workspace :: lambda()
 * @return
 * Allocated \f$n_i^{\lambda}\f$ - vector
 **/
inline gsl_vector * lambda()
{
	return _lambda;
}

/**@fn inline gsl_permutation * perm_i()
 * @return $n_i$-permutation
 **/
inline const gsl_permutation * perm_i() const
{
	return _perm_i;
}	

inline gsl_matrix * inv_sqrt_qi()
{
	return _mat_ii_2;
}

/**@fn tkalman :: f_estimation :: t2_block :: workspace :: ~workspace();
 * @brief
 * Destructor
 **/
~workspace();

protected:
/**@fn void kalman :: f_estimation :: t2_block :: workspace ::  initialize();
 * @brief
 * Object initialization
 **/
void initialize();

unsigned int _size_lambda;
	
gsl_matrix ** _v_it; // V_i^j
gsl_matrix * _mat_it;
gsl_matrix * _mat_ii;
gsl_matrix * _mat_ii_2;
gsl_matrix * _mat_lambda_lambda; //A_i
gsl_vector * _vect_lambda; // B
gsl_vector * _lambda;
gsl_permutation * _perm_i;


};

};
};
};


#endif
