/*
 * m_operatorsNonMember.hpp
 *
 *  Created on: 02.11.2016
 *      Author: Lukas
 */

#ifndef MATH_MATRIX_M_OPERATORSNONMEMBER_HPP_
#define MATH_MATRIX_M_OPERATORSNONMEMBER_HPP_

#include "m_matrix.hpp"
#include "m_vector.hpp"
#include "m_specialMatrix.hpp"

// Operators ----------------------------------------------------------------------------------

// Arithmetic ---------------------------------------------------------------------------------

// Scalar * Matrix
template<typename T, uint16_t lines, uint16_t columns>
m_Matrix<T,lines,columns> operator* (const T& lhs, const m_Matrix<T,lines,columns>& rhs)
{
	return rhs*lhs;
}

// Scalar + 1x1 Matrix
template<typename T, uint16_t lines, uint16_t columns,
typename = typename std::enable_if<std::is_same<m_Matrix<T,lines,columns>,m_Matrix<T,1,1>>::value >::type>
T operator+ (const T& lhs, const m_Matrix<T,lines,columns>& rhs)
{
	return T(rhs+lhs);
}

// Scalar - 1x1 Matrix
template<typename T, uint16_t lines, uint16_t columns,
typename = typename std::enable_if<std::is_same<m_Matrix<T,lines,columns>,m_Matrix<T,1,1>>::value >::type>
T operator- (const T& lhs, const m_Matrix<T,lines,columns>& rhs)
{
	return T(rhs-lhs);
}

// Scalar / 1x1 Matrix
template<typename T, uint16_t lines, uint16_t columns,
typename = typename std::enable_if<std::is_same<m_Matrix<T,lines,columns>,m_Matrix<T,1,1>>::value >::type>
T operator/ (const T& lhs, const m_Matrix<T,lines,columns>& rhs)
{
	return T(lhs/T(rhs));
}

template<typename T, uint16_t size>
m_Matrix<T,size,size> operator+ (const m_DiagonalMatrix<T,size>& lhs, const m_Matrix<T,size,size>& rhs)
{
	m_Matrix<T,size,size> result(rhs);
	for(uint16_t i=0; i < size; i++)
	{
		result[i][i] += lhs[i];
	}
	return result;
}

template<typename T, uint16_t size>
m_Matrix<T,size,size> operator- (const m_DiagonalMatrix<T,size>& lhs, const m_Matrix<T,size,size>& rhs)
{
	m_Matrix<T,size,size> result(-rhs);
	for(uint16_t i=0; i < size; i++)
	{
		result[i][i] += lhs[i];
	}
	return result;
}


template<typename T, uint16_t lines, uint16_t columns>
m_Matrix<T,lines,columns> operator* (const m_DiagonalMatrix<T,lines>& lhs, const m_Matrix<T,lines,columns>& rhs)
{
	m_Matrix<T,lines,columns> result(rhs);
	for(uint16_t i = 0; i < lines; i++) // result lines
	{
		for(uint16_t j = 0; j < columns; j++) // result columns
		{
			result[i][j] *= lhs[i];
		}
	}
	return result;
}

// --------------------------------------------------------------------------------- Arithmetic

// ---------------------------------------------------------------------------------- Operators

// Special vector operators -------------------------------------------------------------------

template<typename T, uint16_t size>
m_ColumnVector<T,size> normalize (const m_ColumnVector<T,size>& rhs)
{
	m_ColumnVector<T,size> result = rhs;
	T norm = rhs.norm2();
	for(uint16_t i = 0; i < size; i++)
	{
		result[i] /= norm;
	}

	return result;
}

template<typename T, uint16_t size>
m_LineVector<T,size> normalize (const m_LineVector<T,size>& rhs)
{
	m_LineVector<T,size> result = rhs;
	T norm = rhs.norm2();
	for(uint16_t i = 0; i < size; i++)
	{
		result[i] /= norm;
	}

	return result;
}

// ------------------------------------------------------------------- Special vector operators

#endif /* MATH_MATRIX_M_OPERATORSNONMEMBER_HPP_ */
