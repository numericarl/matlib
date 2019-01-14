/*
 * m_specialMatrix.hpp
 *
 *  Created on: 24.11.2016
 *      Author: Lukas
 */

#ifndef CT_MATH_MATRIX_M_SPECIALMATRIX_HPP_
#define CT_MATH_MATRIX_M_SPECIALMATRIX_HPP_

#include "m_matrix.hpp"

template<typename T, uint16_t size>
class m_DiagonalMatrix
{
private:
	T data_[size];

	typedef m_DiagonalMatrix<T,size> myType;
public:

	const uint16_t size_ = size;

	m_DiagonalMatrix(const T (&data)[size])
	{
		std::memcpy(data_,data,size*sizeof(T));
	}

	m_DiagonalMatrix()
	{
		std::memset(data_,0x0,size*sizeof(T));
	}

	m_DiagonalMatrix(const T& value)
	{
		for(uint16_t i = 0; i < size; i++)
			data_[i] = value;
	}

	const T& operator[] (uint16_t idx) const
	{
		return data_[idx<size?idx:size-1];
	}

	T& operator[] (uint16_t idx)
	{
		return data_[idx<size?idx:size-1];
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_DiagonalMatrix<T,1>>::value >::type >
	explicit operator T () const
	{
		return T((*this)[0][0]);
	}


	// Arithmetic ---------------------------------------------------------------------------------


	myType& operator+= (const myType& rhs)
	{
		for(uint16_t i = 0; i < size; i++) // result lines
		{
			this->operator [](i) += rhs[i];
		}
		return (*this);
	}

	myType operator+ (const myType& rhs) const
	{
		myType result=*this;
		result += rhs;
		return result;
	}


	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_DiagonalMatrix<T,1>>::value >::type >
	myType& operator+= (const T& rhs)
	{
		(*this)[0] += rhs;
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_DiagonalMatrix<T,1>>::value >::type >
	T operator+ (const T& rhs) const
	{
		return (*this)[0]+rhs;
	}

	myType& operator-= (const myType& rhs)
	{
		for(uint16_t i = 0; i < size; i++) // result lines
		{
			this->operator [](i) -= rhs[i];
		}
		return (*this);
	}

	myType operator- (const myType& rhs) const
	{
		myType result=*this;
		result -= rhs;
		return result;
	}


	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_DiagonalMatrix<T,1>>::value >::type >
	myType& operator-= (const T& rhs)
	{
		(*this)[0] -= rhs;
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_DiagonalMatrix<T,1>>::value >::type >
	T operator- (const T& rhs) const
	{
		return (*this)[0]-rhs;
	}

	myType operator+ () const
	{
		myType result(*this);
		return result;
	}

	myType operator- () const
	{
		myType result;
		for(uint16_t i = 0; i < size; i++) // result lines
		{
			result[i] = -(*this)[i];
		}
		return result;
	}


	myType operator*(const myType &rhs) const
	{
		myType result;
		for(uint16_t i = 0; i < size; i++) // result lines
		{
			result[i] = (*this)[i]*rhs[i];
		}
		return result;
	}

	myType& operator*=(const myType &rhs) const
	{
		*this = *this * rhs;
		return *this;
	}

	myType operator* (const T& rhs) const
	{
		myType result;
		for(uint16_t i = 0; i < size; i++) // result lines
		{
			result[i] = (*this)[i]*rhs;
		}
		return result;
	}

	myType& operator*= (const T& rhs) const
	{
		*this = *this * rhs;
		return *this;
	}

	myType operator/ (const T& rhs) const
	{
		myType result;
		for(uint16_t i = 0; i < size; i++) // result lines
		{
			result[i] = (*this)[i]/rhs;
		}
		return result;
	}

	myType& operator/= (const T& rhs) const
	{

		*this = *this / rhs;
		return *this;
	}

	// --------------------------------------------------------------------------------- Arithmetic


	virtual myType inverse () const
	{
		myType result;
		for(uint16_t i = 0; i < size; i++)
		{
			if((*this)[i] < std::numeric_limits<T>::epsilon())
				result[i] = 0;
			else
				result[i] = T(1)/(*this)[i];
		}
		return result;
	}

};







#endif /* CT_MATH_MATRIX_M_SPECIALMATRIX_HPP_ */
