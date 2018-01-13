#ifndef _GSL_PSEUDO_INVERSE_HPP_
#define _GSL_PSEUDO_INVERSE_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;

class gsl_pseudo_inverse_workspace
{

public:
	/**@fn gsl_pseudo_inverse_workspace :: gsl_pseudo_inverse_workspace( unsigned int size );
	 * @param size: taille de la matrice à inverser
	 * @brief
	 * Constructeur
	 * 
	 **/
	gsl_pseudo_inverse_workspace( unsigned int size ) throw ( exception & );

	/**@fn gsl_pseudo_inverse_workspace :: ~gsl_pseudo_inverse_workspace();
	 * @brief
	 * Destructeur
	 * 
	 **/
	~gsl_pseudo_inverse_workspace();
	
	inline unsigned int size() const
	{
		return _size;
	}
	
	inline gsl_matrix * mat_1()
	{
		return _mat_1;
	}

	inline gsl_matrix * u()
	{
		return _mat_2;
	}

	inline gsl_matrix * v()
	{
		return _mat_3;
	}
	
	inline gsl_matrix * inv_d()
	{
		return _mat_4;
	}

	inline gsl_vector * vect_1()
	{
		return _vect_1;
	}

	inline gsl_vector * sv()
	{
		return _vect_2;
	}

protected:
	unsigned int _size;
	gsl_matrix 	* _mat_1,
				* _mat_2,
				* _mat_3,
				* _mat_4;
	gsl_vector  * _vect_1,
				* _vect_2;
	
	
	
	void initialize();
	void free();
	void alloc();
	
	
};







int gsl_pseudo_inverse( gsl_matrix * pseudo_inverse,
						const gsl_matrix * matrix,
						gsl_pseudo_inverse_workspace * w = NULL );





#endif
