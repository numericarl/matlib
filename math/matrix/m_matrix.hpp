/*
 * m_matrix.hpp
 *
 *  Created on: 02.11.2016
 *      Author: Lukas
 */

#ifndef MATH_MATRIX_M_MATRIX_HPP_
#define MATH_MATRIX_M_MATRIX_HPP_


#include <stdint.h>
#include <cstring>

#include <limits>
#include <cmath>
#include <type_traits>
#include <algorithm>
#include <cstdlib>


#include "m_specialMatrix.hpp"


template<typename T, uint16_t lines, uint16_t columns>
class m_Matrix
{
public:
	typedef m_Matrix<T,lines,columns> myType;

	static const uint16_t lines_ = lines;
	static const uint16_t columns_ = columns;

	template<typename K, uint16_t llines, uint16_t lcolumns>
	friend class m_Matrix;
private:
	T data_[lines][columns];

public:

	m_Matrix(const T (&data)[lines][columns])
	{
		std::memcpy(data_,data,sizeof(data_));
	}

	m_Matrix()
	{
		std::memset(data_,0x0,sizeof(data_));
	}

	m_Matrix(const myType& origin)
	{
		std::memcpy(data_,origin.data_,sizeof(data_));
	}

	m_Matrix(const T& value)
	{
		for(uint16_t i=0; i < lines; i++)
		{
			for(uint16_t j=0; j < columns; j++)
			{
				(*this)[i][j] = value;
			}
		}
	}

	m_Matrix(const T& min, const T& max)
	{
		for(uint16_t i=0; i < lines; i++)
		{
			for(uint16_t j=0; j < columns; j++)
			{
				(*this)[i][j] = T(std::rand())/RAND_MAX*(max-min)-min;
			}
		}
	}

	static myType identity ()
	{
		static_assert(lines==columns,"Only square matrix could be initialized as identity");
		myType result;
		for(uint16_t i = 0; i < lines; i++)
		{
			result[i][i] = T(1);
		}
		return result;
	}


	void swapLines (uint16_t first, uint16_t second)
	{
		T swap;
		for(uint16_t j = 0; j < columns; j++)
		{
			swap = (*this)[first][j];
			(*this)[first][j] = (*this)[second][j];
			(*this)[second][j] = swap;
		}
	}

	void swapColumns (uint16_t first, uint16_t second)
	{
		T swap;
		for(uint16_t i = 0; i < lines; i++)
		{
			swap = (*this)[i][first];
			(*this)[i][first] = (*this)[i][second];
			(*this)[i][second] = swap;
		}
	}

	// Operators ----------------------------------------------------------------------------------

	// Access -------------------------------------------------------------------------------------
	T (&operator[](uint16_t line))[columns]
	{
		return data_[line];
	}

	const T (&operator[](uint16_t line)const)[columns]
	{
		return data_[line];
	}
	// ------------------------------------------------------------------------------------- Access

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,1,1>>::value >::type >
	explicit operator T () const
	{
		return T((*this)[0][0]);
	}

	// Arithmetic ---------------------------------------------------------------------------------


	myType& operator+= (const myType& rhs)
	{
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			for(uint16_t j = 0; j < columns; j++) // result columns
			{
				(*this)[i][j] += rhs[i][j];
			}
		}
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,lines,lines>>::value >::type >
	myType& operator+= (const m_DiagonalMatrix<T,lines>& rhs)
	{
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			(*this)[i][i] += rhs[i];
		}
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,lines,lines>>::value >::type >
	myType operator+ (const m_DiagonalMatrix<T,lines>& rhs)
	{
		myType result=*this;
		result += rhs;
		return result;
	}


	myType operator+ (const myType& rhs) const
	{
		myType result=*this;
		result += rhs;
		return result;
	}


	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,1,1>>::value >::type >
	myType& operator+= (const T& rhs)
	{
		(*this)[0][0] += rhs;
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,1,1>>::value >::type >
	T operator+ (const T& rhs) const
	{
		return (*this)[0][0]+rhs;
	}

	myType& operator-= (const myType& rhs)
	{
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			for(uint16_t j = 0; j < columns; j++) // result columns
			{
				(*this)[i][j] -= rhs[i][j];
			}
		}
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,lines,lines>>::value >::type >
	myType& operator-= (const m_DiagonalMatrix<T,lines>& rhs)
	{
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			(*this)[i][i] -= rhs[i];
		}
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,lines,lines>>::value >::type >
	myType operator- (const m_DiagonalMatrix<T,lines>& rhs)
	{
		myType result=*this;
		result += rhs;
		return result;
	}


	myType operator- (const myType& rhs) const
	{
		myType result = *this;
		result -= rhs;
		return result;
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,1,1>>::value >::type >
	myType& operator-= (const T& rhs)
	{
		(*this)[0][0] -= rhs;
		return (*this);
	}

	template<typename U = myType, typename = typename std::enable_if<std::is_same<U,m_Matrix<T,1,1>>::value >::type >
	T operator- (const T& rhs) const
	{
		return (*this)[0][0]-rhs;
	}

	myType operator+ () const
	{
		myType result(*this);
		return result;
	}

	myType operator- () const
	{
		myType result;
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			for(uint16_t j = 0; j < columns; j++) // result columns
			{
				result[i][j] = -(*this)[i][j];
			}
		}
		return result;
	}



	template<uint16_t lcolumns>
	m_Matrix<T,lines,lcolumns> operator*(const m_Matrix<T,columns,lcolumns> &rhs) const
	{
		m_Matrix<T,lines,lcolumns> result;
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			for(uint16_t j = 0; j < lcolumns; j++) // result columns
			{
				for(uint16_t k = 0; k<columns; k++) // result entry summation
				{
					result[i][j] += (*this)[i][k]*rhs[k][j];
				}
			}
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
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			for(uint16_t j = 0; j < columns; j++) // result columns
			{
				result[i][j] = (*this)[i][j] * rhs;
			}
		}
		return result;
	}

