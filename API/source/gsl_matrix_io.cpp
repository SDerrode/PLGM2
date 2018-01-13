#include "gsl_matrix_io.hpp"
/**@fn unsigned int gsl_matrix_io_check_format(const char * format)
 * @param format : format à analyser
 * @return Nombre de lignes du format.
 * @brief
 * Cette fonction renvoie le nombre d'arguments dans le format.
 */
unsigned int gsl_matrix_io_check_format(const char * format)
{
	unsigned int j = 1;
	unsigned int k = 0;
	for (unsigned int i = 0; format[i] != '\0'; ++ i)
	{
		if (format[i] == '^')
		{
			if (i != (k + 1) || k == 0)
			{
				k = i;
				++ j;
			}
		}
	}
	return j;
}

/**@fn unsigned int gsl_matrix_io_split(const char * string,
										const char character)
 * @param string : chaine
 * @param character : charactère recherché
 * @return position du charactère recherché
 */
unsigned int gsl_matrix_io_split(const char * string,
                                 const char character)
{
	unsigned int i;
	for (i = 0; string[i] != '\0'; ++ i)
	{
		if (string[i] == character)
		{
			if (string[i + 1] != character)
				return i;
		}
	}
	return i;
}

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
                                    const unsigned int size_row)
{
	unsigned int lenght;
	unsigned int string_pos = 0;
	unsigned int size_2 = size_row - 1;

	for (unsigned int i = 0; i < size_2; ++ i)
	{
		//Copie du nombre dans le buffer
		sprintf(buffer, n_format, data[i]);

		//Test de la taille de la chaine
		if ( ( lenght = strlen(buffer) ) > ( size_max - string_pos ) )
			return 0;

		//Recopie du nombre
		strcpy(string + string_pos, buffer);
		string_pos += lenght;

		//Séparateur de colonne
		if ( ( lenght = strlen(col_sep) ) > ( size_max - string_pos ) )
			return 0;
		strcpy(string + string_pos, col_sep);
		string_pos += lenght;
	}

	//Copie du nombre dans le buffer
	sprintf(buffer, n_format, data[size_2]);

	//Test de la taille de la chaine
	if ( ( lenght = strlen(buffer) ) > ( size_max - string_pos ) )
		return 0;
	//Recopie du nombre
	strcpy(string + string_pos, buffer);
	string_pos += lenght;

	return string_pos;
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
                                 const gsl_matrix * matrix)
{
	unsigned int string_pos = 0;
	unsigned int lenght;
	unsigned int size1;
	char * buffer = NULL; //Buffer de recopie
	MATRIX_FORMAT_REF
	if (!matrix_format_ok)
		return 0;
	//Allocation du buffer
	{
		{
			buffer = (char *) malloc(sizeof(char) * ( API_BUFFER_SIZEMAX + 1 ) );
		}
		if (!buffer)
		{
			MATRIX_FORMAT_UNREF
			fprintf ( stderr, "Error : Memory\n");
			return 0;
		}
	}

	//Ecriture du "["
	if ( ( lenght = strlen(l_matrix) ) >  (size_max - string_pos) )
	{
		fprintf(stderr, "Error : Matrix too long for the strign (> %du char.).\n", size_max);
		MATRIX_FORMAT_UNREF
		UNREF(buffer);
		return 0;
	}
	strcpy(string + string_pos, l_matrix);
	string_pos += lenght;

	//Ecriture des lignes
	size1 = matrix->size1 - 1;
	for ( unsigned int i = 0; i < size1; ++ i )
	{
		if ( ( lenght = gsl_matrix_row_sprintf(string + string_pos,
		                                       size_max - string_pos,
		                                       buffer,
		                                       col_sep,
		                                       n_format,
		                                       matrix->data + matrix->tda * i,
		                                       matrix->size2)
		     ) == 0
		   )
		{
			fprintf(stderr, "Error : Matrix too long for the strign (> %du char.).\n", size_max);
			MATRIX_FORMAT_UNREF
			UNREF(buffer);
			return 0;
		}
		string_pos += lenght;

		//Séparateur de lignes

		if ( ( lenght = strlen(row_sep) ) > ( size_max - string_pos ) )
		{
			fprintf(stderr, "Error : Matrix too long for the strign (> %du char.).\n", size_max);
			MATRIX_FORMAT_UNREF
			UNREF(buffer);
			return 0;
		}
		strcpy(string + string_pos, row_sep);
		string_pos += lenght;
	}
	//Dernière ligne
	if ( ( lenght = gsl_matrix_row_sprintf(string + string_pos,
	                                       size_max - string_pos,
	                                       buffer,
	                                       col_sep,
	                                       n_format,
	                                       matrix->data + matrix->tda * size1,
	                                       matrix->size2)
	     ) == 0
	   )
	{
		fprintf(stderr, "Error : Matrix too long for the strign (> %du char.).\n", size_max);
		MATRIX_FORMAT_UNREF
		UNREF(buffer);
		return 0;
	}
	string_pos += lenght;

	//Ecriture du "]"
	if ( ( lenght = strlen(r_matrix) ) >  (size_max - string_pos) )
	{
		fprintf(stderr, "Error : Matrix too long for the strign (> %du char.).\n", size_max);
		MATRIX_FORMAT_UNREF
		UNREF(buffer);
		return 0;
	}
	strcpy(string + string_pos, r_matrix);
	string_pos += lenght;


	//Libération mémoire
	MATRIX_FORMAT_UNREF
	UNREF(buffer);

	return string_pos;
}
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
                                 const gsl_matrix * matrix)
{
	char * buffer;
	unsigned int lenght;
	unsigned int sizemax = (matrix->size1 * matrix->size2 * API_MAXSPACE );



	buffer = (char *) malloc( sizemax * sizeof(char));
	if (!buffer)
	{
		fprintf ( stderr, "Error : Memory\n");
		return 0;
	}

	if ( ( lenght = gsl_matrix_sprintf_(buffer,
	                                    sizemax,
	                                    format,
	                                    matrix )
	     ) == 0
	   )
	{
		free(buffer);
		return 0;
	}
	if ( fprintf(file, "%s", buffer) == 0 )
	{
		free(buffer);
		fprintf(stderr, "Error during writting file.\n");
		return  0;
	}
	free(buffer);
	return 1;
}

