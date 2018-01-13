#include "api_functions.hpp"
#define API_ERROR_UNDEF(var_name, stream) (*( stream )) << "Error: " << ( var_name ) << " is undefined!" << endl;
#define API_ERROR_NOT_INTEGER(var_name, stream) (*( stream )) << "Warning: " << ( var_name ) << " is not an integer!" << endl;
#define API_ERROR_NOT_POSITIVE_INTEGER(var_name, stream) (*( stream )) << "Warning: " << ( var_name ) << " is not a positive integer!" << endl;
#define API_ERROR_NOT_DOUBLE(var_name, stream) (*( stream )) << "Error: " << ( var_name ) << " is not a number!" << endl;
#define API_ERROR_NOT_STRING(var_name, stream) (*( stream )) << "Error: " << ( var_name ) << " is not a string!" << endl;
#define API_ERROR_NOT_VECTOR(var_name, stream) (*( stream )) << "Error: " << ( var_name ) << " is not a vector!" << endl;
#define API_ERROR_NOT_MATRIX(var_name, stream) (*( stream )) << "Error: " << ( var_name ) << " is not a matrix!" << endl;
#define API_ERROR_NOT_POSITIVE_MATRIX(var_name, stream) (*( stream )) << "Error: " << ( var_name ) << " is not a positive matrix!" << endl;

int api_get_integer( api_parameters & params,
					 const char * name,
					 int * number,
					 ostream * out )
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_float() )
	{
		if ( out )
			API_ERROR_NOT_DOUBLE(name, out);
		return 1;
	}
	double v = var->get_float();
	(*number) = v;
	if ( v != ( *number ) )
	{
		if ( out )
			API_ERROR_NOT_INTEGER(name, out);
		return -1;
	}
	return 0;
}

int api_get_positive_integer( api_parameters & params,
							  const char * name,
							  unsigned int * number,
							  ostream * out )
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_float() )
	{
		if ( out )
			API_ERROR_NOT_DOUBLE(name, out);
		return 1;
	}

	double v = var->get_float();
	(*number) = v;
	if ( v != ( *number ) )
	{
		if ( out )
			API_ERROR_NOT_INTEGER(name, out);
		return -1;
	}
	else if ( v < 0 )
	{
		if ( out )
			API_ERROR_NOT_POSITIVE_INTEGER(name, out);
		return -1;
	}
	return 0;
}

int api_get_float( 	api_parameters & params,
					const char * name,
					float * number,
					ostream * out )
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_float() )
	{
		if ( out )
			API_ERROR_NOT_DOUBLE(name, out);
		return 1;
	}
	(*number) = var->get_float();
	return 0;
	
}

int api_get_double(	api_parameters & params,
					const char * name,
					double * number,
					ostream * out )
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_float() )
	{
		if ( out )
			API_ERROR_NOT_DOUBLE(name, out);
		return 1;
	}
	(*number) = var->get_float();
	return 0;
	
}

int api_get_vector(	api_parameters & params,
					const char * name,
					gsl_vector * vect,
					ostream * out)
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_vector() )
	{
		if ( out )
			API_ERROR_NOT_VECTOR(name, out);
		return 1;
	}
	(*vect) = var->get_vector();
	return 0;
}

int api_get_string(	api_parameters & params,
					const char * name,
					string * str,
					ostream * out)
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_string() )
	{
		if ( out )
			API_ERROR_NOT_STRING(name, out);
		return 1;
	}
	
	(*str) = var->get_string();
	return 0;
}

int api_get_matrix(	api_parameters & params,
					const char * name,
					gsl_matrix * matrix,
					ostream * out )
{
	api_variable * var;
	var = params[name];
	if ( var == NULL )
	{
		if ( out )
			API_ERROR_UNDEF(name, out);
		return 1;
	}
	if ( ! var->is_matrix() )
	{
		if ( out )
			API_ERROR_NOT_MATRIX(name, out);
		return 1;
	}
	(*matrix) = (* var->get_matrix());
	return 0;
}


