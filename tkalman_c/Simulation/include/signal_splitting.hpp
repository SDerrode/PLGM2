#ifndef _SPLIT_SIGNALS_HPP_
#define _SPLIT_SIGNALS_HPP_
#include <gsl/gsl_matrix.h>
/**@class
 * Split d'un signal t -> x, y
 * 
 **/
class signal_splitting 
{
public:
	/**@fn
	 * @param[in] t : \f$ t_n = [ x_n; y_{n-1} ]\f$
	 * @param nb_observations : nombre d'observations
	 * @param size_x : dim de x
	 **/
	signal_splitting ( 	const gsl_vector * const * t,
						unsigned int nb_observations,
						unsigned int size_x );
	/**@fn
	 * @param[in] t : \f$ t_n = [ x_n; y_{n-1} ]\f$
	 * @param nb_observations : nombre d'observations
	 * @param size_x : dim de x
	 **/
	int setup ( 	const gsl_vector * const * t,
					unsigned int nb_observations,
					unsigned int size_x );
					
	/**@fn
	 * @brief
	 * Destructeur
	 * 
	 **/
	~signal_splitting();
	/**@fn
	 * @return
	 * Dim. de t
	 * 
	 * 
	 **/
	inline unsigned int size_t() const
	{
		return _size_t;
	}
	/**@fn
	 * @return
	 * Dim. de x
	 * 
	 * 
	 **/
	inline unsigned int size_x() const
	{
		return _size_x;
	}
	/**@fn
	 * @return
	 * Dim. de y
	 * 
	 * 
	 **/
	inline unsigned int size_y() const
	{
		return _size_y;
	}
	/**@fn
	 * @return
	 * Nombre d'observations
	 * 
	 * 
	 **/
	inline unsigned int nb_samples() const
	{
		return _nb_samples;
	}
	/**@fn
	 * @return
	 * x
	 **/
	inline const gsl_vector * const * x() const
	{
		return _x;
	}
	/**@fn
	 * @return
	 * y
	 **/
	inline const gsl_vector * const * y() const
	{
		return _y;
	}


protected:
	/**@fn
	 * @brief
	 * Initialisation
	 * 
	 **/
	void initialize();
	
	/**@fn
	 * @brief
	 * Lib. mémoire
	 * 
	 **/
	void free();


	gsl_vector * _x_data,
			   ** _x,
			   * _y_data,
			   ** _y;
	unsigned int 	_size_x,
					_size_y,
					_size_t;
					
	unsigned int _nb_samples;
};


#endif
