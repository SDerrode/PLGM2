#include "gsl_vector_io.hpp"

unsigned int gsl_vector_array_fscanf(FILE * file,
									 const char * format,
									 vector_array * array)
{
	gsl_matrix * mat;
	if (!gsl_matrix_fscanf_(file,
							format,
							&mat))
	{
		return 0;
	}
	//Construction du tableau
	array->setup(mat);
	//Lib mémoire
	gsl_matrix_free(mat);
	return 1;
}



									  
void  vector_array :: setup(unsigned int nb_vectors, unsigned int size_x)
{
	free();
	initialize();
	n = nb_vectors;
	vectors = new gsl_vector*[n];
	for (unsigned int i = 0; i < n; ++i)
	{
		vectors[i] = gsl_vector_calloc(size_x);
	}
	
}

void vector_array :: setup(const gsl_matrix * mat)
{
	free();
	initialize();
	n = mat->size1;
	vectors = new gsl_vector*[n];
	for (unsigned int i = 0; i < n; ++i)
	{
		vectors[i] = gsl_vector_alloc( mat->size2 );
		gsl_vector_const_view view = gsl_matrix_const_row (mat, i);
		gsl_vector_memcpy( 	vectors[i], 
							&( view.vector) );
	}
}

vector_array :: vector_array(unsigned int nb_vectors, unsigned int size_x)
{
	initialize();
	setup(nb_vectors, size_x);
}

vector_array :: vector_array(const gsl_matrix * mat)
{
	initialize();
	setup(mat);
}

vector_array :: ~vector_array()
{
	free();
	initialize();
}

void vector_array :: free()
{
	if (vectors)
	{
		for (unsigned int i = 0; i < n; ++i)
		{
			if (vectors[i])
				gsl_vector_free(vectors[i]);
		}
		delete[] vectors;
	}
}

void vector_array :: initialize()
{
	vectors = NULL;
	n = 0;
}

gsl_vector * vector_array :: operator[](unsigned int i)
{
	if (i >= n)
		return NULL;
	else
		return vectors[i];
}


vector_array :: vector_array(const gsl_vector * const * vect, unsigned int nb)
{
	initialize();
	setup(vect, nb);
}

vector_array :: vector_array(const vector_array & vect_array)
{
	initialize();
	setup(vect_array);
}

vector_array & vector_array :: operator=(const vector_array & vect_array)
{
	if ( &vect_array != this)
		setup(vect_array);
	return (*this);
}

void vector_array :: setup(const gsl_vector * const * vect, unsigned int nb)
{
	free();
	initialize();
	n = nb;
	vectors = new gsl_vector*[n];
	for (unsigned int i = 0; i < n; ++i)
	{
		vectors[i] = gsl_vector_alloc(vect[i]->size);
		gsl_vector_memcpy( vectors[i], vect[i] ) ;
	}
}
	
void vector_array :: setup(const vector_array & vect_array)
{
	free();
	initialize();
	setup(vect_array.vectors, vect_array.n);
}	
								  							 
unsigned int gsl_vector_array_sscanf(const char * string,
									 const char * format,
									 vector_array * array)
{
	gsl_matrix * mat;
	unsigned int delta;
	if ( (delta = gsl_matrix_sscanf_(string, format, &mat) ) == 0)
	{
		return 0;
	}
	//Construction du tableau
	array->setup(mat);
	//Lib mémoire
	gsl_matrix_free(mat);
	return delta;
}

unsigned int gsl_vector_array_sprintf(char * string,
									  unsigned int size_max,
									  const char * format,
									  const vector_array_const * array)
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
	size1 = array->n - 1;
	for ( unsigned int i = 0; i < size1; ++ i )
	{
		if ( ( lenght = gsl_matrix_row_sprintf(string + string_pos,
											   size_max - string_pos,
											   buffer,
											   col_sep,
											   n_format,
											   array->vectors[i]->data,
											   array->vectors[size1 - 1]->size) 
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
											array->vectors[size1]->data,
											array->vectors[size1]->size) 
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
		
unsigned int gsl_vector_array_fprintf(FILE * file,
									  const char * format,
									  const vector_array_const * array)
{
	unsigned int size;
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
	
	//Ecriture de "vector_array{\n"
	fprintf(file, "%s", l_matrix);
	
	size = array->n - 1;
	for (unsigned int i = 0; i < size; ++i)
	{
		for (unsigned int j = 0; j < array->vectors[size]->size - 1; ++j)
		{
			fprintf(file, 
					n_format, 
					array->vectors[i]->data[array->vectors[i]->stride * j]);
			fprintf(file, "%s", col_sep);
		}
		fprintf(file, 
				n_format, 
				array->vectors[i]->data[array->vectors[i]->stride * (array->vectors[size]->size - 1)]);
		fprintf(file, "%s", row_sep);
	}
	for (unsigned int j = 0; j < array->vectors[size]->size - 1; ++j)
	{
		fprintf(file, 
				n_format, 
				array->vectors[size]->data[array->vectors[size]->stride * j]);
		fprintf(file, "%s", col_sep);
	}
	fprintf(file, 
			n_format, 
			array->vectors[size]->data[array->vectors[size]->stride * (array->vectors[size]->size - 1)]);
	
	//Ecriture de "}"
	fprintf(file, "%s", r_matrix);
	MATRIX_FORMAT_UNREF
	return 1;
}
							 

unsigned int gsl_vector_array_sprintf(char * string,
									  unsigned int size_max,
									  const char * format,
									  const vector_array * array)
{
	vector_array_const array_bis(array->vectors, array->n);
	return gsl_vector_array_sprintf(string,
									size_max,
									format,
									&array_bis);
}


unsigned int gsl_vector_array_fprintf(FILE * file,
									  const char * format,
									  const vector_array * array)
{
	vector_array_const array_bis(array->vectors, array->n);
	return gsl_vector_array_fprintf(file,
									format,
									&array_bis);
	
}
			


void vector_array_const :: setup(const gsl_vector * const * vect, unsigned int nb)
{
	vectors = vect;
	n = nb;
}


vector_array_const :: vector_array_const(const gsl_vector * const * vect, unsigned int nb)
{
	setup(vect, nb);
}



