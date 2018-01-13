#ifndef _TKALMAN_WORKSPACE_HPP_
#define _TKALMAN_WORKSPACE_HPP_
#include <gsl/gsl_matrix.h>
#include <exception>
#include <stdexcept>
using namespace std;
namespace tkalman
{
/**@class tkalman :: workspace
 * @brief
 * Base of tkalman workspace
 **/
class workspace
{
public:
/**@fn tkalman :: workspace :: workspace(	unsigned int size_x,
											unsigned int size_y);

 * @param[in] size_x : size of x
 * @param[in] size_y : size of y
 * @brief
 * Constructor
 **/
workspace (	unsigned int size_x,
			unsigned int size_y ) throw ( exception & );

/**@fn inline unsigned int tkalman :: constants :: size_x() const
 * @return
 * Size of x
 **/
inline unsigned int size_x() const
{
	return _size_x;
}

/**@fn inline unsigned int tkalman :: constants :: size_y() const
 * @return
 * Size of y
 **/
inline unsigned int size_y() const
{
	return _size_y;
}

/**@fn inline unsigned int tkalman :: constants :: size_t() const
 * @return
 * Size of t
 **/
inline unsigned int size_t() const
{
	return _size_t;
}

/**@fn tkalman :: ~workspace();
 * @brief
 * Destructor
 **/
virtual ~workspace();
protected:
/**@fn
 * @brief
 * This function sets object attributes to 0.
 **/
virtual void initialize();

unsigned int _size_x,
			 _size_y,
			 _size_t;
};

};




#endif
