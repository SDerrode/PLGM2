#ifndef _TKALMAN_EM_PARAMETERS_HPP_
#define _TKALMAN_EM_PARAMETERS_HPP_
#include <gsl/gsl_matrix.h>
namespace tkalman
{
namespace EM
{
class parameters
{
public:
/**@fn tkalman :: EM :: parameters ::  parameters( void );
 * @brief
 * Default constructor
 **/
parameters( void );

/**@fn
 * @param[in] f_0 : \f$ F_0\f$
 * @param[in] sqrt_q_0 : \f$ [Q_0]^{\frac{1}{2}}\f$
 * @param[in] p : \f$ P \f$
 * @param[in] nb_f_block : number of blocks for F estimation
 * @param[in] nb_q_block : number of blocks for Q estimation
 * @param[in] f_block_sizes : sizes of F blocks
 * @param[in] q_block_sizes : sizes of Q blocks
 * @param[in] f_block_row_ids : row ids of f blocks
 * @param[in] q_block_row_ids : row ids of q blocks
 * @param[in] f_block_hypotheses : f blocks hypotheses
 * @param[in] q_block_hypotheses : q blocks hypotheses
 * @param[in] f_other_data : other data
 * @param[in] q_other_data : other data
 * 
 **/
parameters(	const gsl_matrix * f_0,
			const gsl_matrix * sqrt_q_0,
			const gsl_matrix * p,
			unsigned int size_x,
			unsigned int nb_f_blocks,
			unsigned int nb_q_blocks,
			const unsigned int * f_block_sizes,
			const unsigned int * q_block_sizes,
			const unsigned int * const * f_block_row_ids,
			const unsigned int * const * q_block_row_ids,
			const unsigned int * f_block_hypotheses,
			const unsigned int * q_block_hypotheses,
			const void * const * f_other_data,
			const void * const * q_other_data,
			bool first_state_estimation = false );

/**@fn void tkalman :: EM_parameters :: reset();
 * @brief Reset
 **/
void reset();

/**@fn int  tkalman :: EM_parameters :: setup(	const parameters & f_params,
												const unsigned int * f_mask,
												const gsl_matrix *p,
												const unsigned int *subnoise_ids,
												const unsigned int *subnoise_hypotheses )
 * @param[in] f_params : Filter parameters
 * @param[in] f_mask : estimated term of \f$F\f$
 * @param[in] p : 
 * @param[in] subnoise_ids : ids of different subnoise
 * @param[in] subnoise_hypotheses : hypotheses for different subnoise
 * @param[in] nb_EM_iterations : number of EM iterations
 * @brief
 * Setup
 **/
int setup(	const gsl_matrix * f_0,
			const gsl_matrix * sqrt_q_0,
			const gsl_matrix * p,
			unsigned int size_x,
			unsigned int nb_f_blocks,
			unsigned int nb_q_blocks,
			const unsigned int * f_block_sizes,
			const unsigned int * q_block_sizes,
			const unsigned int * const * f_block_row_ids,
			const unsigned int * const * q_block_row_ids,
			const unsigned int * f_block_row_hypotheses,
			const unsigned int * q_block_row_hypotheses,
			const void * const * f_other_data,
			const void * const * q_other_data,
			bool first_state_estimation = false );
			
/**@fn EM_parameters::~EM_parameters()
 * @brief
 * Destructor
 * 
 **/
~parameters();

//Others
inline bool operator! () const
{
	return !safe;
}

protected:
/**@fn void tkalman :: parameters :: initialize();
 * @brief
 * This function sets object attributes to 0.
 */
void initialize();

protected:
unsigned int 	_size_x;
public:
/**@fn 
 * @brief
 * \f$n_x\f$
 * 
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

unsigned int 	_size_y;
public:
/**@fn 
 * @brief
 * \f$n_y\f$
 * 
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

unsigned int 	_size_t;
public:
/**@fn 
 * @brief
 * \f$n_y\f$
 * 
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

protected:
bool safe;

protected:
const gsl_matrix 	*_f_0;

public:
inline const gsl_matrix * f_0() const
{
	return _f_0;
}

protected:
const gsl_matrix 	*_sqrt_q_0;

public:
inline const gsl_matrix * sqrt_q_0() const
{
	return _sqrt_q_0;
}

protected:
const gsl_matrix 	*_p;

public:
inline const gsl_matrix * p() const
{
	return _p;
}

protected:
unsigned int _nb_f_blocks;

public:
inline unsigned int nb_f_blocks() const
{
	return _nb_f_blocks;
}

protected:
unsigned int _nb_q_blocks;

public:
inline unsigned int nb_q_blocks() const
{
	return _nb_q_blocks;
}

protected:
const unsigned int * _f_block_sizes;

public:
inline const unsigned int * f_block_sizes() const
{
	return _f_block_sizes;
}

protected:
const unsigned int * _q_block_sizes;

public:
inline const unsigned int * q_block_sizes() const
{
	return _q_block_sizes;
}


protected:
const unsigned int *const * _f_block_row_ids;

public:
inline const unsigned int * const * f_block_row_ids() const
{
	return _f_block_row_ids;
}

protected:
const unsigned int *const * _q_block_row_ids;

public:
inline const unsigned int * const * q_block_row_ids() const
{
	return _q_block_row_ids;
}

protected:
const unsigned int * _f_block_hypotheses;

public:
inline const unsigned int * f_block_hypotheses() const
{
	return _f_block_hypotheses;
}

protected:
const unsigned int * _q_block_hypotheses;

public:
inline const unsigned int * q_block_hypotheses() const
{
	return _q_block_hypotheses;
}

protected:
const void *const * _f_other_data;

public:
inline const void * const * f_other_data() const
{
	return _f_other_data;
}

protected:
const void *const * _q_other_data;

public:
inline const void * const * q_other_data() const
{
	return _q_other_data;
}
protected:
	bool _first_state_estimation;
public:
inline bool first_state_estimation() const
{
	return _first_state_estimation;
}


};
};
};


#endif
