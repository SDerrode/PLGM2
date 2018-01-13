#include "tkalman_f_estimation_parameters.hpp"
using namespace tkalman;
using namespace f_estimation;
parameters :: parameters ( 	unsigned int size_i, 
							unsigned int size_t ) throw (exception &)
{
	initialize();
	if ( !size_t || size_i > size_t )
		throw (invalid_argument("Invalid argument(s) in tkalman :: f_estimation :: parameters"));
	_size_t = size_t;
	_size_i = size_i;
}
parameters :: ~parameters()
{
	initialize();
}

void parameters :: initialize()
{
	_size_i = 0;
	_size_t = 0;
}
