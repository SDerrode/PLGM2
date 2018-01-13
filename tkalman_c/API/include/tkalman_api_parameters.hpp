#ifndef _TKALMAN_API_PARAMETERS_
#define _TKALMAN_API_PARAMETERS_
#include "lib_api.hpp"

namespace tkalman
{
namespace api
{
/**@class parameters
 * @brief
 * Gestion des paramètres du filtre de Kalman couple
 * 
 **/
class parameters
{
public:
/**@fn tkalman :: api :: parameters :: parameters( void );
 * @brief
 * Constructeur
 * 
 **/
parameters( void );

/**@fn virtual int tkalman :: api :: parameters :: setup ( api_parameters & params );
 * 
 **/
virtual int setup ( api_parameters & params );

/**@fn tkalman :: api :: parameters :: ~parameters( void );
 * @brief
 * Destructeru
 **/
virtual ~parameters();

/**@fn gsl_vector * tkalman :: api :: parameters :: t_0() const
 * @return
 * \f$\hat{t}_0\f$
 **/
inline const gsl_vector * t_0() const
{
	return _t_0;
}

/**@fn inline gsl_matrix * tkalman :: api :: parameters :: sqrt_q_0()
 * @return \f$ [Q_0]^{\frac{1}{2}}\f$
 **/
inline const gsl_matrix * q_0() const
{
	return _q_0;
}

/**@fn inline gsl_matrix * tkalman :: api :: parameters :: f()
 * @return \f$ F \f$
 **/
inline const gsl_matrix * f() const
{
	return _f;
}

/**@fn inline gsl_matrix * tkalman :: api :: parameters :: sqrt_q_0()
 * @return \f$ [Q]^{\frac{1}{2}}\f$
 **/
inline const gsl_matrix * q() const
{
	return _q;
}

/**@fn inline unsigned int tkalman :: filter :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: filter :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: filter :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}
protected:
/**@fn
 * @brief
 * Lib. mémoire
 * 
 **/
void free();

/**@fn
 * @brief
 * Initialisation de l'objet
 **/
void initialize();

/**@fn
 * @brief
 * Alloc
 * 
 **/
void alloc();

		
unsigned int 	_size_x,
				_size_y,
				_size_t;

gsl_vector 	*_t_0;
gsl_matrix 	*_q_0,
			*_f,
			*_q;
			
};
};
};



#endif