	myType operator* (const m_DiagonalMatrix<T,columns>& rhs) const
	{
		m_Matrix<T,lines,columns> result(*this);
		for(uint16_t i = 0; i < columns; i++) // result lines
		{
			for(uint16_t j = 0; j < lines; j++) // result columns
			{
				result[j][i] *= rhs[i];
			}
		}
		return result;
	}

	myType operator*= (const m_DiagonalMatrix<T,columns>& rhs)
	{
		*this = *this * rhs;
		return *this;
	}

	myType& operator*= (const T& rhs) const
	{
		*this = *this * rhs;
		return *this;
	}

	myType operator/ (const T& rhs) const
	{
		myType result;
		for(uint16_t i = 0; i < lines; i++) // result lines
		{
			for(uint16_t j = 0; j < columns; j++) // result columns
			{
				result[i][j] = (*this)[i][j] / rhs;
			}
		}
		return result;
	}

	myType& operator/= (const T& rhs) const
	{

		*this = *this / rhs;
		return *this;
	}

	// --------------------------------------------------------------------------------- Arithmetic

	// ---------------------------------------------------------------------------------- Operators


	m_Matrix<T,columns,lines> transpose () const
	{
		m_Matrix<T,columns,lines> result;
		for(uint16_t i = 0; i < lines; i++)
		{
			for(uint16_t j = 0; j < columns; j++)
			{
				result[j][i] = (*this)[i][j];
			}
		}
		return result;
	}


	myType triangle () const
	{
		m_Matrix<T,lines,columns> result = *this;

		for(uint16_t i = 0; i < std::min(lines,columns); i++)
		{
			if(std::fabs(result[i][i]) <= std::numeric_limits<T>::epsilon())
			{
				uint16_t k;
				for(k = i+1; (k < lines) && (std::fabs(result[k][i]) <= std::numeric_limits<T>::epsilon()); k++);

				if(k == lines)	// singular
					return result;

				result.swapLines(i,k);
			}
			T pivot = result[i][i];

			for(uint16_t k = i+1; k < lines; k++)
			{
				T f = result[k][i]/pivot;
				for(uint16_t j = i; j < columns; j++)
				{
					result[k][j] -= f*result[i][j];
				}
			}
		}
		return result;
	}


	myType inverse () const
	{
		static_assert(lines==columns,"Computation of inverse only for quadratic matrices");
		myType c = *this;
		myType result = myType::identity();
		// construct upper triangle
		for(uint16_t i = 0; i < lines-1; i++)
		{
			if(std::fabs(c[i][i]) <= std::numeric_limits<T>::epsilon())
			{
				uint16_t k;
				for(k = i+1; (k < lines) && (std::fabs(c[k][i]) <= std::numeric_limits<T>::epsilon()); k++);

				if(k == lines)	// singular
					return result;

				c.swapLines(i,k);
				result.swapLines(i,k);
			}
			T pivot = c[i][i];

			for(uint16_t k = i+1; k < lines; k++)
			{
				T f = c[k][i]/pivot;
				for(uint16_t j = i; j < lines; j++)
				{
					c[k][j] -= f*c[i][j];
				}
				for(uint16_t j = 0; j <= i; j++)
				{
					result[k][j] -= f*result[i][j];
				}
			}

		}
		if(std::fabs(c[lines-1][lines-1]) <= std::numeric_limits<T>::epsilon()) // singular
			return result;

		for(uint16_t i = lines-1; i>0; i--)
		{
			for(uint16_t j = 0; j < lines; j++)
			{
				result[i][j] /= c[i][i];
			}
			c[i][i] = T(1);

			for(uint16_t k = 0; k < i; k++)
			{
				T f = c[k][i];
				c[k][i] = 0;

				for(uint16_t j = 0; j < lines; j++)
				{
					result[k][j] -= result[i][j]*f;
				}
			}
		}

		for(uint16_t j = 0; j < lines; j++)
		{
			result[0][j] /= c[0][0];
		}

		return result;
	}

};



#endif /* MATH_MATRIX_M_MATRIX_HPP_ */
