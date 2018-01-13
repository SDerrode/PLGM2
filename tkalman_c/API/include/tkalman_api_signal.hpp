#ifndef _TKALMAN_API_SIGNAL_HPP_
#define _TKALMAN_API_SIGNAL_HPP_
#include "lib_api.hpp"
namespace tkalman
{
namespace api
{
/**@class
 * @brief
 * 
 * 
 **/
class signal
{
public:
/**@fn
 * @brief
 * Constructeur
 * 
 **/
signal ( void );

		
/**@fn
 * @brief
 * Setup
 * 
 **/
virtual int setup( api_parameters & params, unsigned int i = 0 );
		
		
/**@fn
 * @brief
 * Destructeur
 * 
 **/
~signal ( void );

/**@fn
 * @return
 * Observations
 * 
 **/
inline gsl_vector ** observations()
{
	return pp_y;
}

/**@fn
 * @return
 * Etats cachés
 * 
 **/
inline gsl_vector ** hidden_states()
{
	return pp_x;
}

/**@fn
 * @return
 * nombre d'échantillons
 * 
 **/
inline unsigned int nb_samples_y() const
{
	return _nb_samples;
}

/**@fn
 * @return
 * nombre d'échantillons
 * 
 **/
inline unsigned int nb_samples_x() const
{
	return _nb_samples_x;
}

protected:
/**@fn
 * @brief
 * Ini.
 * 
 **/
void initialize();

/**@fn
 * @brief
 * Lib. mémoire
 * 
 **/
void free();
// x : signal original
// y : observations
gsl_matrix * x, *y;
//Nombre d'échantillons
unsigned int _nb_samples,
			 _nb_samples_x;

//Pointeurs
gsl_vector * p_x,
		   * p_y;

gsl_vector ** pp_x,
		   ** pp_y;
	
};
};
};

#endif
