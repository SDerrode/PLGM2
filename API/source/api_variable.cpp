#include "api_variable.hpp"
#include <iostream>
using namespace std;
#define UNREF_FORMAT UNREF(vector_array_l_sep);\
					 UNREF(vector_array_r_sep);\
					 UNREF(chain_sep);\
					 UNREF(matrix_left);\
					 UNREF(matrix_right);\
					 UNREF(col_sep);\
					 UNREF(row_sep);\
					 UNREF(number_format);\
					 UNREF(vector_array_format);
#define REF_FORMAT 	char * chain_sep = NULL,\
						 * vector_array_l_sep = NULL,\
						 * vector_array_r_sep = NULL,\
						 * matrix_left = NULL,\
						 * matrix_right = NULL,\
						 * col_sep = NULL,\
						 * row_sep = NULL,\
						 * number_format = NULL,\
						 * vector_array_format = NULL;\
					const char * matrix_format;\
					bool format_ok = true;\
					{\
						unsigned int curr_pos = 0;\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, vector_array_l_sep);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, vector_array_r_sep);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, chain_sep);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, matrix_left);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, matrix_right);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, col_sep);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, row_sep);\
						GSL_MATRIX_IO_GET_FORMAT(format, curr_pos, number_format);\
						vector_array_format = (char * ) calloc((strlen(vector_array_l_sep) + strlen(vector_array_r_sep) + strlen(col_sep) + strlen(row_sep) + strlen(number_format) + 5), sizeof(char)) ;\
						if (! (vector_array_l_sep && vector_array_r_sep && chain_sep && matrix_left && matrix_right && row_sep && col_sep && number_format && vector_array_format) )\
						{\
							UNREF_FORMAT\
							fprintf ( stderr, "Error : Memory\n");\
							format_ok = false;\
						}\
						else\
						{\
							strcpy(vector_array_format, vector_array_l_sep);\
							vector_array_format[strlen(vector_array_format)] = '^';\
							strcpy(vector_array_format + strlen(vector_array_format), vector_array_r_sep);\
							vector_array_format[strlen(vector_array_format)] = '^';\
							strcpy(vector_array_format + strlen(vector_array_format), col_sep);\
							vector_array_format[strlen(vector_array_format)] = '^';\
							strcpy(vector_array_format + strlen(vector_array_format), row_sep);\
							vector_array_format[strlen(vector_array_format)] = '^';\
							strcpy(vector_array_format + strlen(vector_array_format), number_format);\
							vector_array_format[strlen(vector_array_format)] = '\0';\
							matrix_format = format + strlen(vector_array_l_sep) + strlen(vector_array_r_sep) + strlen(chain_sep) + 3;\
						}\
					}
unsigned int api_is_string(const char * data,
                           const char * chain_sep)
{
	unsigned int size_format;
	if ( strlen(data) < (size_format = strlen(chain_sep) ) )
		return 0;
	if (memcmp(chain_sep, data, size_format * sizeof(char)))
		return 0;
	return size_format;
}

unsigned int api_is_matrix(const char * data,
                           const char * l_matrix)
{
	unsigned int size_format;
	if ( strlen(data) < (size_format = strlen(l_matrix) ) )
		return 0;
	if (memcmp(l_matrix, data, size_format * sizeof(char)))
		return 0;
	return size_format;
}

api_variable & api_variable :: operator = (const api_variable & var)
{

	if (&var == this)
		return *this;
	else
	{

		_free();
		initialize();
		//Nom
		api_variable :: set_name(var.name);
		//Type
		type = var.type;

		//data
		if ((var.data && type > 0) || (var.const_data && type < 0))
		{
			switch (type)
			{
			case (API_FLOAT):
				api_variable :: set_float( *( (const double *) var.data ) );
				break;
			case (API_MATRIX):
				api_variable :: set_matrix( (const gsl_matrix *) var.data);
				break;
			case (API_STRING):
				api_variable :: set_string( (const char *) var.data );
				break;
			case (API_VECTOR_ARRAY):
				api_variable :: set_vector_array( * ((const vector_array *) var.data ) );
				break;
			case (-API_MATRIX):
				api_variable :: set_matrix_const( (const gsl_matrix *) var.const_data);
				break;
			case (-API_STRING):
				api_variable :: set_string_const( (const char *) var.const_data);
				break;
			case (-API_VECTOR_ARRAY):

				const_data = var.const_data;
				break;



			default:
				fprintf(stderr, "Warning : Unknown data type. %s\n", name);
				type = 0;
				break;
			}
		}
		api_variable :: set_cmt(var.comment);
	}

	return *this;
}



