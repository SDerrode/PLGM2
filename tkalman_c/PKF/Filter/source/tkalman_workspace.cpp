#include "tkalman_workspace.hpp"
using namespace tkalman;

workspace :: workspace (	unsigned int size_x,
							unsigned int size_y ) throw ( exception & )
{
	initialize();
	_size_x = size_x;
	_size_y = size_y;
	_size_t = size_x + size_y;
}

void workspace :: initialize()
{
	_size_x = 0;
	_size_y = 0;
	_size_t = 0;
}

workspace :: ~workspace()
{
	initialize();
}
