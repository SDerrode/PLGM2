#ifndef TKALMAN_MOMENT_HPP_
#define TKALMAN_MOMENT_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
#ifndef tkalman_expectation_unref
	/**@def tkalman_esperance_unref(moment, nb)
	 * @param moment : moment
	 * @param nb : nombre
	 * @brief
	 Cette macro désalloue un moment statistique vectoriel.
	 *
	**/
	#define tkalman_expectation_unref(moment, nb) if (moment) \
												{\
													for( unsigned int i = 0; i < (nb) ; ++ i) \
													{\
														if ( (moment)[i] )\
														{\
															gsl_vector_free((moment)[i]);\
														}\
													}\
													delete [] (moment);\
												}
#endif

#ifndef tkalman_covariance_unref

	/**@def tkalman_covariance_unref(moment, nb)
	 * @param moment : moment
	 * @param nb : nombre
	 * @brief
	 Cette macro désalloue un moment statistique matriciel.
	 *
	 */
	#define tkalman_covariance_unref(moment, nb) if (moment) \
												 {\
													for( unsigned int i = 0; i < (nb) ; ++ i) \
													{\
														if ( (moment)[i] )\
														{\
															gsl_matrix_free((moment)[i]);\
														}\
													}\
													delete [] (moment);\
												 }
#endif
	
#ifndef tkalman_expectation_ref

	#define tkalman_expectation_ref(moment, nb, size_x, size_t) if (! (moment) ) \
	{\
		(moment) = new gsl_vector*[nb];\
		if (moment)\
		{\
			(moment)[0] = gsl_vector_calloc(size_t);\
			for (unsigned j = 1 ; j < (nb); ++ j)\
			{\
				(moment)[j] = gsl_vector_calloc(size_x);\
			}\
		}\
	}
#endif

#ifndef tkalman_covariance_ref

	#define tkalman_covariance_ref(moment, nb, size_1, size_2, size_1_0, size_2_0) if (! (moment) ) \
	{\
		(moment) = new gsl_matrix*[nb];\
		if (moment)\
		{\
			(moment)[0] = gsl_matrix_calloc(size_1_0, size_2_0);\
			for (unsigned j = 1 ; j < (nb) ; ++ j)\
			{\
				(moment)[j] = gsl_matrix_calloc(size_1, size_2);\
			}\
		}\
	}
#endif