api_variable :: api_variable(const char * _name,
                             int _type,
                             const void * _data)
{
	api_variable :: initialize();
	//Nom
	api_variable :: set_name(_name);
	//Type
	type = _type;
	//data
	if (_data)
	{
		switch (type)
		{
		case (API_FLOAT):
			api_variable :: set_float( *( (const double *) _data ) );
			break;
		case (API_MATRIX):
			api_variable :: set_matrix( (const gsl_matrix *) _data);
			break;
		case (API_STRING):
			api_variable :: set_string( (const char *) _data );
			break;
		case (API_VECTOR_ARRAY):
			api_variable :: set_vector_array( *((const vector_array *) _data) );
			break;
		case (-API_MATRIX):
			api_variable :: set_matrix_const( (const gsl_matrix *) _data);
			break;
		case (-API_STRING):
			api_variable :: set_string_const( (const char *) _data );
			break;
		case (-API_VECTOR_ARRAY):
			api_variable :: set_vector_array_const( *((const vector_array_const *) _data) );
			break;

		default:
			fprintf(stderr, "Warning : Unknown data type. %s\n", name);
			type = 0;
			break;
		}
	}

}
api_variable :: api_variable(const api_variable & variable)
{
	api_variable :: initialize();
	api_variable :: set_name(variable.name);
	type = variable.type;
	if ((variable.data && type > 0) || (variable.const_data && type < 0))
	{

		switch (type)
		{
		case (API_FLOAT):
			api_variable :: set_float( *((double * ) variable.data) );
			break;
		case (API_MATRIX):
			api_variable :: set_matrix( ((gsl_matrix*) variable.data) );
			break;
		case (API_STRING):
			api_variable :: set_string( (char*) variable.data) ;
			break;
		case (API_VECTOR_ARRAY):
			api_variable :: set_vector_array( *((const vector_array *) variable.data) );
			break;

		case (-API_MATRIX):
			api_variable :: set_matrix_const( (const gsl_matrix *) variable.const_data);
			break;
		case (-API_STRING):
			api_variable :: set_string_const( (const char *) variable.const_data);
			break;
		case (-API_VECTOR_ARRAY):

			const_data = variable.const_data;
			break;
		default:
			fprintf(stderr, "Warning : Unknown data type.\n");
			type = 0;
			break;
		}
	}
	api_variable :: set_cmt(variable.comment);
}


void api_variable :: set_vector_array(const vector_array & array)
{
	api_variable :: _free();
	//Type
	type = API_VECTOR_ARRAY;
	data = (void *) new vector_array(array);
}

void api_variable :: set_float(const double & number)
{
	api_variable :: _free();
	//Type
	type = API_FLOAT;
	data = malloc(sizeof(double));
	*( (double *) data ) = number;
}
void api_variable :: set_matrix(const gsl_matrix * matrix)
{
	api_variable :: _free();
	//Type
	type = API_MATRIX;
	data = (void*) gsl_matrix_alloc( matrix->size1,
	                                 matrix->size2);
	gsl_matrix_memcpy((gsl_matrix *) data,
	                  matrix);
}
void api_variable :: set_vector(const gsl_vector * vector)
{
	api_variable :: _free();
	//Type
	type = API_MATRIX;
	data = (void*) gsl_matrix_alloc( vector->size,
	                                 1);
	for (unsigned int i = 0; i < vector->size; ++i)
		((gsl_matrix *) data )->data[i] = vector->data[i * vector->stride];

}

gsl_vector api_variable :: get_vector()
{
	gsl_vector_view view;
	if (get_matrix()->size1 > get_matrix()->size2)
		view = gsl_matrix_column (get_matrix(), 0);
	else
		view = gsl_matrix_row (get_matrix(), 0);
	return view.vector;
}

