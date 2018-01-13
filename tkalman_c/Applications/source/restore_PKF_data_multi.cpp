#include "lib_PKF.hpp"
#include "lib_tkalman_API.hpp"
#include <sstream>
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
			cout << " Arg[2] : signal file" << endl;
			cout << " Arg[3] : save file " << endl;
			cout << "Author: Valérian Némesin." << endl;
			return 0;
			
		} 
	}
	if ( argc < 4 )
	{
		cout << "Missing Arugments!" << endl;
		return 1;
	}
	api_parameters data;
	
	//Chargement du signal
	data.load ( argv[2] );
	unsigned int nb_signals;
	if ( api_get_positive_integer( data, "nb_signals", &nb_signals, &cout ) )
		return 1;
	if ( !nb_signals )
	{
		cout << "!nb_signals" << endl;
		return 1;
	}
	
	tkalman :: api :: signal * signals = new tkalman :: api :: signal[nb_signals];
	for (unsigned int i = 0; i < nb_signals; ++ i )
	{
		if ( signals[i].setup( data, i + 1 ) )
			return 1;
	}
	
	//Conversion
	unsigned int * nb_observations = new unsigned int[nb_signals];
	gsl_vector *** observations = new gsl_vector **[nb_signals];

	for (unsigned int i = 0; i < nb_signals; ++ i )
	{
		nb_observations[i] = signals[i].nb_samples_y();
		observations[i] = signals[i].observations();
	}
	



	
	//Chargement des paramètres
	data.load( argv[1] );
	tkalman :: api :: EM :: parameters params;
	
	if ( params.setup( data ) )
	{
		return 1;
	}	
		
	tkalman :: api :: parameters initial_parameters;
	if ( initial_parameters.setup( data ) )
	{
		return 1;
	}

	tkalman :: EM :: parameters em_params(	params.f_0(),
											params.sqrt_q_i(),
											params.p(),
											params.size_x(),
											params.nb_f_blocks(),
											params.nb_q_blocks(),
											params.f_block_sizes(),
											params.q_block_sizes(),
											params.f_block_row_ids(),
											params.q_block_row_ids(),
											params.f_block_hypotheses(),
											params.q_block_hypotheses(),
											params.f_other_data(),
											params.q_other_data(),
											params.first_state_estimation() );
	

	
	tkalman :: parameters filt_params(	params.t_0(),
										params.q_0(),
										params.f(),
										params.q(),
										params.size_x() );
	
	
	tkalman :: EM :: estimator algo;
	if ( algo.setup( &em_params ) )
		return 1;
	gsl_vector * likelihood = gsl_vector_alloc( params.nb_iterations() + 1 );
	
	
	
	tkalman :: moments * m = new tkalman :: moments[nb_signals];
	
	
	//Algo EM
	algo.estimate( 	m,
					filt_params,
					observations, 
					nb_observations,
					nb_signals,
					params.nb_iterations(),
					likelihood->data );



	
	//Système équivalents
	gsl_matrix * mat = gsl_matrix_alloc( 	params.size_t(), 
											params.size_t() );
	bool ident = false;
	switch ( params.equivalence_type() )
	{
		//Correlation
		case(1):
		{
			gsl_matrix_const_view 	t1 = gsl_matrix_const_submatrix( params.sqrt_q_i(), 0, 0, params.size_x(), params.size_x() );
			gsl_matrix * DarkTemplar = gsl_matrix_calloc( params.size_x(), params.size_y() );
			equivalence :: Q_decorrelation obj( & t1.matrix, DarkTemplar );
			obj.compute_m( mat, filt_params.get_sqrt_q(), algo.get_filter().q2_xy() );
			gsl_matrix_free( DarkTemplar );
		}
		break;
		//Condition sur les matrices d'état
		case(2):
		{
			gsl_matrix_const_view 	t1 = gsl_matrix_const_submatrix( params.f_0(), 0, 0, params.size_x(), params.size_x() ),
									t2 = gsl_matrix_const_submatrix( params.f_0(), 0, params.size_x(), params.size_x(), params.size_y() );
			
			equivalence :: f_state obj( 
				& t1.matrix,
				& t2.matrix);
			obj.compute_m( mat, filt_params.get_f() );
		}
		break;
		//Condition sur les matrices d'observations
		case(3):
		{
			gsl_matrix_const_view 	t1 = gsl_matrix_const_submatrix( params.f_0(), params.size_x(), 0, params.size_y(), params.size_x() ),
									t2 = gsl_matrix_const_submatrix( params.f_0(), params.size_x(), params.size_x(), params.size_y(), params.size_y() );
			
			equivalence :: restoration obj( 
				& t1.matrix,
				& t2.matrix);
			obj.compute_m( mat, filt_params.get_f() );
		}
		break;
		default:
			ident = true;
			gsl_matrix_set_identity(mat);
		break;
	}
	if ( !ident )
	{
		for ( unsigned int i = 0; i < nb_signals; ++ i)
		{
			//Correction des momentsd
			m[i].transformation(mat, observations[i]);
			//Correction des états 
			filt_params.transformation(mat);
		}
	}
	

	double EQM_p = 0;
	unsigned int n = 0;
	for ( unsigned int i = 0; i < nb_signals; ++ i)
	{
		n += nb_observations[i];
		for (unsigned int j = 0; j < nb_observations[i]; ++ j )
		{
			for (unsigned int k = 0; k < m[i].size_x(); ++ k )
			{
				double d = m[i].all_x_p()[j]->data[k] - observations[i][j]->data[k];
				EQM_p +=  d * d;
			}
		}
	}
	EQM_p /= n;
	
			
	//Sauvegarde
	api_parameters save(6);
	gsl_matrix_free(mat);		
	//Estimation
	{
		stringstream oss;
		api_variable var;
		
		oss << "t_0_EM";
		var.set_vector( filt_params.get_t_0() );
		var.set_name( oss.str().c_str() );
		oss.str("");
		save.add_variable( var );
		
		oss << "F_EM";
		var.set_matrix( filt_params.get_f() );
		var.set_name( oss.str().c_str() );
		oss.str("");
		save.add_variable( var );
		
		oss << "Q_EM";
		var.set_matrix( filt_params.q() );
		var.set_name( oss.str().c_str() );
		oss.str("");
		save.add_variable( var );
		
		oss << "Q_0_EM";
		var.set_matrix( filt_params.q_0() );
		var.set_name( oss.str().c_str() );
		oss.str("");
		save.add_variable( var );

	}
	
	//Vraisemblance
	{
		api_variable var;
		var.set_vector(likelihood);
		var.set_name("likelihood");
		save.add_variable(var);
	}
	
	{
		api_variable var( "EQMp", API_FLOAT,&EQM_p);
		save.add_variable( var );
	}
	
	save.save( argv[3], "[^];^\"^[^];^\t^\n^%lf" );
	gsl_vector_free( likelihood );
	delete[] m;
	return 0;
}
