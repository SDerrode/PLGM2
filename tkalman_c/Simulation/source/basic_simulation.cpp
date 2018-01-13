
#include "basic_simulation.hpp"
#include <gsl/gsl_randist.h>
#include <gsl/gsl_blas.h>
unsigned int discrete_rand (	const double * p_cum,
                                unsigned int nb_modes,
                                unsigned int stride,
                                gsl_rng * rng )
{
	unsigned int r = 0;
	double t = gsl_rng_uniform( rng );
	for ( unsigned int j = 0; j < nb_modes; ++ j )
	{
		if ( t < p_cum[ j * stride] )
		{
			r = j;
			break;
		}

	}
	return r;
}

void gaussian_rand ( 	gsl_vector * x,
                        const gsl_vector * mean,
                        const gsl_matrix * sqrt_var,
                        gsl_rng * rng,
                        gsl_vector * vect_x
                   )
{
	unsigned int size_x = vect_x->size;

	for ( unsigned int i = 0; i < size_x; ++ i )
		vect_x->data[i * vect_x->stride] = gsl_ran_ugaussian (rng);
	//Ajout de la moyenne
	gsl_vector_memcpy(	x,
	                    mean);

	gsl_blas_dgemv(CblasTrans,
	               1.0,
	               sqrt_var,
	               vect_x,
	               1.0,
	               x);
}

void MM_rand ( 	gsl_vector * x,
                const double * weight_cum,
                const gsl_vector * const * _x,
                const gsl_matrix * const * _sqrt_p,
                unsigned int nb_modes,
                unsigned int stride,
                gsl_rng * rng,
                gsl_vector * tmp_x )
{
	//Tir du "r"
	unsigned int r = discrete_rand (	weight_cum,
	                                    nb_modes,
	                                    stride,
	                                    rng );

	//Tir du x
	gaussian_rand (	x,
	                _x[r],
	                _sqrt_p[r],
	                rng,
	                tmp_x );
}

