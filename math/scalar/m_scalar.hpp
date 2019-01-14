/*
 * m_power.hpp
 *
 *  Created on: 23.11.2016
 *      Author: Lukas
 */

#ifndef CT_MATH_SCALAR_M_SCALAR_HPP_
#define CT_MATH_SCALAR_M_SCALAR_HPP_

#include <cmath>

template<typename T>
T powerDescreteFast (const T& base, uint32_t exponent)
{
	T result = 1;
	while(exponent)
	{
		if(exponent&0x1)
			result *= base;
		base *= base;
		exponent = exponent >> 1;
	}
	return result;
}



#endif /* CT_MATH_SCALAR_M_SCALAR_HPP_ */
