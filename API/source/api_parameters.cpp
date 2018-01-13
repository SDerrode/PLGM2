#include "api_parameters.hpp"
#include <iostream>
using namespace std;
int api_get_namespace( 	const char * variable,
						char * name )
{
	bool p = false;
	unsigned int i;
	for ( i = 0; variable[i] != '\0'; ++ i )
	{
		if ( variable[i] == ':' )
		{
			if ( p )
			{
				memcpy( name, variable, (i - 1) * sizeof(char) );
				name[i - 1] = '\0';
				return 1;
			}
			else
				p = true;
		}
		else
			p = false;
	}
	return 0;
}

api_parameters :: api_parameters(unsigned int nb_var_max)
{
	initialize();
	setup(nb_var_max);
}

void api_parameters :: setup(unsigned int nb_var_max)
{
	free();
	initialize();
	set_max_nb_variables(nb_var_max);
}

int api_parameters :: add_variable(const char * name)
{
	unsigned int i = 0, j = _nb_var, k;
	if (_nb_var == _nb_var_max)
		return -1;
	while (j - i > 1)
	{
		k = (i + j) / 2;
		if (strcmp(name, variables[k]->get_name()) > 0)
			i = k;
		else
			j = k;
	}
	if (strcmp(name, variables[i]->get_name()) > 0)
	{
		k = j;
	}
	else if (strcmp(name, variables[i]->get_name()) < 0)
	{
		k = i;
	}
	else
	{
		return 1;
	}

	for (j = _nb_var; j > k; --j)
	{
		variables[j] = variables[j - 1];
	}
	variables[k] = new api_variable(name);
	_nb_var ++;
	return 0;
}

int api_parameters :: add_variable(const api_variable & variable)
{
	unsigned int i = 0, j = _nb_var, k;
	if (_nb_var == _nb_var_max)
		return -1;
	if (_nb_var == 0)
	{
		variables[0] = new api_variable(variable);
		_nb_var ++;
		
		return 0;
	}
	while (j - i > 1)
	{

		k = (i + j) / 2;
		if (strcmp(variable.get_name(), variables[k]->get_name()) > 0)
			i = k;
		else
			j = k;
	}
	if (strcmp(variable.get_name(), variables[i]->get_name()) > 0)
	{
		k = j;
		if (j < _nb_var)
		{
			if (strcmp(variable.get_name(), variables[j]->get_name()) == 0)
			{
				if ( variable.get_type() != 0 || ( * (variables[j]) ).get_type() == 0 )
				{
					( * (variables[j]) ) = variable;
				}
				return 0;
			
			}
		}

	}
	else if (strcmp(variable.get_name(), variables[i]->get_name()) < 0)
	{
		k = i;
	}
	else
	{

		( * (variables[i]) ) = variable;
		return 0;
	}

	for (j = _nb_var; j > k; --j)
	{
		variables[j] = variables[j - 1];
	}
	variables[k] = new api_variable(variable);
	_nb_var ++;
	return 0;
}

api_parameters :: ~api_parameters()
{
	free();
	initialize();
}

api_variable * api_parameters :: operator[](const char * name)
{
	unsigned int i = 0, j = _nb_var - 1, k;
	if ( variables == NULL || _nb_var == 0)
		return NULL;
	if (j == 0)
		return NULL;
	while (j - i > 1)
	{

		k = (i + j + 1) / 2;
		if (strcmp(name, variables[k]->get_name()) > 0)
			i = k;
		else 
			j = k;
	}
	if (strcmp(name, variables[i]->get_name()) == 0)
		return variables[i];
	else if (strcmp(name, variables[j]->get_name()) == 0)
		return variables[j];
	return NULL;
}

int api_parameters :: delete_variable(const char * name)
{
	unsigned int i = 0, j = _nb_var, k;
	while (j - i > 1)
	{
		k = (i + j) / 2;
		if (strcmp(name, variables[k]->get_name()) > 0)
			i = k;
		else 
			j = k;
	}

	
	if (strcmp(name, variables[i]->get_name()) != 0)
	{
		if (strcmp(name, variables[j]->get_name()) != 0)
		{
			return 1;
		}
		else
		{
			i = j;
		}
	}
	delete variables[i];
	_nb_var --;
	for (j = i; j < _nb_var; ++j)
	{
		variables[j] = variables[j + 1];
	}

	return 0;
}

int api_parameters :: save(const char * filename, const char * format)
{
	FILE * file = fopen(filename, "w");
	if (!file)
		return -1;
	for (unsigned int i = 0; i < _nb_var; ++i)
	{
		variables[i]->fprintf_(file, format);
	}
	fclose(file);
	return 0;
}

