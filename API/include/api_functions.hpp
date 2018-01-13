/**@file api_functions.hpp
 * @brief
 * Ce fichier contient les fonctions utiles pour la gestion des paramètres du programme
 * 
 **/
#ifndef _API_FUNCTIONS_HPP_
#define _API_FUNCTIONS_HPP_
#include "api_parameters.hpp"
#include <iostream>
using namespace std;

/**@fn int api_get_integer(	api_parameters & params,
							const char * name,
							int * number,
							ostream * out = NULL );
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/
int api_get_integer( api_parameters & params,
					 const char * name,
					 int * number,
					 ostream * out = NULL );
					 
/**@fn int api_get_positive_integer( api_parameters & params,
									 const char * name,
									 unsigned int * number,
									 ostream * out = NULL  );
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/	 
int api_get_positive_integer( api_parameters & params,
							 const char * name,
							 unsigned int * number,
							 ostream * out = NULL  );
/**@fn int api_get_float( 	api_parameters & params,
							const char * name,
							float * number,
							ostream * out = NULL  )
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/		 
int api_get_float( 	api_parameters & params,
					const char * name,
					float * number,
					ostream * out = NULL  );
/**@fn int api_get_double(	api_parameters & params,
							const char * name,
							double * nb,
							ostream * out = NULL  );
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/	 
int api_get_double(	api_parameters & params,
					const char * name,
					double * nb,
					ostream * out = NULL  );
					
/**@fn int api_get_vector(	api_parameters & params,
							const char * name,
							gsl_vector * vect,
							ostream * out = NULL  );
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/	 
int api_get_vector(	api_parameters & params,
					const char * name,
					gsl_vector * vect,
					ostream * out = NULL  );

/**@fn int api_get_matrix(	api_parameters & params,
							const char * name,
							gsl_matrix * matrix,
							ostream * out = NULL  );
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/	 
int api_get_matrix(	api_parameters & params,
					const char * name,
					gsl_matrix * matrix,
					ostream * out = NULL  );
/**@fn int api_get_string(	api_parameters & params,
							const char * name,
							string * str,
							ostream * out = NULL  );
 * @param params : paramètres chargés
 * @param[in] name : nom de la variable
 * @param[out] number : nombre à lire
 * @param out : flux d'erreur
 **/	 
int api_get_string(	api_parameters & params,
					const char * name,
					string * str,
					ostream * out = NULL  );



#endif
