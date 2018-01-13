#include "tkalman_api_signal.hpp"
#include <sstream>
using namespace std;
using namespace tkalman;
using namespace api;

signal :: signal ( void )
{
	initialize();
}

int signal :: setup( api_parameters & params, unsigned int i )
{
	free();
	initialize();
	
	stringstream oss1, oss2;
	oss1 << "x";
	oss2 << "y";
	if ( i )
	{
		oss1  << "(" << i << ")";
		oss2  << "(" << i << ")";
	}
	gsl_matrix tmp_x, tmp_y;
	int qqq = 0;
	if ( api_get_matrix( params, oss1.str().c_str(), &tmp_x, &cout ) )
		qqq = 2;
	if ( api_get_matrix( params, oss2.str().c_str(), &tmp_y, &cout ) )
		qqq = 1;
	if ( qqq == 1)
		return 1;

	//Nombre d'échantillons
	_nb_samples = tmp_y.size1;

	//Chargement des y
	y = gsl_matrix_alloc( tmp_y.size1, tmp_y.size2 );
	gsl_matrix_memcpy( y, &tmp_y );
	p_y = new gsl_vector[_nb_samples];
	pp_y = new gsl_vector*[_nb_samples];
	//Vues sur les lignes
	for ( unsigned int i = 0; i < _nb_samples; ++ i )
	{
		gsl_vector_view view = gsl_matrix_row ( y, i );
		p_y[i] = view.vector;
		pp_y[i] = p_y + i;
	}
	
	
	
	
	
	//Chargement des x
	if ( qqq != 2 )
	{
		//Nombre d'échantillon de x
		_nb_samples_x = tmp_x.size1;
		
		x = gsl_matrix_alloc( tmp_x.size1, tmp_x.size2 );
		gsl_matrix_memcpy( x, &tmp_x );
		
		p_x = new gsl_vector[_nb_samples_x];
		pp_x = new gsl_vector*[_nb_samples_x];
		//Vues sur les lignes
		for ( unsigned int i = 0; i < _nb_samples; ++ i )
		{
			gsl_vector_view view = gsl_matrix_row ( x, i );
			p_x[i] = view.vector;
			pp_x[i] = p_x + i;
		}
	}

	return 0;

}
signal :: ~signal ( void )
{
	free();
	initialize();
}

void signal :: initialize()
{
	x = 0;
	y = 0;
	_nb_samples = 0;
	_nb_samples_x = 0;
	p_x = 0;
	p_y = 0;
	pp_x = 0;
	pp_y = 0;
}

void signal :: free()
{
	if ( x )
		gsl_matrix_free(x);
	if ( y )
		gsl_matrix_free(y);
	if ( p_x )
		delete[] p_x;
	if ( p_y )
		delete[] p_y;
	if ( pp_x )
		delete[] pp_x;
	if ( pp_y )
		delete[] pp_y;
}

