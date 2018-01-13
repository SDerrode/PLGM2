#ifndef _TKALMAN_Q_ESTIMATION_TYPEDEF_HPP_
#define _TKALMAN_Q_ESTIMATION_TYPEDEF_HPP_
#include <gsl/gsl_matrix.h>

namespace tkalman
{
namespace q_estimation
{
	/**@typedef void* (*tkalman :: f_estimation :: allocation_function) ( const void * data );
	 * @param data : size parameters
	 * @brief
	 * Prototype for allocation functions
	 **/
	typedef void* (*allocation_function) ( const void * data );
	
	/**@typedef void (*tkalman :: f_estimation :: freeing_function) ( void * data );
	 * @param data : data
	 * @brief
	 * Prototype for freeing function
	 **/
	typedef void (*freeing_function) ( void * data );
	
	/**@typedef int (*tkalman :: f_estimation ::setting_function) (	void *object,
	 * 																unsigned int * rows_ids
																	const void * params )
	 * @param object : object
	 * @param row_ids : row indices
	 * @param params : paramters
	 * @brief
	 * Prototype for setting function
	 **/
	typedef int (*setting_function) (	void *object,
										const void * params );
										
	/**@typedef int (*tkalman :: f_estimation ::estimation_function) (	const gsl_matrix * f_i,
																		const gsl_matrix * sqrt_c_i,
																		const void * estimator );
	 * @param[out]: f_i : \f$ F_i\f$
	 * @param[in] sqrt_c_i :\f$ [\tilde{C}_i]^{\frac{1}{2}} \f$
	 * @brief
	 * Prototype for estimation function
	 **/
	typedef void (*estimation_function) (	gsl_matrix * sqrt_q_i,
											const gsl_matrix * f_i,
											const gsl_matrix * sqrt_c_i,
											unsigned int nb_observations,
											const void * estimator );
										
	/**@class tkalman :: f_estimation :: function_set
	 * @brief
	 * Set of functions for F estimation.
	 **/
	class function_set
	{
		public:
			/**@fn tkalman :: q_estimation :: function_set :: function_set(	allocation_function estimator_allocation_function,
																			estimation_function f_estimation_function,
																			freeing_function estimator_freeing_function,
																			allocation_function parameters_allocation_function,
																			setting_function paramters_setting_function,
																			freeing_function parameters_freeing_function )
			 * @param[in] estimator_allocation_function : function for estimator allocation
			 * @param[in] f_estimation_function :  function for F estimation
			 * @param[in] estimator_freeing_function : function for estimator freeing 
			 * @param[in] parameters_allocation_function : function for parameter allocation
			 * @param[in] parameters_setting_function :  function for parameter setting 
			 * @param[in] parameters_freeing_function : function for parameter freeing
			 * @brief
			 * Constructor
			 * */
			inline function_set(	allocation_function estimator_allocation_function,
									estimation_function f_estimation_function,
									freeing_function estimator_freeing_function,
									allocation_function parameters_allocation_function,
									setting_function parameters_setting_function,
									freeing_function parameters_freeing_function )
			{
				_estimator_allocation_function = estimator_allocation_function;
				_parameters_allocation_function = parameters_allocation_function;
				_parameters_setting_function = parameters_setting_function;
				_f_estimation_function = f_estimation_function;
				_estimator_freeing_function = estimator_freeing_function;
				_parameters_freeing_function = parameters_freeing_function;
			}
				
			/**@fn bool tkalman :: f_estimation :: function_set :: operator!() const
			 * @return
			 * Check functions
			 **/
			inline bool operator!() const
			{
				return ( 	! _estimator_allocation_function	||
							! _parameters_allocation_function	||
							! _parameters_setting_function		||
							! _f_estimation_function			||
							! _estimator_freeing_function		||
							! _parameters_freeing_function		);
			}
			
			/**@fn inline allocation_function estimator_allocation_function() const
			 * @return function for estimator allocation
			 **/
			inline allocation_function estimator_allocation_function() const
			{
				return _estimator_allocation_function;
			}
			/**@fn inline estimation_function f_estimation_function() const
			 * @return function for F estimation
			 **/
			inline estimation_function f_estimation_function() const
			{
				return _f_estimation_function;
			}
			/**@fn inline freeing_function estimator_freeing_function() const
			 * @return function for estimator freeing 
			 **/
			inline freeing_function estimator_freeing_function() const
			{
				return _estimator_freeing_function;
			}
			/**@fn inline allocation_function parameters_allocation_function() const
			 * @return function for parameter allocation
			 **/
			inline allocation_function parameters_allocation_function() const
			{
				return _parameters_allocation_function;
			}
			/**@fn inline setting_function parameters_setting_function() const
			 * @return function for parameter setting 
			 **/
			inline setting_function parameters_setting_function() const
			{
				return _parameters_setting_function;
			}
			/**@fn inline freeing_function parameters_freeing_function() const
			 * @return function for parameter freeing
			 **/
			inline freeing_function parameters_freeing_function() const
			{
				return _parameters_freeing_function;
			}
			
			
		protected:
			allocation_function _estimator_allocation_function,
								_parameters_allocation_function;
			setting_function _parameters_setting_function;
			estimation_function _f_estimation_function;
			freeing_function _estimator_freeing_function,
							 _parameters_freeing_function;
	};

};
	
};

#endif