/**@fn unsigned int gsl_matrix_row_sscanf(const char * string,
										  const char * col_sep,
										  const char * row_sep,
										  const char * r_matrix,
										  const char * n_format,
										  double * data,
										  const unsigned int size_row)
 * @param string : chaine de charactères
 * @param col_sep : séparateur de collones
 * @param row_sep : séparateur de lignes
 * @param r_matrix : ]
 * @param n_format : format des nombres
 * @param data : lignes
 * @param size_row : taille de la ligne
 * @return
 * - Nombre de charactère lus
 * - 0 en cas de problèmes
 * @brief
 * Cette fonction lit une ligne de matrice.
 *
 */
unsigned int gsl_matrix_row_sscanf(const char * string,
                                   const char * col_sep,
                                   const char * row_sep,
                                   const char * r_matrix,
                                   const char * n_format,
                                   double * data,
                                   const unsigned int size_row)
{
	unsigned int string_pos = 0;
	unsigned int string_size;
	unsigned int lenght;
	unsigned int tmp_width = 0;
	//Récupération des dim.*
	string_size = strlen(string);

	//std::cerr << "string=" << string << ", col_sep=" << col_sep << ", row_sep=" << row_sep;

	//Détermination des dimensions
	if (string_pos == string_size)
	{
		fprintf(stderr, "Error : Invalid matrix\n");
		return 1;
	}

	//Détermination de la larguer de la ligne
	bool next = false;
	bool read = true;
	do
	{
		//Fin de matrice
		lenght = strlen(r_matrix);
		if ( (string_size - string_pos) <  (lenght) )
		{
			fprintf(stderr, "Error : Invalid matrix\n");
			return 1;
		}
		if (! memcmp ( r_matrix, string + string_pos, lenght * sizeof(char) ) )
			next = true;
		//Fin de ligne
		else
		{
			lenght = strlen(row_sep);
			if ( (string_size - string_pos) <  (lenght) )
			{
				fprintf(stderr, "Error : Invalid matrix\n");
				return 0;
			}
			if (! memcmp ( row_sep, string + string_pos, lenght * sizeof(char) ) )
			{
				next = true;
				tmp_width += 1;
			}
			//Séparateur de colonne
			else
			{
				lenght = strlen(col_sep);
				if ( (string_size - string_pos) >=  (lenght) )
				{
					if (! memcmp ( col_sep, string + string_pos, lenght * sizeof(char) ) )

						read = true;
					else if (read)
					{
						if (!sscanf(string + string_pos, n_format, data + tmp_width))
						{
							fprintf(stderr, "Warning : number format!\n");
							data[tmp_width] = 0;
						}
						else
						{
							++ tmp_width;
							read = false;
						}
					}
					lenght = 1;
				}
				else
				{
					if (read)
					{
						if (!sscanf(string + string_pos, n_format, data + tmp_width))
						{
							fprintf(stderr, "Warning : number format!\n");
							data[tmp_width] = 0;
						}
						else
						{
							++ tmp_width;
							read = false;
						}
					}
					lenght = 1;
				}
			}
		}
		string_pos += lenght;
	}
	while (! next);
	return string_pos;
}

