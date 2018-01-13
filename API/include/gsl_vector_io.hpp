/**@file gsl_vector_io.hpp
 * @brief
 * Ce fichier permet la lecture des vecteurs dans un fichier de paramètres.
 * 
 */
#ifndef _GSL_VECTOR_IO_HPP_
#define _GSL_VECTOR_IO_HPP_
#include "gsl_matrix_io.hpp"
#include <gsl/gsl_matrix.h>
#define API_DEFAULT_VECTOR_ARRAY_FORMAT "{^}^\t^\n^%lf"
/**@struct vector_array
 * @brief
 * Cette structure permet de gerer un tableau de vecteurs.
 **/
struct vector_array
{
	unsigned int n;
	gsl_vector ** vectors;

	/**@fn void vector_array :: setup(int nb_vectors = 0, unsigned int size_x);
	 * 
	 **/
	void setup(unsigned int nb_vectors, unsigned int size_x);

	/**@fn void vector_array :: setup(const gsl_matrix * mat);
	 * 
	 **/
	void setup(const gsl_matrix * mat);
	
	/**@fn void vector_array :: setup(const gsl_vector * const * vect, unsigned int nb); 
	 * 
	 **/
	void setup(const gsl_vector * const * vect, unsigned int nb); 
	
	/**@fn void vector_array :: setup(const vector_array & vect_array);
	 * 
	 **/
	void setup(const vector_array & vect_array); 
	
	
	
	/**@fn vector_array :: vector_array(int nb_vectors = 0, unsigned int size_x);
	 * 
	 */
	vector_array(unsigned int nb_vectors, unsigned int size_x);
	
	/**@fn vector_array :: vector_array(gsl_matrix * mat);
	 * 
	 */
	vector_array(const gsl_matrix * mat);
	
	/**@fn vector_array :: vector_array(const gsl_vector * const * vect,  unsigned int nb); 
	 * 
	 */
	vector_array(const gsl_vector * const * vect, unsigned int nb); 
	
	/**@fn vector_array :: vector_array(const vector_array & vect_array);
	 * 
	 */
	vector_array(const vector_array & vect_array);
	
	/**@fn vector_array & vector_array :: operator=(const vector_array & vect_array);
	 **/
	vector_array & operator=(const vector_array & vect_array);
	
	/**@fn vector_array :: ~vector_array();
	 * 
	 */
	~vector_array();
	
	/**@fn void vector_array :: free();
	 * 
	 *
	 **/
	void free();
	
	/**@fn void vector_array :: initialize();
	 * 
	 */
	void initialize();
	
	/**@fn gsl_vector * vector_array :: operator[](unsigned int i)
	 * 
	 **/
	gsl_vector * operator[](unsigned int i);
	
};

/**@struct vector_array_const
 * @brief
 * Cette structure permet de gerer un tableau de vecteurs.
 **/
struct vector_array_const
{
	unsigned int n;
	const gsl_vector * const * vectors;

	/**@fn void vector_array :: setup(const gsl_vector * const * vect, unsigned int nb); 
	 * 
	 **/
	void setup(const gsl_vector * const * vect, unsigned int nb); 
	
	/**@fn vector_array :: vector_array(const gsl_vector * const * vect,  unsigned int nb); 
	 * 
	 */
	vector_array_const(const gsl_vector * const * vect, unsigned int nb); 
	
};

/**@fn unsigned int gsl_vector_array_fprintf(FILE * file,
											 const char * format,
											 const vector_array * array);
 * @param file : fichier
 * @param format : format de la chaine
 * Délimiteur gauche de la matrice \n
 * Délimiteur droit de la matrice \n
 * Séparateur de colonne de la matrice \n
 * Séparateur de ligne de la matrice \n
 * Format des nombres (%le ou %lf)
 * @param vector_array : pointeur vers la matrice
 **/								 
unsigned int gsl_vector_array_fprintf(FILE * file,
									  const char * format,
									  const vector_array * array);
unsigned int gsl_vector_array_fprintf(FILE * file,
									  const char * format,
									  const vector_array_const * array);
/**@fn unsigned int gsl_vector_array_fscanf(FILE * file,
											 const char * format,
											 vector_array * array);
 * @param file : fichier
 * @param format : format de la chaine
 * Délimiteur gauche de la matrice \n
 * Délimiteur droit de la matrice \n
 * Séparateur de colonne de la matrice \n
 * Séparateur de ligne de la matrice \n
 * Format des nombres (%le ou %lf)
 * @param vector_array : pointeur vers la matrice
 **/								 
unsigned int gsl_vector_array_fscanf(FILE * file,
									 const char * format,
									 vector_array * array);
									
/**@fn unsigned int gsl_vector_array_sprintf(char * string,
											 unsigned int size_max,
											 const char * format,
											 const vector_array * array)
 * @param file : fichier
 * @param format : format de la chaine
 * Délimiteur gauche de la matrice \n
 * Délimiteur droit de la matrice \n
 * Séparateur de colonne de la matrice \n
 * Séparateur de ligne de la matrice \n
 * Format des nombres (%le ou %lf)
 * @param vector_array : pointeur vers la matrice
 **/								 
unsigned int gsl_vector_array_sprintf(char * string,
									  unsigned int size_max,
									  const char * format,
									  const vector_array * array);
									  
/**@fn unsigned int gsl_vector_array_sscanf(const char * string,
											const char * format,
											vector_array * array);
 * @param file : fichier
 * @param format : format de la chaine
 * Délimiteur gauche de la matrice \n
 * Délimiteur droit de la matrice \n
 * Séparateur de colonne de la matrice \n
 * Séparateur de ligne de la matrice \n
 * Format des nombres (%le ou %lf)
 * @param vector_array : pointeur vers la matrice
 **/								 
unsigned int gsl_vector_array_sscanf(const char * string,
									 const char * format,
									 vector_array * array);
									
unsigned int gsl_vector_array_sprintf(char * string,
									  unsigned int size_max,
									  const char * format,
									  const vector_array_const * array);						
										
									  

									  

#endif