void api_variable :: set_string(const char * string,
                                unsigned int size)
{
	api_variable :: _free();
	//Type
	type = API_STRING;
	if (size == 0)
		size = strlen(string);
	data = malloc(sizeof(char) * (size + 1) );
	memcpy(data, string, size * sizeof(char));
	((char *) data)[size] = '\0';
}
void api_variable :: set_name(const char * _name,
                              unsigned int size)
{
	if (size == 0)
		size = strlen(_name);
	if ( size >= API_STRING_SIZEMAX )
	{
		fprintf(stderr, "Warning : Variable name too long.\n");
		size = API_STRING_SIZEMAX - 1;
	}
	memcpy(name, _name, size);
	name[size] = '\0';

}
unsigned int api_variable :: sscanf_(const char * string,
                                     const char * format)
{

	char * cmt;
	unsigned int cmt_pos;
	unsigned int string_pos = 0;
	_free();
	initialize();

	//Taille de la chaine
	unsigned int size = strlen(string);
	//Suppression des blancs
	//
	//%
	//cerr << string + string_pos<< endl;
	while ( string[string_pos] == '\n' || string[string_pos] == '\r' || string[string_pos] == '\t' || string[string_pos] == ' ' )
		++ string_pos;
	if (string[string_pos] == '\0')
	{
		fprintf(stderr, "Error : No variable found in the string\n");
		return 0;
	}

	cmt_pos = string_pos;
	//% dfklklfkldfkl
	//%

	while ( string[string_pos] == '%' )
	{
		while ( string[string_pos] != '\n' && string[string_pos] != '\r' && string[string_pos] != '\0' )
			++ string_pos;
		if (string[string_pos] == '\0')
		{
			fprintf(stderr, "Error : No variable found in the string\n");
			return 0;
		}
		++ string_pos;
	}

	cmt = new char[string_pos - cmt_pos + 1];
	unsigned int j = 0;
	for ( unsigned int i = cmt_pos; i < string_pos; ++ i )
	{
		if ( string[i] != '%' )
		{
			cmt[j] = string[i];
			++ j;
		}
	}
	cmt[j] = '\0';
	if ( j == 0 )
	{
		delete[] cmt;
		cmt = NULL;
	}
	else
		cmt[j - 1] = '\0';
	//cerr << string + string_pos<< endl;
	//_____Name_____=_____data
	//Suppression des espaces(\t\r\n )
	while ( string[string_pos] == '\n' || string[string_pos] == '\r' || string[string_pos] == '\t' || string[string_pos] == ' ' || string[string_pos] == ';' )
		++ string_pos;
	if (string[string_pos] == '\0')
	{
		fprintf(stderr, "Error : No variable found in the string\n");
		delete[] cmt;
		return 0;
	}

	//Name_____=_____data
	//Récupération du nom de la variable
	{
		unsigned int curr;
		curr = string_pos;
		while ( string[string_pos] != '\n' && string[string_pos] != '\r' && string[string_pos] != '\t' && string[string_pos] != ' ' && string[string_pos] != '\0' && string[string_pos] != '=' && string[string_pos] != ';')
			++ string_pos;
		api_variable :: set_name(string + curr, string_pos - curr);
	}
	if ( string[string_pos] == ';' )
	{
		//~ cout << "Warning : Empty variable \"" << name << "\"!" << endl;
		while ( string[string_pos] == '\n' || string[string_pos] == '\r' || string[string_pos] == '\t' || string[string_pos] == ' ' || string[string_pos] == ';' )
		{
			if (string[string_pos] == '\0')
				return string_pos;
			++ string_pos;
		}
		return string_pos;
	}

	//_____=____data
	//Détection du =
	while ( string[string_pos] != '=')
	{
		if (string[string_pos] == '\0')
		{
			cout << name << endl;
			return string_pos;
		}
		else if ( string[string_pos] != '\n' && string[string_pos] != '\r' && string[string_pos] != '\t' && string[string_pos] != ' ')
		{
			if ( string[string_pos] != ';' )
				cout << name << " ";
			return string_pos;

		}
		++ string_pos;
	}
	++ string_pos;
	//____data
	//Suppression des espaces(\t\r\n )
	while ( string[string_pos] == '\n' || string[string_pos] == '\r' || string[string_pos] == '\t' || string[string_pos] == ' ' )
	{
		if (string[string_pos] == '\0')
		{
			delete[] cmt;
			return string_pos;
		}
		++ string_pos;
	}
	//data
	//Récupération des formats
	REF_FORMAT
	if (!format_ok)
	{
		delete[] cmt;
		return 0;
	}
	//Récupération des données
	{
		unsigned int size_format;
		double tmp;
		//Test si c'est un nombre
		if ( sscanf((string + string_pos), number_format, &tmp))
		{
			api_variable :: set_float(tmp);
			//Mise à jour de la position de la chaine
			for (; string[string_pos] == '-' || string[string_pos] == '.' || (string[string_pos] >= '0' && string[string_pos] <= '9') || string[string_pos] == 'e'; ++ string_pos);
		}
		//Teste si c'est une chaine
		else if ( ( size_format = api_is_string(string + string_pos, chain_sep) ) != 0 )
		{
			string_pos += size_format;
			unsigned int curr = string_pos;
			if ( size - string_pos  < size_format )
			{
				fprintf ( stderr, "Error : Missing %s in a string.\n", chain_sep);
				UNREF_FORMAT
				delete[] cmt;
				return string_pos ;
			}
			while ( memcmp ( string + string_pos, chain_sep, size_format) )
			{
				++ string_pos;
				if ( size - string_pos  < size_format )
				{
					fprintf ( stderr, "Error : Missing %s in a string.\n", chain_sep);
					UNREF_FORMAT
					delete[] cmt;
					return string_pos ;
				}
			}
			api_variable :: set_string(string + curr, string_pos - curr);
			string_pos += size_format;
		}
		//Teste si c'est une matrice
		else if ( ( size_format = api_is_matrix(string + string_pos, matrix_left) ) != 0 )
		{
			unsigned int delta;
			if ((delta = gsl_matrix_sscanf_(string + string_pos, matrix_format, ((gsl_matrix ** ) &data) )) == 0)
			{
				UNREF_FORMAT
				return string_pos;
			}
			type = API_MATRIX;
			string_pos += delta;
		}
		//Teste si c'est un tableau de vecteurs
		else if ( ( size_format = api_is_matrix(string + string_pos, vector_array_l_sep) ) != 0 )
		{
			unsigned int delta;
			data = (void*) new vector_array((unsigned int) 0, (unsigned int) 0);
			if ((delta = gsl_vector_array_sscanf(string + string_pos, vector_array_format, ((vector_array * ) data) )) == 0)
			{
				UNREF_FORMAT
				return string_pos;
			}
			type = API_VECTOR_ARRAY;
			string_pos += delta;
		}
		else
		{
			fprintf ( stderr, "Error : Unknown data type %s\n", name);
			UNREF_FORMAT
			delete[] cmt;
			return string_pos;
		}
	}

	UNREF_FORMAT
	bool display = true;
	while ( string[string_pos] == '\n' || string[string_pos] == '\r' || string[string_pos] == '\t' || string[string_pos] == ' ' || string[string_pos] == ';' )
	{
		if ( string[string_pos] == ';' )
			display = false;
		++ string_pos;
	}
	if ( display )
		fprintf_(	stdout, "\n{^}^\n\"^\n[^]^\t^\n^%lf" );

	comment = cmt;
	return string_pos;
}

