/**@file gsl_matrix_io.hpp
 * @brief
 * Ce fichier permet la lecture des matrices dans un fichier de paramètres.
 * 
 **/
#ifndef GSL_MATRIX_IO_HPP
	#define GSL_MATRIX_IO_HPP
	#include <cstdio>
	#include <cstdlib>
	#include <cstring>
	#include <gsl/gsl_matrix.h>
	#define API_STRING_SIZEMAX 1024
	#define API_BUFFER_SIZEMAX 2560
	#define API_MAXSPACE 50
	#define API_SPLIT '^'
	#define API_DEFAULT_MATRIX_FORMAT "[^]^\t^\n^%lf"
	#define GSL_MATRIX_IO_GET_FORMAT(formats, begin, format)\
			{\
				unsigned int pos = 0;\
				pos = gsl_matrix_io_split( (formats) + (begin),\
										   API_SPLIT );\
				if (pos == 0)\
					++ pos;\
				(format) = (char *) malloc(sizeof(char) * (pos + 1));\
				if ((format))\
				{\
					memcpy(( format ), ( formats ) + (begin), pos);\
					(format)[pos] = '\0';\
					(begin) += pos + 1;\
				}\
			}
	#define UNREF(var)	if (var)\
							free((var));\
						var = NULL;
	#ifndef MIN
		#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
	#endif
	#define MATRIX_FORMAT_UNREF UNREF(l_matrix);\
								UNREF(r_matrix);\
								UNREF(col_sep);\
								UNREF(row_sep);\
								UNREF(n_format);
	#define MATRIX_FORMAT_REF 	char * l_matrix = NULL,\
									 * r_matrix = NULL,\
									 * row_sep = NULL,\
									 * col_sep = NULL,\
									 * n_format = NULL;\
								bool matrix_format_ok = true;\
								if (gsl_matrix_io_check_format(format) != 5)\
								{\
									fprintf(stderr, "Erreur : Format de matrice invalide\n");\
									return 0;\
								}\
								{\
									unsigned int curr_pos = 0;\
									GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, l_matrix);\
									GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, r_matrix);\
									GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, col_sep);\
									GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, row_sep);\
									GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, n_format);\
									if (! (l_matrix || r_matrix || row_sep || col_sep || n_format) )\
									{\
										UNREF(l_matrix);\
										UNREF(r_matrix);\
										UNREF(col_sep);\
										UNREF(row_sep);\
										UNREF(n_format);\
										fprintf ( stderr, "Error : Memory\n");\
										matrix_format_ok = false;\
									}\
								}




	/**@fn unsigned int gsl_matrix_sprintf_(char * string,
								         const unsigned int size_max,
									     const char * format,
										 const gsl_matrix * matrix)
	 * @param string : taille de la chaine
	 * @param size_max : taille maximale de la chaine
	 * @param format : format de la chaine
	 * Délimiteur gauche de la matrice \n
	 * Délimiteur droit de la matrice \n
	 * Séparateur de colonne de la matrice \n
	 * Séparateur de ligne de la matrice \n
	 * Format des nombres (%le ou %lf)
	 * @param matrix : matrice à écrire
	 * @brief
	 * Cette fonction écrit une matrice dans la chaine de caractère.
	 **/

	unsigned int gsl_matrix_sprintf_(char * string,
									 const unsigned int size_max,
									 const char * format,
									 const gsl_matrix * matrix);
	
	/**@fn unsigned int gsl_matrix_fprintf_(FILE * file,
											const char * format,
											const gsl_matrix * matrix)
	 * @param file : fichier
	 * @param format : format de la chaine
	 * Délimiteur gauche de la matrice \n
	 * Délimiteur droit de la matrice \n
	 * Séparateur de colonne de la matrice \n
	 * Séparateur de ligne de la matrice \n
	 * Format des nombres (%le ou %lf)
	 * @param matrix : matrice à écrire
	 * @brief
	 * Cette fonction écrit une matrice dans un fichier.
	 **/
	unsigned int gsl_matrix_fprintf_(FILE * file,
									 const char * format,
									 const gsl_matrix * matrix);
									 
									 
	/**@fn unsigned int gsl_matrix_sscanf_(const char * string,
									const char * format,
									gsl_matrix ** matrix)
	 * @param string : chaine de charactères
	 * @param format : format de la chaine
	 * Délimiteur gauche de la matrice \n
	 * Délimiteur droit de la matrice \n
	 * Séparateur de colonne de la matrice \n
	 * Séparateur de ligne de la matrice \n
	 * Format des nombres (%le ou %lf)
	 * @param matrix : pointeur vers la matrice
	 * @return
	 * - 0 en cas d'échéc
	 * - nombre de charactères lus en cas de réussite.
	 * @brief
	 * Cette fonction lit une matrice dans une chaine de charactères.
	 */
	unsigned int gsl_matrix_sscanf_(const char * string,
									const char * format,
									gsl_matrix ** matrix);
									
	/**@fn unsigned int gsl_matrix_fscanf_(FILE * file,
									const char * format,
									gsl_matrix ** matrix)
									
	 * @param file : fichier
	 * @param format : format de la chaine
	 * Délimiteur gauche de la matrice \n
	 * Délimiteur droit de la matrice \n
	 * Séparateur de colonne de la matrice \n
	 * Séparateur de ligne de la matrice \n
	 * Format des nombres (%le ou %lf)
	 * @param matrix : pointeur vers la matrice
	 * @return
	 * - 0 en cas d'échéc
	 * - 1 sinon
	 * @brief
	 * Cette fonction lit une matrice dans le fichier
	 */								
	unsigned int gsl_matrix_fscanf_(FILE * file,
									const char * format,
									gsl_matrix ** matrix);				
									
																 
	/**@fn unsigned int gsl_matrix_io_split(const char * string,
											const char character)
	 * @param string : chaine
	 * @param character : charactère recherché
	 * @return position du charactère recherché
	 */
	unsigned int gsl_matrix_io_split(const char * string,
									 const char character);		 
	

	/**@fn unsigned int gsl_matrix_io_check_format(const char * format)
	 * @param format : format à analyser
	 * @return Nombre de lignes du format.
	 * @brief
	 * Cette fonction renvoie le nombre d'arguments dans le format.
	 */
	unsigned int gsl_matrix_io_check_format(const char * format);
	
	/**@fn unsigned int gsl_matrix_row_sprintf(char * string,
												const unsigned int size_max,
												char * buffer,
												const buffer_size,
												const char * col_sep,
												const char * n_format,
												const double * data,
												const unsigned int size_row)
	 * @param string : chaine dans laquelle on écrit
	 * @param size_max : taille maximale de la chaine
	 * @param buffer : buffer d'écriture 
	 * @param buffer_size : taille du buffer
	 * @param col_sep : séparateur de colonnes
	 * @param n_format : foramt des nombres
	 * @param data : nombre de la ligne
	 * @param size_row : taille de la ligne
	 * @return 
	 * - 0 si échec d'écriture
	 * - taille de la chaine écrite
	 * @brief
	 * Cette fonction écrit une ligne de matrice dans une chaine de charactères.
	 * 
	 */
	unsigned int gsl_matrix_row_sprintf(char * string,
										 const unsigned int size_max,
										 char * buffer,
										 const char * col_sep,
										 const char * n_format,
										 const double * data,
										 const unsigned int size_row);
										  
										  
	
#endif
