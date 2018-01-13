#include "lib_PKF.hpp"
#include "lib_tkalman_API.hpp"
#include "lib_tkalman_simulation.hpp"
#include <ctime>
int main( int argc, char ** argv )
{
	if ( argc > 1 )
	{
		if (	! strcmp( argv[1], "--help" ) ||
		        !  strcmp( argv[1], "-H" ) )
		{
			cout << "Help" << endl;
			cout << endl;
			cout << " Arg[1] : parameter file" << endl;
			cout << " Arg[2] : save file " << endl;
			cout << " Arg[3] : (opt) Nb of samples" << endl;
			cout << "Author: Valérian Némesin." << endl;
			return 0;

		}
	}
	if ( argc < 3 )
	{
		cout << "Missing Arugments!" << endl;
		return 1;
	}
	api_parameters toto;
	toto.load ( argv[1] );

	tkalman :: api :: parameters params;

	if ( params.setup( toto ) )
		return 1;

	//Nombre d'échantillons

	unsigned int nb_samples = 0;
	if ( argc > 3 )
	{
		if ( sscanf( argv[3], "%ud", &nb_samples ) == 0)
			nb_samples = 0;

	}

	if ( !nb_samples )
	{
		if ( api_get_positive_integer(	toto,
		                                "nb_samples",
		                                &nb_samples,
		                                &cout ) )
			return 1;
	}

	gsl_rng * r = gsl_rng_alloc (gsl_rng_taus);
	gsl_rng_set (r, time(NULL));

	tkalman_simualtion simu( 	params.t_0(),
	                            params.q_0(),
	                            params.f(),
	                            params.q(),
	                            r );
	gsl_vector ** t_data = 0;

	tkalman_expectation_ref( t_data,
	                         nb_samples + 1,
	                         params.size_t(),
	                         params.size_t()) ;

	simu.simulate_tkalman_data(	t_data,
	                            nb_samples );

	signal_splitting signal( 	t_data,
	                            nb_samples,
	                            params.size_x() );

	//Sauvegarde
	api_parameters save;
	{
		api_variable var1;
		vector_array_const	v_const(	signal.x(),
		                                nb_samples + 1 );
		var1.set_vector_array_const( v_const );
		var1.set_name("x");
		save.add_variable( var1 );
	}
	{
		api_variable var2;
		vector_array_const	v_const(	signal.y(),
		                                nb_samples );
		var2.set_vector_array_const( v_const );
		var2.set_name("y");
		save.add_variable( var2 );
	}

	save.save( argv[2], "[^];^\"^[^];^\t^\n^%lf"  );

	gsl_rng_free( r );
	tkalman_expectation_unref( t_data, nb_samples + 1 );

	return 0;
}
