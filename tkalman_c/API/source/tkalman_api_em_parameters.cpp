#include "tkalman_api_em_parameters.hpp"
#include "lib_PKF.hpp"
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <cmath>
#include <gsl/gsl_eigen.h>
#include <sstream>
using namespace std;
namespace tkalman
{
namespace api
{
namespace EM
{
parameters :: parameters( void )
	: tkalman :: api :: parameters()
{
	initialize();
}

int parameters :: load_F_data(	api_parameters & params )
{
	gsl_vector block_sets;
	_p = gsl_matrix_calloc (_size_t, _size_t);
	unsigned int * _ids = NULL;

	if ( api_get_vector( 	params,
	                        "F::block::sets",
	                        &block_sets ) )
	{
		string str;
		if ( api_get_string(	params,
		                        "F::block::sets",
		                        &str ) )
			cout << "Warning : F::block::sets = ones(" << _size_t << ",1)" << endl;
		else if ( str != "default" )
			cout << "Warning : F::block::sets = ones(" << _size_t << ",1)" << endl;

		_nb_f_blocks = 1;
		//Allocation mémoire
		_f_block_sizes = new unsigned int[_nb_f_blocks];
		_f_block_sizes[0] = _size_t;

		_f_block_hypotheses = new unsigned int [_nb_f_blocks];
		_f_block_hypotheses[0] = 3;

		_f_block_row_ids = new unsigned int*[_nb_f_blocks];
		_f_block_row_ids[0] = new unsigned int[_size_t];
		for ( unsigned int i = 0; i < _size_t; ++ i )
			_f_block_row_ids[0][i] = i;
		_f_other_data = new void*[_nb_f_blocks];
		_f_other_data[0] = 0;
		_ids = new unsigned int[1];
		_ids[0] = 1;

	}
	else if ( block_sets.size < _size_t )
	{
		cout << "Warning : Wrong dimensions for F::block::sets" << endl;
		cout << "Warning : F::block::sets = ones(" << _size_t << ",1)" << endl;
		_nb_f_blocks = 1;
		//Allocation mémoire
		_f_block_sizes = new unsigned int[_nb_f_blocks];
		_f_block_sizes[0] = _size_t;

		_f_block_hypotheses = new unsigned int [_nb_f_blocks];
		_f_block_hypotheses[0] = 3;

		_f_block_row_ids = new unsigned int*[_nb_f_blocks];
		_f_block_row_ids[0] = new unsigned int[_size_t];
		for ( unsigned int i = 0; i < _size_t; ++ i )
			_f_block_row_ids[0][i] = i;
		_f_other_data = new void*[_nb_f_blocks];
		_f_other_data[0] = 0;
		_ids = new unsigned int[1];
		_ids[0] = 1;
	}
	else
	{
		//Nombre de block
		_nb_f_blocks = 0;
		_ids = new unsigned int[ _size_t ];

		for ( unsigned int i = 0; i < _size_t ; ++ i )
		{
			bool exist = false;
			for ( unsigned int j = 0; j < _nb_f_blocks; ++ j )
			{
				if ( _ids[j] == block_sets.data[i * block_sets.stride] )
					exist = true;
			}
			if ( ! exist )
			{
				_ids[_nb_f_blocks] = block_sets.data[i * block_sets.stride];
				_nb_f_blocks ++;
			}

		}

		//Allocation mémoire
		_f_block_sizes = new unsigned int[_nb_f_blocks];
		memset
		(	_f_block_sizes,
		    0,
		    sizeof (unsigned int) * _nb_f_blocks );
		_f_block_hypotheses = new unsigned int [_nb_f_blocks];
		memset( _f_block_hypotheses,
		        0,
		        sizeof (unsigned int) * _nb_f_blocks );

		_f_block_row_ids = new unsigned int*[_nb_f_blocks];
		_f_other_data = new void*[_nb_f_blocks];

		memset(	_f_other_data,
		        0,
		        _nb_f_blocks * sizeof(void*) );
		//Taille des différents blocks
		for ( unsigned int i = 0; i < _nb_f_blocks ; ++ i )
		{
			for ( unsigned int j = 0; j < _size_t; ++ j )
			{
				if ( _ids[i] == block_sets.data[j * block_sets.stride] )
					++ _f_block_sizes[i];
			}
		}

		//Lignes des différents block
		for ( unsigned int i = 0; i < _nb_f_blocks ; ++ i )
		{
			unsigned int n = 0;
			_f_block_row_ids[i] = new unsigned int[_f_block_sizes[i]];
			for ( unsigned int j = 0; j < _size_t; ++ j )
			{
				if ( _ids[i] == block_sets.data[j * block_sets.stride] )
				{
					_f_block_row_ids[i][n] = j;
					++n;
				}
			}
		}

		//Lecture des hypothèses des différents blocks
		for ( unsigned int i = 0; i < _nb_f_blocks ; ++ i )
		{

			stringstream oss;
			oss << "F::block(" << _ids[i] << ")::hypothesis";



			if ( api_get_positive_integer(	params,
			                                oss.str().c_str(),
			                                _f_block_hypotheses + i ) )
			{
				string toto;
				if ( api_get_string ( params, oss.str().c_str(), &toto, &cout ) )
				{
					delete[] _ids;
					return 1;
				}

				if ( toto == "known_block" )
					_f_block_hypotheses[i] = 0;
				else if ( toto == "free_block" )
					_f_block_hypotheses[i] = 3;
				else if ( toto == "t1_block" )
					_f_block_hypotheses[i] = 1;
				else if ( toto == "t2_block" )
					_f_block_hypotheses[i] = 2;
				else
				{
					delete[] _ids;
					return 1;
				}
			}

			if ( _f_block_hypotheses[i] > 3 )
			{
				cout << "Error : " << oss.str().c_str() << "=" << _f_block_hypotheses[i] << endl;
				delete[] _ids;
				return 1;
			}

		}


	}

	//Lecture des matrices P associées
	for ( unsigned int i = 0; i < _nb_f_blocks ; ++ i )
	{
		gsl_matrix tmp_p;
		stringstream oss;
		oss << "F::block(" << _ids[i] << ")::P";
		if ( api_get_matrix(	params,
		                        oss.str().c_str(),
		                        &tmp_p ) )
		{
			string toto;

			if ( api_get_string( params, oss.str().c_str(), &toto ) )
				cout << "Warning : " << oss.str() << " was set to I(" << _f_block_sizes[i] << ")" << endl;
			else if (	toto != "I" 		&&
			            toto != "Identity"	&&
			            toto != "default"	)
				cout << "Warning : " << oss.str() << " was set to I(" << _f_block_sizes[i] << ")" << endl;
			for ( unsigned int k = 0; k < _f_block_sizes[i]; ++ k )
				_p->data[ ( _p->tda + 1) * _f_block_row_ids[i][k]] = 1;
		}
		else
		{
			if ( 	tmp_p.size1 != _f_block_sizes[i] ||
			        tmp_p.size2 != _f_block_sizes[i] )
			{
				cout << "Error : Wrong dimension for " << oss.str().c_str() << "!" << endl;
				delete[] _ids;
				return 1;
			}
			if ( gsl_matrix_rank( &tmp_p ) <  _f_block_sizes[i] )
			{
				cout << "Error : Matrix " << oss.str().c_str() << " is invertible !" << endl;
				delete[] _ids;
				return 1;
			}

			for ( unsigned int k = 0; k < _f_block_sizes[i]; ++ k )
			{
				for ( unsigned int l = 0; l < _f_block_sizes[i]; ++ l )
				{
					_p->data[ _p->tda * _f_block_row_ids[i][k] + _f_block_row_ids[i][l] ] =
					    tmp_p.data[ tmp_p.tda * k + l];
				}
			}
		}


	}

	//Lecture des données auxiliaires des différents blocs
	for ( unsigned int i = 0; i < _nb_f_blocks ; ++ i )
	{
		switch ( _f_block_hypotheses[i] )
		{
		//Bloc connu ( Rien à faire!)
		case (0):
			break;

		//Bloc type-2
		case (1):
		{
			gsl_matrix toto;
			stringstream oss;
			oss << "F::block(" << _ids[i] << ")::t1_block::M";

			if ( api_get_matrix ( params, oss.str().c_str(), &toto ) )
			{
				string str;
				bool id = true;
				if ( api_get_string( params, oss.str().c_str(), &str ) )
					cout << "Warning : " << oss.str() << " was set to I(" << _f_block_sizes[i] << ")" << endl;
				else if (	str == "I" 			||
				            str == "Identity"	||
				            str == "default"	)
				{}
				else if (	str == "Kalman"	)
				{
					id = false;
					gsl_matrix * tmp = gsl_matrix_calloc( _size_x, _size_t );
					gsl_matrix_view m_view = gsl_matrix_submatrix( 	tmp,
					                         0,
					                         0,
					                         _size_x,
					                         _size_x );
					gsl_matrix_set_identity( &m_view.matrix );
					_f_other_data[i] = (void*) tmp;

				}
				else
					cout << "Warning : " << oss.str() << " was set to I(" << _f_block_sizes[i] << ")" << endl;
				if ( id )
				{
					gsl_matrix * tmp = gsl_matrix_alloc( _size_t, _size_t );
					gsl_matrix_set_identity( tmp );
					_f_other_data[i] = (void*) tmp;
				}
			}
			else if ( toto.size1 > _size_t || toto.size2 != _size_t )
			{
				cout << "Error: Wrong dimensions for " << oss.str() << "!" << endl;
				delete[] _ids;
				return 1;
			}
			else if ( gsl_matrix_rank( &toto) != toto.size1 )
			{
				cout << "Error: " << oss.str() << " is not full-rank!" << endl;
				cout << "Rank = " << gsl_matrix_rank( &toto) << endl;
				delete[] _ids;
				return 1;
			}
			else
			{
				gsl_matrix * tmp = gsl_matrix_alloc( toto.size1, toto.size2 );
				gsl_matrix_memcpy ( tmp, &toto );
				_f_other_data[i] = (void*) tmp;
			}
		}
		break;
		//Bloc type-3
		case (2):
		{
			stringstream oss;
			oss << "F::block(" << _ids[i] << ")::t2_block::nb_lambda";
			unsigned int nb_lambda;

			if ( api_get_positive_integer ( params, oss.str().c_str(), &nb_lambda, &cout ) )
			{
				delete[] _ids;
				return 1;
			}

			gsl_matrix * tmp_mat = new gsl_matrix[nb_lambda];
			for ( unsigned int j = 0; j < nb_lambda; ++ j)
			{
				oss.str("");
				oss << "F::block(" << _ids[i] << ")::t2_block::M(" << j + 1 << ")";
				if ( api_get_matrix ( params, oss.str().c_str(), tmp_mat + j, &cout ) )
				{
					cout << "Error : " << oss.str() << " doesn't exist!" << endl;
					delete[] tmp_mat;
					delete[] _ids;
					return 1;
				}
				if ( tmp_mat[j].size1 != _f_block_sizes[i] || tmp_mat[j].size2 != _size_t )
				{
					cout << "Error : Wrong dimensions for " << oss.str() << "!" << endl;
					delete[] tmp_mat;
					delete[] _ids;
					return 1;
				}

			}
			f_estimation :: t2_block :: file_data * tmp = new f_estimation :: t2_block :: file_data;
			tmp->m = new gsl_matrix*[nb_lambda];
			tmp->size_lambda = nb_lambda;

			for ( unsigned int j = 0; j < nb_lambda; ++ j )
			{
				tmp->m[j] = gsl_matrix_alloc( _f_block_sizes[i], _size_t );
				gsl_matrix_memcpy( tmp->m[j], tmp_mat + j );
			}

			_f_other_data[i] = (void*) tmp;
			delete[] tmp_mat;

			//Check de l'indépendance
			{
				unsigned int n = _f_block_sizes[i] * _size_t;
				if ( tmp->size_lambda > n )
					return 4;
				gsl_matrix * mat = gsl_matrix_alloc(	tmp->size_lambda,
				                                        n );
				for ( unsigned int k = 0; k < tmp->size_lambda; ++ k )
				{
					for ( unsigned int l = 0; l < _f_block_sizes[i]; ++ l )
					{
						for ( unsigned int m = 0; m < _size_t; ++ m )
						{
							mat->data[ k * mat->tda + l * _size_t + m ] =
							    tmp->m[k]->data[l * tmp->m[k]->tda + m];
						}
					}
				}
				gsl_matrix * mat_2 = gsl_matrix_alloc( n, tmp->size_lambda );
				gsl_matrix_transpose_memcpy( mat_2, mat );

				unsigned int rk = gsl_matrix_rank( mat_2 );
				gsl_matrix_free( mat );
				gsl_matrix_free( mat_2 );
				if ( rk != tmp->size_lambda )
				{
					cout << "Error : F::block(" << _ids[i] << ")::t2_block::M(*) are not independant!" << endl;
					delete[] _ids;
					return 1;
				}
			}


		}
		break;
		case (3): //Free block
		{
			gsl_matrix * tmp = gsl_matrix_alloc( _size_t, _size_t );
			gsl_matrix_set_identity( tmp );
			_f_other_data[i] = (void*) tmp;
			_f_block_hypotheses[i] = 1;
		}
		break;
		default://Impossible
			break;
		}

	}
	if ( _ids )
		delete[] _ids;

	return 0;
}

int parameters :: load_Q_data(	api_parameters & params )
{
	gsl_vector block_sets;
	unsigned int * _ids = 0;
	if ( api_get_vector( 	params,
	                        "Q::block::sets",
	                        &block_sets ) )
	{
		string str;
		if ( api_get_string(	params,
		                        "Q::block::sets",
		                        &str ) )
			cout << "Warning : Q::block::sets = F::block::sets" << endl;
		else if ( str != "default" )
			cout << "Warning : Q::block::sets = F::block::sets" << endl;


		_nb_q_blocks = _nb_f_blocks;
		//Allocation mémoire
		_q_block_sizes = new unsigned int[_nb_f_blocks];
		memcpy(	_q_block_sizes,
		        _f_block_sizes,
		        sizeof(int) * _nb_f_blocks );

		_q_block_hypotheses = new unsigned int [_nb_q_blocks];
		for ( unsigned int i = 0; i < _nb_f_blocks; ++ i )
			_q_block_hypotheses[i] = 1;



		_q_block_row_ids = new unsigned int*[_nb_q_blocks];
		for ( unsigned int i = 0; i < _nb_f_blocks; ++ i )
		{
			_q_block_row_ids[i] = new unsigned int[_f_block_sizes[i]];
			memcpy(	_q_block_row_ids[i],
			        _f_block_row_ids[i],
			        sizeof(int) * _f_block_sizes[i] );
		}

		_q_other_data = new void*[_nb_q_blocks];
		memset( _q_other_data, 0, sizeof( void*) * _nb_q_blocks );
		_ids = new unsigned int[_nb_q_blocks];

		for ( unsigned int i = 0; i < _nb_q_blocks; ++ i)
			_ids[i] = (unsigned int) - i;

	}
	else if ( block_sets.size < _size_t )
	{
		cout << "Error : Wrong dimensions for Q::block::sets" << endl;
		return 1;
	}
	else
	{
		//Nombre de block
		_nb_q_blocks = 0;
		_ids = new unsigned int[ _size_t ];

		for ( unsigned int i = 0; i < _size_t ; ++ i )
		{
			bool exist = false;
			for ( unsigned int j = 0; j < _nb_q_blocks; ++ j )
			{
				if ( _ids[j] == block_sets.data[i * block_sets.stride] )
					exist = true;
			}
			if ( ! exist )
			{
				_ids[_nb_q_blocks] = block_sets.data[i * block_sets.stride];
				_nb_q_blocks ++;
			}

		}

		//Allocation mémoire
		_q_block_sizes = new unsigned int[_nb_q_blocks];
		memset
		(	_q_block_sizes,
		    0,
		    sizeof (unsigned int) * _nb_q_blocks );
		_q_block_hypotheses = new unsigned int [_nb_q_blocks];
		memset( _q_block_hypotheses,
		        0,
		        sizeof (unsigned int) * _nb_q_blocks );
		_q_block_row_ids = new unsigned int*[_nb_q_blocks];
		_q_other_data = new void*[_nb_q_blocks];
		memset(	_q_other_data,
		        0,
		        _nb_q_blocks * sizeof(void*) );
		//Taille des différents blocks
		for ( unsigned int i = 0; i < _nb_q_blocks ; ++ i )
		{
			for ( unsigned int j = 0; j < _size_t; ++ j )
			{
				if ( _ids[i] == block_sets.data[j * block_sets.stride] )
					++ _q_block_sizes[i];
			}
		}

		//Lignes des différents block
		for ( unsigned int i = 0; i < _nb_q_blocks ; ++ i )
		{
			unsigned int n = 0;
			_q_block_row_ids[i] = new unsigned int[_q_block_sizes[i]];
			for ( unsigned int j = 0; j < _size_t; ++ j )
			{
				if ( _ids[i] == block_sets.data[j * block_sets.stride] )
				{
					_q_block_row_ids[i][n] = j;
					++n;
				}
			}
		}

		//Lecture des hypothèses des différents blocks
		for ( unsigned int i = 0; i < _nb_q_blocks ; ++ i )
		{

			stringstream oss;
			oss << "Q::block(" << _ids[i] << ")::hypothesis";



			if ( api_get_positive_integer(	params,
			                                oss.str().c_str(),
			                                _q_block_hypotheses + i ) )
			{
				string toto;
				if ( api_get_string ( params, oss.str().c_str(), &toto, &cout ) )
				{
					delete[] _ids;
					return 1;
				}

				if ( toto == "known_block" )
					_q_block_hypotheses[i] = 0;
				else if ( toto == "free_block" )
					_q_block_hypotheses[i] = 1;
				else if ( toto == "t2_block" )
					_q_block_hypotheses[i] = 2;
				else if ( toto == "t3_block" )
					_q_block_hypotheses[i] = 3;
				else
				{
					delete[] _ids;
					return 1;
				}
			}

			if ( _q_block_hypotheses[i] > 3 )
			{
				cout << "Error : " << oss.str() << "=" << _q_block_hypotheses[i] << endl;
				delete[] _ids;
				return 1;
			}

		}
	}
	//Lecture des données auxiliaire des différents blocks
	for ( unsigned int i = 0; i < _nb_q_blocks ; ++ i )
	{
		switch ( _q_block_hypotheses[i] )
		{
		case (3):
		{
			gsl_vector toto;
			stringstream oss;
			oss << "Q::block(" << _ids[i] << ")::t3_block::sets";

			if ( api_get_vector ( params, oss.str().c_str(), &toto, &cout ) )
			{
				delete[] _ids;
				return 1;
			}
			else if ( toto.size < _q_block_sizes[i] )
			{
				cout << "Error: Wrong dimensions for " << oss.str() << "!" << endl;
				delete[] _ids;
				return 1;
			}
			q_estimation :: t3_block :: file_data * tmp = new q_estimation :: t3_block :: file_data;
			_q_other_data[i] = (void*) tmp;

			tmp->nb_blocks = 0;
			tmp->matrices = 0;
			tmp->row_ids = 0;

			//nombre de block différents
			unsigned int * _ids_2 = new unsigned int[ _q_block_sizes[i] ];
			for ( unsigned int j = 0; j < _q_block_sizes[i] ; ++ j )
			{
				bool exist = false;
				for ( unsigned int k = 0; k < tmp->nb_blocks; ++ k )
				{
					if ( _ids_2[k] == toto.data[j * toto.stride] )
						exist = true;
				}
				if ( ! exist )
				{
					_ids_2[tmp->nb_blocks] = toto.data[j * toto.stride];
					tmp->nb_blocks++;
				}
			}

			tmp->block_sizes = _q_block_sizes[i] / tmp->nb_blocks;
			if ( _q_block_sizes[i] % tmp->nb_blocks )
			{
				delete[] _ids;
				delete[] _ids_2;
				cout << "Error : Wrong subblock set indices " << oss.str() << endl;
				return 1;
			}

			//Vérification de la taille des blocks
			for ( unsigned int j = 0; j < tmp->nb_blocks ; ++ j )
			{
				unsigned int size = 0;
				for ( unsigned int k = 0; k < _q_block_sizes[i]; ++ k )
				{
					if ( _ids_2[j] == toto.data[k * toto.stride] )
						++ size;
				}
				if ( size != tmp->block_sizes )
				{
					delete[] _ids;
					delete[] _ids_2;
					cout << "Error : Wrong subblock set indices " << oss.str() << endl;
					return 1;
				}
			}

			tmp->row_ids = new unsigned int*[tmp->nb_blocks];

			//Lignes des différents block
			for ( unsigned int j = 0; j < tmp->nb_blocks ; ++ j )
			{
				unsigned int n = 0;
				tmp->row_ids[j] = new unsigned int[tmp->block_sizes];
				for ( unsigned int k = 0; k <  _q_block_sizes[i]; ++ k )
				{
					if ( _ids_2[j] == toto.data[k * toto.stride] )
					{
						tmp->row_ids[j][n] = k;
						++n;
					}
				}
			}

			//Lecture des différentes matrices
			tmp->matrices = new gsl_matrix*[tmp->nb_blocks];
			memset(	tmp->matrices,
			        0,
			        sizeof( gsl_matrix*) * tmp->nb_blocks );

			for ( unsigned int j = 0; j < tmp->nb_blocks ; ++ j )
			{
				oss.str("");
				oss << "Q::block(" << _ids[i] << ")::t3_block::M(" << _ids_2[j] << ")";
				gsl_matrix mat;
				if ( api_get_matrix (	params,
				                        oss.str().c_str(),
				                        &mat ) )
				{
					string str;
					if ( api_get_string(	params,
					                        oss.str().c_str(),
					                        &str ) )
						cout << "Warning : " << oss.str() << " was set to I!" << endl;
					else if ( str != "I" && str != "Identity" && str != "default" )
						cout << "Warning : " << oss.str() << " was set to I!" << endl;
					tmp->matrices[j] = gsl_matrix_alloc( tmp->block_sizes, tmp->block_sizes  );
					gsl_matrix_set_identity( tmp->matrices[j] );

				}
				else if ( 	mat.size1 != tmp->block_sizes ||
				            mat.size2 != tmp->block_sizes )
				{
					cout << "Error : Wrong dimension for " << oss.str() << "!" << endl;
					delete[] _ids_2;
					delete[] _ids;
					return 1;
				}
				else if ( gsl_matrix_rank( &mat ) != tmp->block_sizes )
				{
					cout << "Error : " << oss.str() << " is not invertible!" << endl;
					delete[] _ids_2;
					delete[] _ids;
					return 1;
				}
				else
				{
					tmp->matrices[j] = gsl_matrix_alloc( tmp->block_sizes, tmp->block_sizes  );
					gsl_matrix_memcpy( tmp->matrices[j], &mat );
				}
			}
			delete[] _ids_2;
		}
		break;
		default:
			break;
		}

	}
	delete[] _ids;

	return 0;
}

int parameters :: setup ( api_parameters & params )
{
	free();
	initialize();
	//Chargement des paramètres initiaux
	if ( tkalman :: api :: parameters :: setup( params ) )
		return 1;

	//Chargement de F_0 et q_i
	//F_0
	//Si rien, F_0 = 0
	{
		bool exist = true;
		gsl_matrix f_0;
		if ( api_get_matrix( 	params,
		                        "EM::F_0",
		                        &f_0 ) )
		{
			cout << "Warning : EM::F_0 doesn't exist!" << endl;
			cout << "\t\t: EM::F_0 := 0" << endl;
			exist = false;
		}
		_f_0 = gsl_matrix_alloc( _size_t,
		                         _size_t );
		if ( exist )
		{
			if ( f_0.size2 != _size_t )
			{
				cout << "f_0.size2=" << f_0.size2 << ", _size_t=" << _size_t;
				cout << "Warning : EM::F_0 is not square!" << endl;
				cout << "\t\t: EM::F_0 := 0" << endl;
				exist = false;
			}
		}
		if ( exist )
			gsl_matrix_memcpy( 	_f_0,
			                    &f_0 );
		else
			gsl_matrix_set_zero( _f_0 );
	}
	//q_i
	//Si rien q_i = I
	{
		bool exist = true;
		gsl_matrix q_i;
		if ( api_get_matrix( 	params,
		                        "EM::Q_0",
		                        &q_i,
		                        &cout ) )
		{
			cout << "Warning : EM::Q_0 doesn't exist!" << endl;
			cout << "\t\t: EM::Q_0 := I" << endl;
			exist = false;
		}

		_q_i = gsl_matrix_alloc( _size_t,
		                         _size_t );
		_sqrt_q_i = gsl_matrix_alloc( 	_size_t,
		                                _size_t );
		if ( exist )
		{
			if ( q_i.size2 != _size_t ||
			        q_i.size1 != _size_t  )
			{
				cout << "Warning : EM::Q_0 is not square!" << endl;
				cout << "\t\t: EM::Q_0 := I" << endl;
				exist = false;
			}
		}
		if ( exist )
		{
			gsl_matrix_memcpy( 	_q_i,
			                    &q_i );
			gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (_size_t);
			gsl_matrix * q_cp = gsl_matrix_alloc( _size_t, _size_t );
			gsl_matrix * _p = gsl_matrix_alloc( _size_t, _size_t );
			gsl_vector * vp = gsl_vector_alloc( _size_t );

			//Recopie de q
			gsl_matrix_memcpy( q_cp, _q_i );

			//Calcul des vp
			gsl_eigen_symmv (	q_cp,
			                    vp,
			                    _p,
			                    w );

			//Construction de la matrice sq(D)
			gsl_matrix_set_zero( q_cp );
			for ( unsigned int i = 0; i < _size_t; ++ i )
			{
				if ( vp->data[i * vp->stride] < 0 )
				{
					gsl_vector_free ( vp );
					gsl_matrix_free( q_cp );
					gsl_eigen_symmv_free (w);
					cout << "Warning : EM::Q_0 is not positive!" << endl;
					cout << "\t\t: EM::Q_0 := I" << endl;
					exist = false;
					break;
				}
				q_cp->data[ i * (q_cp->tda + 1) ] = sqrt( vp->data[i * vp->stride] );

			}

			if ( exist )
			{
				gsl_blas_dgemm(	CblasNoTrans,
				                CblasTrans,
				                1.0,
				                q_cp,
				                _p,
				                0.0,
				                _sqrt_q_i );
				gsl_linalg_QR_decomp(_sqrt_q_i,
				                     vp);
				gsl_triangle_matrix(_sqrt_q_i);

				gsl_vector_free ( vp );
				gsl_matrix_free( q_cp );
				gsl_matrix_free( _p );
				gsl_eigen_symmv_free (w);
			}
		}

		if ( ! exist )
		{
			gsl_matrix_set_identity( _q_i );
			gsl_matrix_set_identity( _sqrt_q_i );
		}
	}

	//Nombre d'itérations EM
	// 0 par défaut
	{
		if ( api_get_positive_integer( params, "nb_iter_EM", &_nb_EM_iterations ) )
		{
			cout << "Warning : nb_iter_EM = 0!" << endl;
			_nb_EM_iterations = 0;
		}
	}

	//F-Block
	if ( load_F_data( params ) )
		return 1;

	//Q-Block
	if ( load_Q_data( params ) )
		return 1;

	//Equivalences
	{
		if ( api_get_positive_integer( params, "EM::equivalence_type", &_type_equivalence ) )
		{
			string toto;
			if ( api_get_string( params, "EM::equivalence_type", &toto ) )
				_type_equivalence = 0;
			else
			{
				if ( toto == "default" )
					_type_equivalence = 0;
				else if ( toto == "t1" )
					_type_equivalence = 1;
				else if ( toto == "t2" )
					_type_equivalence = 2;
				else if ( toto == "t3" )
					_type_equivalence = 3;
			}
		}
		if ( _type_equivalence > 3 )
			_type_equivalence = 0;
	}
	//Estimation des états initiaux
	int toto;
	if ( api_get_integer( params, "EM:first_state_estimation", &toto ) )
		toto = 0;
	_first_state_estimation = (toto != 0);


	return 0;
}


parameters :: ~parameters()
{
	free();
	initialize();
}

void parameters :: free()
{
	//Free
	//F
	if ( _f_other_data )
	{
		for ( unsigned int i = 0; i < _nb_f_blocks; ++ i )
		{
			if ( _f_other_data[i] )
			{
				switch ( _f_block_hypotheses[i] )
				{
				case (1):
					gsl_matrix_free( (gsl_matrix*) _f_other_data[i] );
					break;
				case (2):
				{
					tkalman :: f_estimation :: t2_block :: file_data * tmp = ( tkalman :: f_estimation :: t2_block :: file_data * ) _f_other_data[i];
					if ( tmp->m )
					{
						for ( unsigned int j = 0; j < tmp->size_lambda; ++ j )
						{
							if (tmp->m[j] )
								gsl_matrix_free( tmp->m[j] );
						}
						delete[] tmp->m;
					}
					delete tmp;
				}
				break;
				default://Impossible

					break;
				}
			}
		}
		delete[] _f_other_data;
	}

	if ( _f_block_row_ids )
	{
		for ( unsigned int i = 0; i < _nb_f_blocks; ++ i )
		{
			if ( _f_block_row_ids[i] )
				delete[] _f_block_row_ids[i];
		}
		delete[] _f_block_row_ids;
	}

	if ( _f_block_sizes )
		delete[] _f_block_sizes;
	if ( _f_block_hypotheses )
		delete[] _f_block_hypotheses;

	if ( _f_0)
		gsl_matrix_free ( _f_0 );
	if ( _p )
		gsl_matrix_free( _p );

	//Q
	if ( _q_other_data )
	{
		for ( unsigned int i = 0; i < _nb_q_blocks; ++ i )
		{
			if ( _q_other_data[i] )
			{
				switch ( _q_block_hypotheses[i] )
				{
				case (3):
				{
					q_estimation :: t3_block :: file_data * tmp = (q_estimation :: t3_block :: file_data *) _q_other_data[i];

					if ( tmp->matrices )
					{
						for ( unsigned int j = 0; j < tmp->nb_blocks; ++ j )
						{
							if ( tmp->matrices[j] )
								gsl_matrix_free( tmp->matrices[j] );
						}
						delete[] tmp->matrices;
					}

					if ( tmp->row_ids )
					{
						for ( unsigned int j = 0; j < tmp->nb_blocks; ++ j )
						{
							if ( tmp->row_ids[j] )
								delete[] tmp->row_ids[j];
						}
						delete[] tmp->row_ids;
					}

					delete tmp;
				}
				break;
				default://Impossible

					break;
				}
			}
		}
		delete[] _q_other_data;
	}

	if ( _q_block_row_ids )
	{
		for ( unsigned int i = 0; i < _nb_q_blocks; ++ i )
		{
			if ( _q_block_row_ids[i] )
				delete[] _q_block_row_ids[i];
		}
		delete[] _q_block_row_ids;
	}

	if ( _q_block_sizes )
		delete[] _q_block_sizes;

	if ( _q_block_hypotheses )
		delete[] _q_block_hypotheses;

	if ( _q_i)
		gsl_matrix_free ( _q_i );
	if ( _sqrt_q_i)
		gsl_matrix_free ( _sqrt_q_i );
}

void parameters :: initialize()
{
	_f_0 = 0;
	_q_i = 0;
	_nb_EM_iterations = 0;
	_nb_f_blocks = 0;
	_nb_q_blocks = 0;
	_f_block_sizes = 0;
	_q_block_sizes = 0;
	_f_block_row_ids = 0;
	_q_block_row_ids = 0;
	_f_block_hypotheses = 0;
	_q_block_hypotheses = 0;
	_p = 0;
	_f_other_data = 0;
	_q_other_data = 0;
	_sqrt_q_i = 0;
	_type_equivalence = 0;
	_first_state_estimation = false;
}

};
};
};