unsigned int api_variable :: sprintf_(char * string,
                                      const char * format,
                                      unsigned int size_string)
{
	unsigned int string_pos = 0,
	             size_tmp;
	REF_FORMAT
	if (!format_ok)
		return 0;
	//Recopie du nom de la variable (toto = )
	{
		if ( ( size_tmp = strlen(name) ) < size_string - string_pos - 3 )
		{
			memcpy(string + string_pos, name, size_tmp);
			string_pos += size_tmp;
			string[string_pos] = ' ';
			string_pos ++;
			string[string_pos] = '=';
			string_pos ++;
			string[string_pos] = ' ';
			string_pos ++;

		}
		else
		{
			//Lib. mémoire
			UNREF_FORMAT

			fprintf ( stderr, "Error : size of buffer.\n");
			return string_pos;
		}
	}
	if ((data && type > 0) || (const_data && type < 0))
	{
		//Recopie des données
		{
			switch (type)
			{
			case (API_FLOAT):
			{
				char buffer[API_BUFFER_SIZEMAX];
				sprintf(buffer, number_format, get_float());
				if ( ( size_tmp = strlen(buffer) ) < size_string - string_pos )
				{
					memcpy(string + string_pos, name, size_tmp);
					string_pos += size_tmp;
					string[string_pos] = '\0';
				}
				else
				{
					//Lib. mémoire
					UNREF_FORMAT
					fprintf ( stderr, "Error : size of buffer.\n");
					return string_pos;
				}
			}
			break;
			case (API_STRING):
			{
				unsigned int size_tmp_bis = strlen(chain_sep);
				size_tmp = strlen(get_string_const());
				if ( 2 * size_tmp_bis + size_tmp <  size_string - string_pos )
				{
					memcpy(string + string_pos, chain_sep, size_tmp_bis);
					string_pos += size_tmp_bis;

					memcpy(string + string_pos, get_string(), size_tmp);
					string_pos += size_tmp;


					memcpy(string + string_pos, chain_sep, size_tmp_bis);
					string_pos += size_tmp_bis;

				}
				else
				{
					//Lib. mémoire
					UNREF_FORMAT
					fprintf ( stderr, "Error : size of buffer.\n");
					return string_pos;
				}

			}
			break;
			case (API_MATRIX):
			{
				string_pos += gsl_matrix_sprintf_(string + string_pos,
				                                  size_string - string_pos,
				                                  matrix_format,
				                                  get_matrix_const());
			}
			break;
			case (API_VECTOR_ARRAY):
			{
				vector_array_const tmp15 = get_vector_array_const();
				string_pos += gsl_vector_array_sprintf(string + string_pos,
				                                       size_string - string_pos,
				                                       vector_array_format,
				                                       &tmp15);
			}
			break;
			case (-API_STRING):
			{
				unsigned int size_tmp_bis = strlen(chain_sep);
				size_tmp = strlen(get_string_const());
				if ( 2 * size_tmp_bis + size_tmp <  size_string - string_pos )
				{
					memcpy(string + string_pos, chain_sep, size_tmp_bis);
					string_pos += size_tmp_bis;

					memcpy(string + string_pos, get_string(), size_tmp);
					string_pos += size_tmp;


					memcpy(string + string_pos, chain_sep, size_tmp_bis);
					string_pos += size_tmp_bis;

				}
				else
				{
					//Lib. mémoire
					UNREF_FORMAT
					fprintf ( stderr, "Error : size of buffer.\n");
					return string_pos;
				}

			}
			break;
			case (-API_MATRIX):
			{
				string_pos += gsl_matrix_sprintf_(string + string_pos,
				                                  size_string - string_pos,
				                                  matrix_format,
				                                  get_matrix_const());
			}
			break;
			case (-API_VECTOR_ARRAY):
			{
				vector_array_const tmp15 = get_vector_array_const();
				string_pos += gsl_vector_array_sprintf(string + string_pos,
				                                       size_string - string_pos,
				                                       vector_array_format,
				                                       &tmp15);
			}
			break;



			default:

				break;

			}
		}
	}
	//Lib. mémoire
	UNREF_FORMAT
	return string_pos;


}

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
unsigned int  api_variable :: fprintf_(FILE * file,
                                       const char * format)
{
	REF_FORMAT
	if (!format_ok)
		return 0;
	//Recopie du nom de la variable (toto = )
	{
		if ( !fprintf(file, "%s = ", name) )
		{
			UNREF_FORMAT
			return 0;
		}
	}

	if ((data && type > 0) || (const_data && type < 0))
	{
		//Recopie des données
		{
			switch (type)
			{
			case (API_FLOAT):
			{
				if ( !fprintf(file, number_format, get_float() ) )
				{
					UNREF_FORMAT
					return 0;
				}
			}
			break;
			case (API_STRING):
			{
				if (fprintf(file, "%s%s%s\n", chain_sep, get_string_const(), chain_sep) != 3)
				{
					UNREF_FORMAT
					return 0;
				}

			}
			break;
			case (API_MATRIX):
			{
				if (!gsl_matrix_fprintf_(file, matrix_format, get_matrix_const() ))
				{
					UNREF_FORMAT
					return 0;
				}
			}
			break;
			case (API_VECTOR_ARRAY):
			{
				vector_array_const tmp15 = get_vector_array_const();
				if (! gsl_vector_array_fprintf(file,
				                               vector_array_format,
				                               &tmp15) )
				{
					UNREF_FORMAT
					return 0;
				}
			}
			break;
			case (-API_STRING):
			{
				if (fprintf(file, "%s%s%s\n", chain_sep, get_string_const(), chain_sep) != 3)
				{
					UNREF_FORMAT
					return 0;
				}

			}
			break;
			case (-API_MATRIX):
			{
				if (!gsl_matrix_fprintf_(file, matrix_format, get_matrix_const() ))
				{
					UNREF_FORMAT
					return 0;
				}
			}
			break;
			case (-API_VECTOR_ARRAY):
			{
				vector_array_const tmp15 = get_vector_array_const();
				if (! gsl_vector_array_fprintf(file,
				                               vector_array_format,
				                               &tmp15) )
				{
					UNREF_FORMAT
					return 0;
				}
			}
			break;




			default:

				break;

			}
		}
		if ( !fprintf(file, "\r\n") )
		{
			UNREF_FORMAT
			return 0;
		}
	}

	UNREF_FORMAT
	return 1;
}

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
unsigned int api_variable :: fscanf_(FILE * file,
                                     const char * format)
{
	//Calcul de la taille du flux
	unsigned int cur = ftell(file);
	unsigned int size;

	fseek(file, SEEK_END, 0);
	size = ftell(file) - cur + 1;

	fseek(file, SEEK_SET, cur);

	char * buffer = (char *) malloc(sizeof(char) * (size + 1));
	size = fread(buffer, sizeof(char), size, file);
	buffer[size - 1] = '\0';
	size = sscanf_(buffer, format);
	free(buffer);

	fseek(file, SEEK_SET, cur + size);
	return (size > 0);
}