namespace tkalman
{
/**@class tkalman :: moments
 * @brief
 * PK moments
 **/
class moments
{
public:
/**@fn tkalman :: moments :: moments ( void );
 * @brief
 * - Default constructor
 * - Sets object attributes to 0.
 * 
 */
moments ( void );

/**@fn tkalman :: moments (	unsigned int size_x,
								unsigned int size_y,
								unsigned int nb_moments );

 * @param[in] size_x : size of x
 * @param[in] size_y : size of y
 * @param[in] nb_moments : nomber of moments
 * @brief
 * Setup
 **/
moments (	unsigned int size_x,
			unsigned int size_y,
			unsigned int nb_moments = 0 ) throw( exception&);

/**@fn int tkalman :: moments :: setup(	unsigned int size_x,
										unsigned int size_y,
										unsigned int nb_moments )

 * @param[in] size_x : size of x
 * @param[in] size_y : size of y
 * @param[in] nb_moments : nomber of moments
 * @brief
 * Setup
 **/
int setup(	unsigned int size_x,
			unsigned int size_y,
			unsigned int nb_moments = 0 );

//Transformation
int transformation( const gsl_matrix * m,
					const gsl_vector * const * y );


/**@fn void tkalman :: moments :: reset()
 * @brief
 * Reset
 * 
 **/
void reset();

/**@fn void tkalman :: moments :: set_nb_moments( unsigned int nb );
 * @param nb : nomber of moments
 * @brief
 * sets the number of moments.
 **/
void set_nb_moments( unsigned int nb );


/**@fn tkalman :: moments :: ~moments();
 * @brief
 * Destructor
 **/
~moments();

//Accesseurs <-> const
/**@fn inline unsigned int tkalman :: moments :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: moments :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: moments :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn inline unsigned int tkalman :: moments :: nb_moments() const
 * @return
 * Size of t
 **/
inline unsigned int nb_moments() const
{
	return _nb_moments;
}

/**@fn const gsl_vector * tkalman :: moments :: get_innovation( unsigned int n ) const;
 * @param[in] n : n
 * @return
 * \f$ \tilde{y}_{n|n-1}\f$, Innovation
 **/
const gsl_vector * get_innovation( unsigned int n ) const;

/**@fn int tkalman :: moments :: get_s( 	gsl_matrix * s,
											unsigned int n ) const;
 * @param[out] s : \f$ S_{n|n-1}\f$, covariance of the innovation
 * @param[in] n : n
 **/
int get_s( 	gsl_matrix * s,
			unsigned int n ) const;

/**@fn const gsl_vector * tkalman :: moments :: get_x_p( unsigned int n ) const;
 * @param[in] n : n
 * @return
 * \f$ \hat{x}_{n|n-1}\f$, prediction expectation
 **/
const gsl_vector * get_x_p( unsigned int n ) const;


/**@fn int tkalman :: moments :: get_p_p(	gsl_matrix * p_p, 
											unsigned int n ) const;
 * @param[out] p_p : \f$ P_{n|n-1}\f$, prediction covariance
 * @param[in] n : n
 **/
int get_p_p(	gsl_matrix * p_p, 
				unsigned int n ) const;

/**@fn const gsl_vector * tkalman :: moments :: get_x_f( unsigned int n ) const;
 * @param[in] n : n
 * @return
 * \f$ \hat{x}_{n|n}\f$, filtering expectation
 **/
const gsl_vector * get_x_f( unsigned int n ) const;


/**@fn int tkalman :: moments :: get_p_p(	gsl_matrix * p_f, 
											unsigned int n ) const;
 * @param[out] p_f : \f$ P_{n|n}\f$, filtering covariance
 * @param[in] n : n
 **/
int get_p_f(	gsl_matrix * p_f, 
				unsigned int n ) const;

/**@fn const gsl_vector * tkalman :: moments :: get_x_s( unsigned int n ) const;
 * @param[in] n : n
 * @return
 * \f$ \hat{x}_{n|N}\f$, smoothing expectation
 **/
const gsl_vector * get_x_s( unsigned int n ) const;


/**@fn int tkalman :: moments :: get_p_s(	gsl_matrix * p_s, 
											unsigned int n ) const;
 * @param[out] p_f : \f$ P_{n|N}\f$, smoothing covariance
 * @param[in] n : n
 **/
int get_p_s(	gsl_matrix * p_s, 
				unsigned int n ) const;


/**@fn inline const gsl_vector * const * moments :: all_x_s() const
 * @param[in] n : n
 * @return
 * \f$ \hat{x}_{n|N}\f$, smoothing expectation
 **/
inline const gsl_vector * const * all_x_s() const
{
	return _x_s;
}

/**@fn inline const gsl_vector * const * moments :: all_x_p() const
 * @param[in] n : n
 * @return
 * \f$ \hat{x}_{n|n-1}\f$, smoothing expectation
 **/
inline const gsl_vector * const * all_x_p() const
{
	return _x_p;
}

/**@fn inline const gsl_vector * const * moments :: all_x_f() const
 * @param[in] n : n
 * @return
 * \f$ \hat{x}_{n|n}\f$, smoothing expectation
 **/
inline const gsl_vector * const * all_x_f() const
{
	return _x_f;
}


/**@fn inline const gsl_matrix * const * moments :: all_sqrt_p_s() const
 * @param[in] n : n
 * @return
 * \f$ [P_{n|N}]^{\frac{1}{2}}\f$, smoothing expectation
 **/
inline const gsl_matrix * const * all_sqrt_p_s() const
{
	return _sqrt_p_s;
}

/**@fn inline const gsl_matrix * const * moments :: all_sqrt_p_p() const
 * @param[in] n : n
 * @return
 * \f$ [P_{n|n-1}]^{\frac{1}{2}}\f$, smoothing expectation
 **/
inline const gsl_matrix * const * all_sqrt_p_p() const
{
	return _sqrt_p_p;
}

/**@fn inline const gsl_matrix * const * moments :: all_sqrt_p_f() const
 * @param[in] n : n
 * @return
 * \f$ [P_{n|n}]^{\frac{1}{2}}\f$, smoothing expectation
 **/
inline const gsl_matrix * const * all_sqrt_p_f() const
{
	return _sqrt_p_f;
}

/**@fn inline const gsl_matrix * const * moments :: all_c_s() const
 * @param[in] n : n
 * @return
 **/
inline const gsl_matrix * const * all_c_s() const
{
	return _c_s;
}



//Accesseurs <-> no-const (no protected !!!!)
/**@fn inline gsl_vector * tkalman :: moments ::y_p ( unsigned int i ) 
 * @param[in] i : i
 **/
inline gsl_vector * y_p ( unsigned int i ) 
{
	return _y_p[i];
}
/**@fn inline gsl_matrix ** tkalman :: moments ::sqrt_s_p ( unsigned int i )  
 * @param[in] i : i
 **/
inline gsl_matrix * sqrt_s_p ( unsigned int i )  
{
	return _sqrt_s_p[i];
}
/**@fn inline gsl_vector * tkalman :: moments ::x_p ( unsigned int i ) 
 * @param[in] i : i
 **/
inline gsl_vector * x_p ( unsigned int i ) 
{
	return _x_p[i];
}
/**@fn inline gsl_matrix ** tkalman :: moments ::sqrt_p_p ( unsigned int i )   
 * @param[in] i : i
 **/
inline gsl_matrix * sqrt_p_p ( unsigned int i )  
{
	return _sqrt_p_p[i];
}
/**@fn inline gsl_vector * tkalman :: moments ::x_f ( unsigned int i ) 
 * @param[in] i : i
 **/
inline gsl_vector * x_f ( unsigned int i ) 
{
	return _x_f[i];
}
/**@fn inline gsl_matrix ** tkalman :: moments ::sqrt_p_f ( unsigned int i )   
 * @param[in] i : i
 **/
inline gsl_matrix * sqrt_p_f ( unsigned int i )  
{
	return _sqrt_p_f[i];
}
/**@fn inline gsl_vector * tkalman :: moments ::x_s ( unsigned int i ) 
 * @param[in] i : i
 **/
inline gsl_vector * x_s ( unsigned int i ) 
{
	return _x_s[i];
}
/**@fn inline gsl_matrix ** tkalman :: moments ::sqrt_p_s ( unsigned int i ) 
 * @param[in] i : i
 **/
inline gsl_matrix * sqrt_p_s ( unsigned int i )  
{
	return _sqrt_p_s[i];
}
/**@fn inline gsl_matrix ** tkalman :: moments ::c_s ( unsigned int i )  
 * @param[in] i : i
 **/
inline gsl_matrix * c_s ( unsigned int i )  
{
	return _c_s[i];
}


protected:
/**@fn void tkalman :: constants :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();
/**@fn void tkalman :: constants :: free();
 * @brief
 * This function frees memory.
 */
void free();
/**@fn void tkalman :: constants :: alloc();
 * @brief
 * This function allocates attributes.
 */
void alloc();

//Moments
gsl_vector ** _y_p;
gsl_matrix ** _sqrt_s_p;

gsl_vector ** _x_p;
gsl_matrix ** _sqrt_p_p;

gsl_vector ** _x_f;
gsl_matrix ** _sqrt_p_f;
gsl_vector ** _x_s;
gsl_matrix ** _sqrt_p_s;
gsl_matrix ** _c_s;

gsl_vector 	_x_p_0, 
			_x_s_0, 
			_x_f_0;

unsigned int _nb_moments;

//Paramètres
unsigned int	_size_x,
				_size_y,
				_size_t,
				_max_moments;
};


};


#endif
