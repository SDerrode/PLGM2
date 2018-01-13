
#ifndef API_VARIABLE_HPP
#define API_VARIABLE_HPP
#define API_FLOAT 1
#define API_MATRIX  2
#define API_STRING  3
#define API_VECTOR_ARRAY  4
#define API_DEFAULT_FORMAT "{^}^\"^[^]^\t^\n^%lf"
/*
* Délimiteur des chaines \n
	 * Délimiteur gauche de la matrice \n
	 * Délimiteur droit de la matrice \n
	 * Séparateur de colonne de la matrice \n
	 * Séparateur de ligne de la matrice \n
	 * Format des nombres (%le ou %lf)
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "gsl_matrix_io.hpp"
#include "gsl_vector_io.hpp"
/**@class api_variable
 **/
class api_variable
{
	public :
		/**@fn api_variable :: api_variable(const char * name = "",
											int type = 0,
											void * data = NULL);
		 * @param name : nom de la variable
		 * @param type : type de variabl
		 * @param data : données de la variable
		 */
		api_variable(const char * name = "",
		             int type = 0,
		             const void * data = NULL);
		/**@fn api_variable :: api_variable(const api_variable & variable);
		 */
		api_variable(const api_variable & variable);

		/**@fn void api_variable :: set_name(const char * name);*
		 * @param name : nom de la variable
		 */
		void set_name(const char * name,
		              unsigned int size = 0);

		/**@fn api_variable & api_variable :: operator = (const api_variable & var);
		 * @param var : variable
		 * @brief
		 * Opérateur de recopie.
		 **/
		api_variable & operator = (const api_variable & var);

		/**@fn void api_variable :: set_float(const double & number);
		 * @param number : nombre
		 */
		void set_float(const double & number);

		/**@fn void api_variable :: set_matrix(const gsl_matrix * matrix);
		 *
		 */
		void set_matrix_const(const gsl_matrix * matrix);

		/** void api_variable :: set_string(const char * string);
		 *
		 */
		void set_string_const(const char * string);

		/**@fn void api_variable :: set_vector_array(const vector_array & array);
		 *
		 */
		void set_vector_array_const(const vector_array_const & array);

		/**@fn void api_variable :: set_vector(const gsl_vector * vector)
		 * @param vector : vecteur
		**/
		void set_vector(const gsl_vector * vector);

		/**@fn void api_variable :: set_matrix(const gsl_matrix * matrix);
		 *
		 */
		void set_matrix(const gsl_matrix * matrix);

		/** void api_variable :: set_string(const char * string);
		 *
		 */
		void set_string(const char * string,
		                unsigned int size = 0);

		/**@fn void api_variable :: set_vector_array(const vector_array & array);
		 *
		 */
		void set_vector_array(const vector_array & array);

		/**@fn inline double & api_variable :: get_float();
		 * @brief
		 * Cette méthode renvoie le flottant
		 */
		inline double & get_float()
		{
			return *((double * ) data);
		}

		/**@fn gsl_vector api_variable :: get_vector_const() const;
		 * @brief
		 * Cette méthode renvoie un vecteur
		**/
		gsl_vector get_vector_const() const;

		/**@fn inline vector_array & api_variable :: get_vector_array_const()
		 *
		 **/
		inline vector_array_const get_vector_array_const() const
		{
			if (API_VECTOR_ARRAY == type)
				return vector_array_const(((vector_array*) data)->vectors, ((vector_array_const*) data)->n);
			else if (type == -API_VECTOR_ARRAY)
				return (* ((vector_array_const*) const_data));
			return vector_array_const(NULL, 0);
		}

		/**@fn inline const gsl_matrix * api_variable :: get_matrix_const()
		 * @brief
		 * Cette méthode renvoie la matrice
		 */
		inline const gsl_matrix * get_matrix_const() const
		{
			if (type == API_MATRIX )
				return ((const gsl_matrix*) data);
			else if  (type == -API_MATRIX )
				return ((const gsl_matrix*) const_data);
			else
				return NULL;
		}

		/**@fn inline const char * api_variable :: get_string_const()
		 * @brief
		 * Cette méthode renvoie la chaine de charactère
		 */
		inline const char * get_string_const() const
		{
			if (type == API_STRING)
				return ((const char*) data);
			else if (type == -API_STRING)
				return ((const char*) const_data);
			else
				return NULL;
		}

		/**@fn inline int api_variable :: get_type() const
		 * @return
		 * Type de la variable.
		 *
		 **/
		inline int get_type() const
		{
			return type;
		}


		/**@fn gsl_vector api_variable :: get_vector();
		 * @brief
		 * Cette méthode renvoie un vecteur
		**/
		gsl_vector get_vector();

		/**@fn inline vector_array* api_variable :: get_vector_array()
		 *
		 **/
		inline vector_array* get_vector_array()
		{
			return ((vector_array*) data);
		}