api_variable :: ~api_variable()
{
	api_variable :: _free();
	api_variable :: initialize();
}

void api_variable :: _free()
{
	switch (type)
	{
	case (API_FLOAT):
		if ( data )
			free( data );
		break;
	case (API_MATRIX):
		if ( data )
			gsl_matrix_free( (gsl_matrix *) data );
		break;
	case (API_STRING):
		if ( data )
			free( data );
		break;
	case (API_VECTOR_ARRAY):
		if ( data )
			delete ( (vector_array*) data );
		break;
	default:

		break;


	}
	if ( api_variable :: comment )
		delete[] api_variable :: comment;
}

void api_variable :: initialize()
{
	type = 0;
	data = NULL;
	comment = NULL;
	const_data = NULL;
	memset(name, 0, API_STRING_SIZEMAX);

}
/**@fn void api_variable :: set_matrix(const gsl_matrix * matrix);
 *
 */
void  api_variable :: set_matrix_const(const gsl_matrix * matrix)
{
	api_variable :: _free();
	api_variable :: initialize();
	const_data = (const void *) matrix;
	type = -API_MATRIX;

}
/** void api_variable :: set_string(const char * string);
 *
 */
void api_variable :: set_string_const(const char * string)
{
	api_variable :: _free();
	api_variable :: initialize();
	const_data = (const void *) string;
	type = -API_STRING;
}

/**@fn void api_variable :: set_vector_array(const vector_array & array);
 *
 */
void api_variable :: set_vector_array_const(const vector_array_const & array)
{
	api_variable :: _free();
	api_variable :: initialize();
	const_data = (const void *) &array;
	type = -API_VECTOR_ARRAY;
}

void api_variable :: set_cmt( const char * _comment )
{
	if ( comment )
		delete[] comment;
	if ( ! _comment )
		comment = NULL;
	if ( _comment )
	{
		unsigned int size = strlen( _comment );
		comment = new char[size + 1];
		comment[size] = '\0';
		memcpy( comment, _comment, sizeof(char) * size );
	}
}