/**@fn int gsl_matrix_io_get_dims(unsigned int * size1,
								  unsigned int * size2,
								  const char * l_matrix,
								  const char * col_sep,
								  const char * row_sep,
								  const char * r_matrix,
								  const char * string)
 * @param size1 : largeur
 * @param size2 : hauteur
 * @param l_matrix : "["
 * @param col_sep : séparateur de colonnes
 * @param row_sep : sép. de lignes
 * @param r_matrix : "]"
 * @param string : chaine de caractères
 * @return
 * - 0 en cas de réssite d'acquisition des dimensions de la matrice
 * - 1 en cas d'erreur
 * @brief
 * Cette fonction détermine la dimension de la matrice stockée dans la chaine de charactère
 */
int gsl_matrix_io_get_dims(unsigned int * size1,
                           unsigned int * size2,
                           const char * l_matrix,
                           const char * col_sep,
                           const char * row_sep,
                           const char * r_matrix,
                           const char * string)
{
	unsigned int tmp_width = 0;
	unsigned int string_pos = 0;
	unsigned int string_size;
	unsigned int lenght;
	//Mise à zéro des dim.
	(*size1) = 0;
	(*size2) = 0;


	//Récupération des dim.*
	string_size = strlen(string);

	//Détection du "["
	{
		lenght = strlen(l_matrix);
		do
		{
			if ( (string_size - string_pos) <  (lenght) )
			{
				fprintf(stderr, "Error : No matrix in the string\n");
				return 1;
			}
			++ string_pos;
		}
		while (memcmp ( l_matrix, string + string_pos - 1, lenght * sizeof(char) ) );
		string_pos += lenght;
	}




	//Détermination des dimensions
	bool next0 = false;
	do
	{
		if (string_pos == string_size)
		{
			fprintf(stderr, "Error : Invalid matrix\n");
			return 1;
		}

		//Détermination de la larguer de la ligne
		tmp_width = 0;
		bool next = false;
		do
		{
			//Fin de matrice
			lenght = strlen(r_matrix);
			if ( (string_size - string_pos) <  (lenght) )
			{
				fprintf(stderr, "Error : Invalid matrix\n");
				return 1;
			}
			if (! memcmp ( r_matrix, string + string_pos, lenght * sizeof(char) ) )
			{
				tmp_width += 1;
				next = true;
				next0 = true;
			}
			//Fin de ligne
			else
			{
				lenght = strlen(row_sep);
				if ( (string_size - string_pos) <  (lenght) )
				{
					fprintf(stderr, "Error : Invalid matrix\n");
					return 1;
				}
				if (! memcmp ( row_sep, string + string_pos, lenght * sizeof(char) ) )
				{
					next = true;
					tmp_width += 1;
				}
				//Séparateur de colonne
				else
				{
					lenght = strlen(col_sep);
					if ( (string_size - string_pos) >=  (lenght) )
					{
						if (! memcmp ( col_sep, string + string_pos, lenght * sizeof(char) ) )
							tmp_width += 1;
						else
							lenght = 1;
					}
					else
						lenght = 1;
				}
			}
			string_pos += lenght;
		}
		while (! next);
		//Check de la largeur
		if ( ( *size2 ) > 0)
		{
			if ( (*size2) != tmp_width )
			{
				fprintf(stderr, "Error : No-constant width.\n");
				return 1;
			}
		}
		else
			(*size2) = tmp_width;
		(*size1) ++;
	}
	while (! next0);
	return 0;
}
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
                                gsl_matrix ** matrix)
{
	unsigned int string_pos = 0;
	unsigned int lenght;
	unsigned int size1,
	         size2;
	unsigned int string_size;

	//Contrôle du format
	if (gsl_matrix_io_check_format(format) != 5)
	{
		fprintf(stderr, "Erreur : Format de matrice invalide\n");
		return 0;
	}

	//Récupération du format
	MATRIX_FORMAT_REF
	if (!matrix_format_ok)
		return 0;

	//Récupération des dimensions de la matrice
	if (gsl_matrix_io_get_dims(&size1,
	                           &size2,
	                           l_matrix,
	                           col_sep,
	                           row_sep,
	                           r_matrix,
	                           string))
	{
		MATRIX_FORMAT_UNREF
		return 0;
	}

	//Allocation de la matrice
	(*matrix) = gsl_matrix_calloc(size1, size2);

	//Recherche du premier caractère
	//Récupération des dim.*
	string_size = strlen(string);

	//Détection du "["
	{
		lenght = strlen(l_matrix);
		do
		{
			if ( (string_size - string_pos) <  (lenght) )
			{
				fprintf(stderr, "Error : No matrix in the string\n");
				MATRIX_FORMAT_UNREF
				gsl_matrix_free(*matrix);
				return 1;
			}
			++ string_pos;
		}
		while (memcmp ( l_matrix, string + string_pos - 1, lenght * sizeof(char) ) );
		string_pos += lenght - 1;
	}
	for (unsigned int i = 0; i < (*matrix)->size1; ++ i)
	{
		if ( (lenght = gsl_matrix_row_sscanf(string + string_pos,
		                                     col_sep,
		                                     row_sep,
		                                     r_matrix,
		                                     n_format,
		                                     (*matrix)->data + (*matrix)->tda * i,
		                                     (*matrix)->size2) ) == 0 )
		{
			MATRIX_FORMAT_UNREF
			gsl_matrix_free(*matrix);
			return 0;
		}
		string_pos += lenght;
	}


	//Lib. mémoire
	MATRIX_FORMAT_UNREF
	return string_pos;
}
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
                                gsl_matrix ** matrix)
{
	char * buffer;
	unsigned int size;
	unsigned int curr;
	unsigned int pos;
	curr = ftell(file);
	fseek(file, 0, SEEK_END);
	size = ftell(file) - curr + 1;
	fseek(file, curr, SEEK_SET);

	buffer = (char *) malloc(sizeof(char) * (size + 1));
	if (!buffer)
	{
		fprintf ( stderr, "Error : Memory\n");
		return 0;
	}

	//Recopie du fichier
	size = fread(buffer, sizeof(char), size, file);
	buffer[size - 1] = '\0';

	//Lecture de la matrice
	if ((pos = gsl_matrix_sscanf_(buffer,
	                              format,
	                              matrix)) == 0 )
	{
		free(buffer);
		return 0;
	}
	fseek(file, curr + pos, SEEK_SET);
	free(buffer);
	return 1;
}
