#include "gsl_matrix_trace.hpp"
int gsl_matrix_trace(	double & trace,
						const gsl_matrix * m )
{
	if ( m == NULL )
		return -1;
		
	if ( m->size1 != m->size2 )
		return 1;
		
	trace = 0;
	for ( unsigned int i = 0; i < m->size1; ++ i)
	{
		trace += m->data[ i * (m->tda + 1)];
	}
	return 0;
}
