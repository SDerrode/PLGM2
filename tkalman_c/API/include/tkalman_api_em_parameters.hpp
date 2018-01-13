#ifndef _TKALMAN_API_EM_PARAMETERS_
#define _TKALMAN_API_EM_PARAMETERS_
#include "tkalman_api_parameters.hpp"
namespace tkalman
{
namespace api
{
namespace EM
{
/**@class parameters
 * @brief
 * EM_parameters
 * 
 **/
class parameters : public tkalman :: api :: parameters
{
public:
/**@fn tkalman :: api :: EM_parameters :: EM_parameters( void );
 * @brief
 * Default constructor
 **/
parameters( void );

/**@fn virtual int tkalman :: api :: EM_parameters :: setup ( api_parameters & params );
 * @brief
 * Setup.
 **/
virtual int setup ( api_parameters & params );

/**@fn tkalman :: api :: EM_parameters :: ~EM_parameters( void );
 * @brief
 * Destructor
 **/
~parameters();

protected:
/**@fn
 * @brief
 * Lib. mémoire
 * 
 **/
void free();

/**@fn
 * @brief
 * Initialisation de l'objet
 **/
void initialize();

/**@fn
 * @brief
 * Load EM data for F blocks
 **/
int load_F_data( api_parameters & params );
/**@fn
 * @brief
 * Load EM data for Q blocks
 **/
int load_Q_data( api_parameters & params );


//Paramètres obtenus directement
gsl_matrix 	*_f_0,
			*_q_i,
			*_sqrt_q_i;
			
unsigned int _nb_EM_iterations;

//Paramètres calculés
unsigned int 	_nb_f_blocks,
				_nb_q_blocks;
unsigned int 	*_f_block_sizes,
				*_q_block_sizes;
				
unsigned int 	**_f_block_row_ids,
				**_q_block_row_ids;
			 
unsigned int 	*_f_block_hypotheses,
				*_q_block_hypotheses;
				
gsl_matrix * _p;
				
void 	**_f_other_data,
		**_q_other_data;
		
unsigned int _type_equivalence;		
bool _first_state_estimation;
public: //Accesseurs
/**@fn
 * @brief
 * return constant part of F
 * 
 **/
inline const gsl_matrix * f_0() const
{
	return _f_0;
}
/**@fn
 * @brief
 * return constant part of Q
 * 
 **/
inline const gsl_matrix * q_i() const
{
	return _q_i;
}
/**@fn
 * @brief
 * return sqrt of constant part of Q
 * 
 **/
inline const gsl_matrix * sqrt_q_i() const
{
	return _sqrt_q_i;
}

/**@fn
 * @brief
 * return transformation matrix P
 * 
 **/
inline const gsl_matrix * p() const
{
	return _p;
}

/**@fn
 * @brief
 * return nb of EM iterations
 * 
 **/
inline unsigned int nb_iterations() const
{
	return _nb_EM_iterations;
}

/**@fn
 * @brief
 * return nb of F blocks
 * 
 **/
inline unsigned int nb_f_blocks() const
{
	return _nb_f_blocks;
}

/**@fn
 * @brief
 * return nb of Q blocks
 * 
 **/
inline unsigned int nb_q_blocks() const
{
	return _nb_q_blocks;
}

/**@fn
 * @brief
 * return sizes of F blocks
 * 
 **/
inline const unsigned int * f_block_sizes() const
{
	return _f_block_sizes;
}
/**@fn
 * @brief
 * return sizes of Q blocks
 * 
 **/
inline const unsigned int * q_block_sizes() const
{
	return _q_block_sizes;
}

inline const unsigned int * const * f_block_row_ids() const
{
	return _f_block_row_ids;
}

inline const unsigned int * const * q_block_row_ids() const
{
	return _q_block_row_ids;
}

inline const unsigned int * f_block_hypotheses() const
{
	return _f_block_hypotheses;
}

inline const unsigned int * q_block_hypotheses() const
{
	return _q_block_hypotheses;
}

inline const void * const * f_other_data() const
{
	return _f_other_data;
}

inline const void * const * q_other_data() const
{
	return _q_other_data;
}

inline unsigned int equivalence_type() const
{
	return _type_equivalence;
}
inline bool first_state_estimation() const
{
	return _first_state_estimation;
}

};
	
	
};
};
};


#endif
