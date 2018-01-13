#ifndef _TKALMAN_PARAMETERS_HPP_
#define _TKALMAN_PARAMETERS_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
/**@class tkalman::parameters
 * @brief
 * PK parameters
 **/
class parameters
{
public:
/**@fn tkalman :: parameters :: parameters( void );
 * @brief Default constructor
 **/
parameters( void );

/**@fn tkalman :: parameters ::parameters ( const parameters & p );
 * @param[in] p : paramètres à recopier
 * @brief
 * Recopie les paramètres
 **/
parameters ( const parameters & p ) throw ( exception &);

/**@fn tkalman :: parameters :: parameters(	const gsl_vector * t_0,
											const gsl_matrix * sqrt_q_0,
											const gsl_matrix * f,
											const gsl_matrix * sqrt_q,
											unsigned int size_x ) throw ( exception &);
 * @param[in] t_0, \f$ \hat{t}_0\f$, expectation of initial state
 * @param[in] q_0, \f$ Q_0\f$, initial state covariance matrix
 * @param[in] f : \f$ F\f$, transition matrix
 * @param[in] q : \f$ Q\f$ , covariance matrix
 * @param[in] size_x : size of hidden states
 **/
parameters(	const gsl_vector * t_0,
			const gsl_matrix * q_0,
			const gsl_matrix * f,
			const gsl_matrix * q,
			unsigned int size_x ) throw ( exception &);


/**@fn int tkalman :: parameters :: parameters(	const gsl_vector * t_0,
												const gsl_matrix * sqrt_q_0,
												const gsl_matrix * f,
												const gsl_matrix * sqrt_q,
												unsigned int size_x,
												const unsigned int * noise_ids,
												const unsigned int * f_mask );
 * @param[in] t_0, \f$ \hat{t}_0\f$, expectation of initial state
 * @param[in] q_0, \f$ Q_0\f$, initial state covariance matrix
 * @param[in] f : \f$ F\f$, transition matrix
 * @param[in] q : \f$ Q\f$ , covariance matrix
 * @param[in] size_x : size of hidden states
 * 
 **/
virtual int setup(	const gsl_vector * t_0,
					const gsl_matrix * q_0,
					const gsl_matrix * f,
					const gsl_matrix * q,
					unsigned int size_x );

/**@fn tkalman :: parameters :: parameters ( const parameters & p );
 * @param[in] p : paramètres à recopier
 * @brief
 * Recopie les paramètres
 **/
virtual int setup ( const parameters & p );


/**@fn tkalman :: parameters :: setup( 	unsigned int size_x,
					unsigned int size_t );
 * @brief
 **/
virtual int setup( 	unsigned int size_x,
					unsigned int size_t );

/**@fn tkalman :: parameters :: parameters ( const parameters & p );
 * @param[in] p : paramètres à recopier
 * @brief
 * Recopie les paramètres
 **/
parameters & operator=( const parameters & p ) throw ( exception &);

/**@fn void tkalman :: parameters :: reset();
 * @brief Reset
 **/
virtual void reset();

/**@fn tkalman :: parameters ::~parameters();
 * @brief
 * Destructor
 **/
~parameters();

/**@fn void EM_parameters :: update_q_0_and_q();
 * @brief
 * Update q_0 and Q
 **/
void update_q_0_and_q();

//Transformation
int transformation( const gsl_matrix * m );



//Accesseur no-const
/**@fn inline gsl_vector * EM_parameters ::  t_0()
 * @return
 * \f$ \hat{t}_0\f$, expectation of initial state
 **/
inline gsl_vector * t_0()
{
	return _t_0;
}
/**@fn inline gsl_matrix * EM_parameters ::  sqrt_q_0()
 * @return
 * \f$ [Q_0]^{\frac{1}{2}}\f$, square root of initial state covariance
 **/
inline gsl_matrix * sqrt_q_0()
{
	return _sqrt_q_0;
}
/**@fn inline gsl_matrix * EM_parameters ::  sqrt_q()
 * @return
 * \f$ [Q]^{\frac{1}{2}}\f$, square root of covariance
 **/
inline gsl_matrix * sqrt_q()
{
	return _sqrt_q;
}
/**@fn inline gsl_matrix * EM_parameters ::  f()
 * @return
 * \f$ F \f$, square root of covariance
 **/
inline gsl_matrix * f()
{
	return _f;
}
//Accesseurs const
/**@fn inline unsigned int tkalman :: parameters :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: parameters :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: parameters :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn inline const gsl_vector * tkalman :: parameters :: get_t_0() const
 * @return
 * \f$ \hat{t}_0\f$, initial state expectation!
 **/
inline const gsl_vector * get_t_0() const
{
	return _t_0;
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: sqrt_q_0() const
 * @return
 * \f$ [Q_0]^{\frac{1}{2}}\f$, square root of initial state covariance matrix
 **/
inline const gsl_matrix * get_sqrt_q_0() const
{
	return _sqrt_q_0;
	
}

/**@fn inline const gsl_vector * tkalman :: parameters :: get_f() const
 * @return
 * \f$ F\f$, initial state expectation!
 **/
inline const gsl_matrix * get_f() const
{
	return _f;
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: sqrt_q() const
 * @return
 * \f$ [Q]^{\frac{1}{2}}\f$, square root of initial state covariance matrix
 **/
inline const gsl_matrix * get_sqrt_q() const
{
	return _sqrt_q;
	
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: sqrt_q_view_xx() const
 * @return
 * \f$ [Q]^{\frac{1}{2}}\f$, square root of initial state covariance matrix
 **/
inline const gsl_matrix * get_sqrt_q_xx() const
{
	return &_sqrt_q_xx;
	
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: sqrt_q_view_xy() const
 * @return
 * \f$ [Q]^{\frac{1}{2}}\f$, square root of initial state covariance matrix
 **/
inline const gsl_matrix * get_sqrt_q_view_xy() const
{
	return &_sqrt_q_xy;
	
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: sqrt_q_view_yy() const
 * @return
 * \f$ [Q]^{\frac{1}{2}}\f$, square root of initial state covariance matrix
 **/
inline const gsl_matrix * get_sqrt_q_view_yy() const
{
	return &_sqrt_q_yy;
	
}

/**@fn inline const gsl_vector * tkalman :: parameters :: get_f_xt() const
 * @return
 * \f$ F^{x,t}\f$, initial state expectation!
 **/
inline const gsl_matrix * get_f_xt() const
{
	return &_f_xt;
}

/**@fn inline const gsl_vector * tkalman :: parameters :: get_f_yt() const
 * @return
 * \f$ F^{y,t}\f$, initial state expectation!
 **/
inline const gsl_matrix * get_f_yt() const
{
	return &_f_yt;
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: gsl_matrix * q() const
 * @return \f$ Q \f$, noise covariance matrix
 **/
inline const gsl_matrix * q() const
{
	return _q;
}

/**@fn inline const gsl_matrix * tkalman :: parameters :: gsl_matrix * q_0() const
 * @return \f$ Q_0 \f$, initial noise covariance matrix
 **/
inline const gsl_matrix * q_0() const
{
	return _q_0;
}
protected:
/**@fn void tkalman :: parameters :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();
/**@fn void tkalman :: parameters :: free();
 * @brief
 * This function frees memory.
 */
void free();
/**@fn void tkalman :: parameters :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

//Paramètres
unsigned int 	_size_x,
				_size_y,
				_size_t;

gsl_vector * _t_0;
gsl_matrix * _sqrt_q_0;

gsl_matrix 	* _f,
			_f_xt,
			_f_yt;


gsl_matrix 	* _sqrt_q,
			_sqrt_q_xx,
			_sqrt_q_xy,
			_sqrt_q_yy;

gsl_matrix * _q_0,
		   * _q;
};
};

#endif