		/**@fn inline gsl_matrix * api_variable :: get_matrix()
		 * @brief
		 * Cette méthode renvoie la matrice
		 */
		inline gsl_matrix * get_matrix()
		{
			return ((gsl_matrix*) data);
		}

		/**@fn inline char * api_variable :: get_string()
		 * @brief
		 * Cette méthode renvoie la chaine de charactère
		 */
		inline char * get_string()
		{
			return ((char*) data);
		}

		/**@fn void api_variable :: set_cmt( const char * _cmt );
		 * @param _cmt :données sup. sur la variable
		 * @brief
		 * Met à jour les commentaires sur la variable
		 **/
		void set_cmt( const char * _cmt );

		/**@fn inline const char * api_variable :: get_name()
		 * @brief
		 * Renvoie le nom de la variable
		 */
		inline const char * get_name() const
		{
			return name;
		}

		/**@fn inline bool api_variable :: is_float()
		 * @brief
		 * Teste si c'est un flottant
		 */
		inline bool is_float() const
		{
			return (type == API_FLOAT || type == -API_FLOAT);
		}

		/**@fn inline bool api_variable :: is_matrix()
		 * @brief
		 * Teste si c'est uen matrice
		 */
		inline bool is_matrix() const
		{
			return (type == API_MATRIX || type == -API_MATRIX);
		}

		/**@fn inline bool api_variable :: is_vector()
		 * @brief
		 * Teste si c'est un vectgeur
		 */
		inline bool is_vector() const
		{
			if (type != API_MATRIX)
				return false;
			return (((gsl_matrix*) data)->size1 == 1 || ((gsl_matrix*) data)->size2 == 1);
		}

		/**@fn inline bool api_variable :: is_string()
		 * @brief
		 * Teste si c'est uen matrice
		 */
		inline bool is_string() const
		{
			return (type == API_STRING || type == -API_STRING);
		}

		/**@fn inline bool api_variable :: is_vector_array() const
		 *
		 **/
		inline bool is_vector_array() const
		{
			return (type == API_VECTOR_ARRAY || type == -API_VECTOR_ARRAY);
		}

		/**@fn inline const char * api_variable :: get_comment() const
		 * @brief
		 * Retourne les commentaires sur la variable
		 **/
		inline const char * get_comment() const
		{
			return comment;
		}


		/**@fn unsigned int api_variable :: sscanf(const char * string,
								   const char * format);
		 * @param string : chaine de charactères
		 * @param format : format de la chaine
		 * Délimiteur des chaines \n
		 * Délimiteur gauche de la matrice \n
		 * Délimiteur droit de la matrice \n
		 * Séparateur de colonne de la matrice \n
		 * Séparateur de ligne de la matrice \n
		 * Format des nombres (%le ou %lf)
		 */
		unsigned int sscanf_(	const char * string,
		                        const char * format);


		/**@fn unsigned int api_variable :: sprintf(char * string,
													const char * format,
													unsigned int size_string);
		 * @param string : chaine de charactères
		 * @param format : format de la chaine
		 * Délimiteur des chaines \n
		 * Délimiteur gauche de la matrice \n
		 * Délimiteur droit de la matrice \n
		 * Séparateur de colonne de la matrice \n
		 * Séparateur de ligne de la matrice \n
		 * Format des nombres (%le ou %lf)
		 */
		unsigned int sprintf_(char * string,
		                      const char * format,
		                      unsigned int size_string);

		/**@fn unsigned int api_variable :: fprintf(FILE * file,
													const char * format)
		 * @param file : fichier
		 * @param format : format
		 * @brief
		 * Cette fonction écrit la variable dans un fichier sous la forme
		 * Name = "string"
		 * Name = [matrix]
		 * Name = 42
		 */
		unsigned int fprintf_(	FILE * file,
		                        const char * format = API_DEFAULT_FORMAT);


		/**@fn unsigned int api_variable :: fscanff(FILE * file,
													const char * format)
		 * @param file : fichier
		 * @param format : format
		 * @brief
		 * Cette fonction lit la variable dans un fichier sous la forme
		 * Name = "string"
		 * Name = [matrix]
		 * Name = 42
		 */
		unsigned int fscanf_(	FILE * file,
		                        const char * format = API_DEFAULT_FORMAT);

		/**@fn api_variable :: ~api_variable()
		 */
		~api_variable();

	protected :

		/**@fn void api_variable :: _free();
		 * @brief
		 * Libère la mémoire allouée utilisée par l'objet
		 */
		void _free();

		/**@fn void api_variable :: initialize();
		 * @brief
		 * Initialisation de l'objet
		 */
		void initialize();


		char name[API_STRING_SIZEMAX];
		int type;
		void * data;
		const void * const_data;
		char * comment;
};





#endif