int api_parameters :: load(const char * filename, const char * format)
{
	FILE * file = fopen(filename, "r");
	if (!file)
		return -1;
	//Calcul de la taille du fichier + recopie en mémoire
	char * buffer;
	unsigned int string_pos = 0;
	unsigned int string_size;
	{
		unsigned int size = 0;
		bool stop = false;
		int c;
		while ((c = fgetc(file)) != EOF)
		{
			if (c == '#')
				stop = true;
			else if (c == '\n' or c == '\r')
				stop = false;
			if (! stop)
				size ++;
		}
		fseek(file, SEEK_SET, 0);
		buffer = new char[size + 1];
		stop = false;
		size = 0;
		while ((c = fgetc(file)) != EOF)
		{
			if (c == '#')
				stop = true;
			else if (c == '\n' or c == '\r')
				stop = false;
			if (! stop)
			{
				buffer[size] = c;
				size ++;
			}
		}
		buffer[size] = '\0';
		string_size = size;
	}

	while (string_pos < string_size)
	{
		unsigned int delta;
		api_variable tmp;
		if ( ( delta = tmp.sscanf_(buffer + string_pos, format) ) == 0 )
		{
			break;
		}
		string_pos += delta;
		add_variable(tmp);

	}
	delete[] buffer;

	fclose(file);
	return 0;
}

void api_parameters :: set_max_nb_variables(unsigned int nb_var_max)
{
	if (_nb_var > nb_var_max)
	{
		setup(nb_var_max);
	}
	else
	{
		api_variable ** tmp = new api_variable*[nb_var_max];
		_nb_var_max = nb_var_max;
		for (unsigned int i = 0; i < _nb_var; ++i)
		{
			tmp[i] = variables[i];
		}
		delete[] variables;
		variables = tmp;
	}
}

void api_parameters :: free()
{
	for (unsigned int i = 0; i < _nb_var; ++i)
	{
		delete variables[i];
	}
	delete[] variables;
}

void api_parameters :: initialize()
{
	variables = NULL;
	_nb_var = 0;
	_nb_var_max = 0;
	
	
}

int api_parameters :: search_variables_with_prefix(	const char * prefix, 
													api_variable ** variables_out,
													unsigned int * nb_variables_out,
													unsigned int nb_variables_out_max )
{
	unsigned int size;
	( *nb_variables_out ) = 0;
	if ( prefix == NULL )
	{
		return 35;
	}
	size = strlen( prefix );
	for (unsigned int i = 0; i < _nb_var; ++ i)
	{
		if ( strlen( variables[i]->get_name() ) >= size )
		{
			if ( ! memcmp( prefix, variables[i]->get_name(), size * sizeof(char) ) && strcmp("NAME",variables[i]->get_name() + size ) ) 
			{
				if ((*nb_variables_out) >= nb_variables_out_max )
					return 1;
				variables_out[*nb_variables_out] = variables[i];
				(*nb_variables_out) ++;
			}
		}
	}
	return 0;
}

int api_parameters :: detect_namespaces( 	char *** namespaces,
											unsigned int * nb_namespaces )
{
	unsigned int n_var;
	unsigned int i;
	char cur_namespace[API_STRING_SIZEMAX],
		 pre_namespace[API_STRING_SIZEMAX];
	*nb_namespaces = 0;
	
	//Détection du premier espace de nom
	for ( n_var = 0; n_var < _nb_var; ++ n_var )
	{
		if ( api_get_namespace( variables[n_var]->get_name(), 
								pre_namespace ) )
		{
			++ (*nb_namespaces);
			break;
		}
	}
	
	for (; n_var < _nb_var; ++ n_var )
	{
		if ( api_get_namespace( variables[n_var]->get_name(), 
								cur_namespace ) )
		{
			if ( strcmp ( cur_namespace, pre_namespace ) )
			{
				strcpy( pre_namespace, cur_namespace );
				++ (*nb_namespaces);
			}
			
		}
		
	}
	
	(*namespaces) = new char*[*nb_namespaces];
	for ( i = 0; i < (*nb_namespaces); ++ i )
	{
		(*namespaces)[i] = new char[API_STRING_SIZEMAX];
	}
	
	i = 0;
	for ( n_var = 0; i < (*nb_namespaces); ++ n_var )
	{
		if ( api_get_namespace( variables[n_var]->get_name(), 
								(*namespaces)[i] ) )
		{
			if ( i == 0 )
				++ i;
			else if ( strcmp ( (*namespaces)[i], (*namespaces)[i - 1]) )
			{
				++ i;
			}
		}
	}
	
	return 0;
}
