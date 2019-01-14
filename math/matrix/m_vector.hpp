/*
 * m_vector.hpp
 *
 *  Created on: 02.11.2016
 *      Author: Lukas
 */

#ifndef MATH_MATRIX_M_VECTOR_HPP_
#define MATH_MATRIX_M_VECTOR_HPP_

#include "m_matrix.hpp"

template<typename T, uint16_t columns>
class m_LineVector : public m_Matrix<T,1,columns>
{

public:
	typedef m_Matrix<T,1,columns> baseType;
	typedef m_LineVector<T,columns> myType;

	m_LineVector(const T (&data)[columns])
	:baseType()
	{
		for(uint16_t j = 0; j < columns; j++)
		{
			baseType::operator [](0)[j] = data[j];
		}
	}


	m_LineVector()
	:baseType()
	{
	}

	m_LineVector(const myType& origin)
	:baseType(static_cast<baseType>(origin))
	{
	}

	m_LineVector(const baseType& origin)
	:baseType(origin)
	{
	}

	m_LineVector(const T& value)
	:baseType(value)
	{
	}

	m_LineVector(const T& min, const T& max)
	:baseType(min,max)
	{
	}

	// Operators ----------------------------------------------------------------------------------

	// Assignment ---------------------------------------------------------------------------------
	myType& operator= (const baseType& origin)
	{
		for(uint16_t i = 0; i < origin.columns_; i++)
		{
			baseType::operator [](0)[i] = origin[0][i];
		}
		return (*this);
	}
	// --------------------------------------------------------------------------------- Assignment

	// Access -------------------------------------------------------------------------------------
	T& operator[](uint16_t column)
	{
		return baseType::operator [](0)[column];
	}

	const T& operator[](uint16_t column) const
	{
		return baseType::operator [](0)[column];
	}
	// ------------------------------------------------------------------------------------- Access

	// Cast ---------------------------------------------------------------------------------------

	operator const m_Matrix<T,1,columns>() const
	{
		return (*this);
	}

	// --------------------------------------------------------------------------------------- Cast

	// ---------------------------------------------------------------------------------- Operators

	T norm2squared () const
	{
		T sum = T(0);
		for(uint16_t i = 0; i < columns; i++)
		{
			sum += (*this)[i]*(*this)[i];
		}
		return sum;
	}



	T norm2 () const
	{
		return std::sqrt(norm2squared());
	}
};


template<typename T, uint16_t lines>
class m_ColumnVector : public m_Matrix<T,lines,1>
{

public:
	typedef m_Matrix<T,lines,1> baseType;
	typedef m_ColumnVector<T,lines> myType;

	m_ColumnVector(const T (&data)[lines])
	:baseType()
	{
		for(uint16_t i = 0; i < lines; i++)
		{
			baseType::operator [](i)[0] = data[i];
		}
	}


	m_ColumnVector()
	:baseType()
	{
	}

	m_ColumnVector(const myType& origin)
	:baseType(static_cast<baseType>(origin))
	{
	}

	m_ColumnVector(const baseType& origin)
	:baseType(origin)
	{
	}

	m_ColumnVector(const T& value)
	:baseType(value)
	{
	}

	m_ColumnVector(const T& min, const T& max)
	:baseType(min,max)
	{
	}

	// Operators ----------------------------------------------------------------------------------

	// Assignment ---------------------------------------------------------------------------------
	myType& operator= (const baseType& origin)
	{
		for(uint16_t i = 0; i < lines; i++)
		{
			baseType::operator [](i)[0] = origin[i][0];
		}
		return (*this);
	}
	// --------------------------------------------------------------------------------- Assignment

	// Access -------------------------------------------------------------------------------------
	T& operator[](uint16_t line)
	{
		return baseType::operator [](line)[0];
	}

	const T& operator[](uint16_t line) const
	{
		return baseType::operator [](line)[0];
	}
	// ------------------------------------------------------------------------------------- Access

	// Cast ---------------------------------------------------------------------------------------

	operator const m_Matrix<T,lines,1>() const
	{
		return (*this);
	}

	// --------------------------------------------------------------------------------------- Cast

	// ---------------------------------------------------------------------------------- Operators



	T norm2squared () const
	{
		T sum = T(0);
		for(uint16_t i = 0; i < lines; i++)
		{
			sum += (*this)[i]*(*this)[i];
		}
		return sum;
	}



	T norm2 () const
	{
		return std::sqrt(norm2squared());
	}


};



#endif /* MATH_MATRIX_M_VECTOR_HPP_ */
