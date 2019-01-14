/*
 * m_gcd.hpp
 *
 *  Created on: 08.02.2018
 *      Author: Lukas
 */

#ifndef CT_MATH_SCALAR_M_GCD_HPP_
#define CT_MATH_SCALAR_M_GCD_HPP_


template<typename T, typename K, typename = typename std::enable_if<std::is_integral<T>::value >::type, typename = typename std::enable_if<std::is_integral<K>::value >::type>
T gcd (const T& a, const K& b)
{
	T loc_a = a;
	K loc_b = b;

	if(a == T(0))
		return b;

	while(b != K(0))
	{
		T h = loc_a%loc_b;
		loc_a = loc_b;
		loc_b = h;
	}
	return std::abs(loc_a);
}

template<typename T, typename K, typename = typename std::enable_if<std::is_integral<T>::value >::type, typename = typename std::enable_if<std::is_integral<K>::value >::type>
T lcm (const T& a, const T&b)
{
	return std::abs(a*b/gcd(a, b));
}


#endif /* CT_MATH_SCALAR_M_GCD_HPP_ */
