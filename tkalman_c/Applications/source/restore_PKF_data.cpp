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
			cout << " Arg[4] : -scm - save covariance matrix " << endl;
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
	tkalman :: api :: signal signal;
	
	if ( signal.setup( data, 0 ) )
		return 1;
	
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
	tkalman :: moments * m = new tkalman :: moments();



	//Algo EM
	algo.estimate( 	*m,
					filt_params,
					signal.observations(), 
					signal.nb_samples_y(),
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
		//Correction des momentsd
		m->transformation(mat, signal.observations());
		//Correction des états 
		filt_params.transformation(mat);
	}
	
	gsl_matrix_free(mat);					

	bool save_cvm = false;
	if ( argc >= 5 )
	{
		if ( !strcmp( "-scm", argv[4] ) )
		{
			save_cvm = true;
		}
	}
	
	unsigned int nb_var = 8;
	if ( save_cvm )
		nb_var += 3 * signal.nb_samples_y() + 2;
	//Sauvegarde
	api_parameters save( nb_var );

	//Moments
	{
		gsl_vector_view v_p, v_f, v_s;
		gsl_matrix * mat_x_p = gsl_matrix_alloc( signal.nb_samples_y() + 1, params.size_x() );
		gsl_matrix * mat_x_f = gsl_matrix_alloc( signal.nb_samples_y(), params.size_x() );
		gsl_matrix * mat_x_s = gsl_matrix_alloc( signal.nb_samples_y() + 1, params.size_x() );
		
		
		stringstream oss;
		api_variable var;

		for ( 	unsigned int i = 0; 
				i < signal.nb_samples_y(); 
				++ i )
		{
			const gsl_vector * v_tmp;
			
			v_tmp = m->get_x_p( i );
			v_p = gsl_matrix_row( mat_x_p, i);
			gsl_vector_memcpy( &v_p.vector, v_tmp );
			
			v_tmp = m->get_x_f( i );
			v_f = gsl_matrix_row( mat_x_f, i);
			gsl_vector_memcpy( &v_f.vector, v_tmp );
			
			v_tmp = m->get_x_s( i );
			v_s = gsl_matrix_row( mat_x_s, i);
			gsl_vector_memcpy( &v_s.vector, v_tmp );
		}
		
		// x_p
		const gsl_vector * v_tmp = m->get_x_p( signal.nb_samples_y() );
		v_p = gsl_matrix_row( mat_x_p, signal.nb_samples_y());
		gsl_vector_memcpy( &v_p.vector, v_tmp );
		
		v_tmp = m->get_x_s( signal.nb_samples_y() );
		v_s = gsl_matrix_row( mat_x_s, signal.nb_samples_y() );
		gsl_vector_memcpy( &v_s.vector, v_tmp );
		
		var.set_name("x_p");
		var.set_matrix( mat_x_p );
		save.add_variable( var );
		
		var.set_name("x_f");
		var.set_matrix( mat_x_f );
		save.add_variable( var );
		
		var.set_name("x_s");
		var.set_matrix( mat_x_s );
		save.add_variable( var );
		
		gsl_matrix_free(mat_x_p);
		gsl_matrix_free(mat_x_f);
		gsl_matrix_free(mat_x_s);
	}
	
	if ( save_cvm )
	{
		gsl_matrix * tmp = gsl_matrix_alloc( params.size_x(), params.size_x() );
		stringstream oss;
		api_variable var;

		for ( 	unsigned int i = 0; 
				i < signal.nb_samples_y(); 
				++ i )
		{
			// p_p
			oss << "p_p(" << i + 1 << ")";
			m->get_p_p( tmp, i );
			var.set_matrix( tmp );
			var.set_name( oss.str().c_str() );
			oss.str("");
			save.add_variable( var );
			
			// p_f
			oss << "p_f(" << i + 1 << ")";
			m->get_p_f( tmp, i );
			var.set_matrix( tmp );
			var.set_name( oss.str().c_str() );
			oss.str("");
			save.add_variable( var );
			
			// p_s
			oss << "p_s(" << i + 1 << ")";
			m->get_p_f( tmp, i );
			var.set_matrix( tmp );
			var.set_name( oss.str().c_str() );
			oss.str("");
			save.add_variable( var );
		}
		
		// p_s
		oss << "p_s(" << signal.nb_samples_y() + 1 << ")";
		m->get_p_s( tmp, signal.nb_samples_y() );
		var.set_matrix( tmp );
		var.set_name( oss.str().c_str() );
		oss.str("");
		save.add_variable( var );
		
		//P_p
		oss << "p_p(" << signal.nb_samples_y() + 1 << ")";
		m->get_p_p( tmp, signal.nb_samples_y() );
		var.set_matrix( tmp );
		var.set_name( oss.str().c_str() );
		oss.str("");
		save.add_variable( var );
		gsl_matrix_free(tmp);
	}
	
	
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
	
	
	save.save( argv[3], "[^];^\"^[^];^\t^\n^%lf" );
	gsl_vector_free( likelihood );
	delete m;
	return 0;
}
