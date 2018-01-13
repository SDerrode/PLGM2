#ifndef _TKALMAN_F_ESTIMATION_t1_block_WORKSPACE_HPP_
#define _TKALMAN_F_ESTIMATION_t1_block_WORKSPACE_HPP_
#include "../../Filter/lib_PKF_filter.hpp"
#include <gsl/gsl_permutation.h>
namespace tkalman
{
namespace f_estimation
{
namespace t1_block
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
																					unsigned int size_g );
 * @param[in] size_i : \f$n_i\f$
 * @param[in] size_t : \f$n_t\f$
 * @param[in] size_g: \f$ n_i^G\f$
 * @brief
 * Constructor
 **/
workspace( 	unsigned int size_i,
			unsigned int size_t,
			unsigned int size_g );

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
inline unsigned int size_g() const
{
	return _size_g;
}

/**@fn inline gsl_matrix * mat_tpi_gpi_1()
 * @return
 * \f$(n_t + n_i by n_g + n_i)-matrix\f$
 **/
inline gsl_matrix * mat_tpi_gpi_1()
{
	return _mat_tpi_gpi_1;
}

inline gsl_matrix * mat_tpi_gpi_1_view_00()
{
	return &_mat_tpi_gpi_1_view_00;
}

inline gsl_matrix * mat_tpi_tpi()
{
	return _mat_tpi_tpi;
}

inline gsl_matrix * mat_tpi_tpi_view_00()
{
	return &_mat_tpi_tpi_view_00;
}

inline gsl_matrix * mat_tpi_tpi_view_01()
{
	return &_mat_tpi_tpi_view_01;
}

inline gsl_matrix * mat_tpi_gpi_2()
{
	return _mat_tpi_gpi_2;
}

inline gsl_matrix * mat_tpi_gpi_2_view_00()
{
	return &_mat_tpi_gpi_2_view_00;
}

inline gsl_matrix * mat_tpi_gpi_2_view_01()
{
	return &_mat_tpi_gpi_2_view_01;
}

inline gsl_vector * vect_gpi()
{
	return _vect_gpi;
}

inline gsl_permutation * perm_g()
{
	return _perm_g;
}

inline gsl_matrix * mat_gi()
{
	return _mat_gi;
}

inline gsl_matrix * mat_gg()
{
	return _mat_gg;
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

unsigned int _size_g;

gsl_matrix  *_mat_tpi_gpi_1,
			_mat_tpi_gpi_1_view_00;
			
gsl_matrix 		*_mat_tpi_tpi,
				_mat_tpi_tpi_view_00,
				_mat_tpi_tpi_view_01;

gsl_matrix  *_mat_tpi_gpi_2,
			_mat_tpi_gpi_2_view_00,
			_mat_tpi_gpi_2_view_01;
			
gsl_vector * _vect_gpi;
gsl_permutation * _perm_g;

gsl_matrix * _mat_gi,
		   * _mat_gg;
};
};
};
};

#endif
