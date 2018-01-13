#ifndef _TKALMAN_EM_HPP_
#define _TKALMAN_EM_HPP_
#include "tkalman_em_parameters.hpp"
#include "../../Filter/lib_PKF_filter.hpp"
#include "../../Q_estimation/lib_PKF_Q.hpp"
#include "../../F_estimation/lib_PKF_F.hpp"
#include "tkalman_sum.hpp"
#include "tkalman_em_estimator_workspace.hpp"
namespace tkalman
{

namespace EM
{
	
/**@class tkalman :: EM
 * @brief
 * Class for EM algorithm in Pairwise Kalman filter
 * 
 **/
class estimator
{
public:
	/**@fn tkalman :: EM :: EM ( void )
	 * @brief
	 * Default constructor
	 * 
	 **/
	estimator( void );

	/**@fn tkalman :: EM :: EM ( const EM_parameters * initial_parameters );
	 * @param[in] initial_parameters : EM parameters
	 * @brief
	 * Constructor
	 *
	 **/
	estimator( const EM :: parameters * params ) throw (exception&);
	
	/**@fn int tkalman :: EM :: setup ( const EM_parameters * initial_parameters );
	 * @param[in] initial_parameters : EM parameters
	 * @brief
	 * Setup
	 *
	 **/
	int setup ( const EM :: parameters * params );
	
	/**@fn void tkalman :: EM :: reset();
	 * @brief Reset
	 **/
	void reset();
	
	/**@fn tkalman :: EM :: ~EM();
	 * @brief
	 * Destructor
	 * 
	 **/
	~estimator();

	/**@fn int tkalman :: EM :: smooth(	moments & m,
										parameters & p,
										const gsl_vector * const * y,
										unsigned int nb_observations,
										unsigned int nb_iterations,
										double * likelihood = NULL ) const;
	 * @param[out] moments : moments
	 * @param[out] p : estimated parameters
	 * @param[in] y : observations
	 * @param[in] nb_observations : nb of observations
	 * @param[in] nb_iterations : nb of iterations
	 * @brief
	 * EM algorithm
	 **/
	int estimate( 	tkalman :: moments & m,
					tkalman :: parameters & p,
					const gsl_vector * const * observations,
					unsigned int nb_observations,
					unsigned int nb_iterations,
					double * likelihood = NULL ) const;
	
	int estimate( 	tkalman :: moments * m,
					tkalman :: parameters & p,
					const gsl_vector * const * const * observations,
					const unsigned int * nb_observations,
					unsigned int nb_signals,
					unsigned int nb_iterations,
					double * likelihood = NULL ) const;
	
	
	
	/**@fn
	 * @return
	 * Filter
	 * 
	 **/
	inline const filter & get_filter() const
	{
		return pkf_filter;
	}

protected:
	/**@fn void tkalman :: EM  :: initialize();
	 * @brief
	 * This function sets object attributes to 0.
	 */
	void initialize();
	
	/**@fn void tkalman :: EM :: free();
	 * @brief
	 * This function frees memory.
	 */
	void free();
	/**@fn void tkalman :: EM :: alloc();
	 * @brief
	 * This function allocates attributes.
	 */
	void alloc();
	
	//Parameters
	const EM :: parameters * p;
	
	//filter + Sums
	filter  pkf_filter;
	sum pkf_sum;
	
	//Estimators
	f_estimation :: estimator f_estimator;
	q_estimation :: estimator q_estimator;
	
	//Workspaces
	mutable tkalman :: EM :: estimator_workspace * w;
	
	
	
	bool _first_state_estimation;
};
};
};


#endif
