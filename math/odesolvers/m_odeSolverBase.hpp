/*
 * odeSolver.hpp
 *
 *  Created on: 24.02.2017
 *      Author: Lukas
 */

#ifndef CT_MATH_ODESOLVERS_M_ODESOLVERBASE_HPP_
#define CT_MATH_ODESOLVERS_M_ODESOLVERBASE_HPP_

#include <stdint.h>

#include "../matrix/matrix.hpp"

template<typename T, uint16_t SystemOrder, uint16_t InputOrder>
class m_OdeSolverBase
{
public:
	typedef m_ColumnVector<T,SystemOrder> (*rightHandSide_t) (const m_ColumnVector<T,SystemOrder>& x,const m_ColumnVector<T,InputOrder>& u, void* arg);

protected:

	rightHandSide_t rhs_;
	m_ColumnVector<T,SystemOrder> x_;
	m_ColumnVector<T,InputOrder> u_;
	void* rhsArg_;

	T Td_;

	virtual m_ColumnVector<T,SystemOrder> iterate (const m_ColumnVector<T,InputOrder>& u) const = 0;



public:

	m_OdeSolverBase(rightHandSide_t rhs, const T& Td, void* rhsArg = nullptr):
		rhs_(rhs),x_(0),u_(0),rhsArg_(rhsArg),Td_(Td)
	{

	}

	m_OdeSolverBase(rightHandSide_t rhs, const m_ColumnVector<T,SystemOrder>& x0, const m_ColumnVector<T,InputOrder>& u0, const T& Td, void* rhsArg = nullptr):
		rhs_(rhs),x_(x0),u_(u0),rhsArg_(rhsArg),Td_(Td)
	{

	}

	virtual ~m_OdeSolverBase(){};

	const m_ColumnVector<T,SystemOrder>& operator () (const m_ColumnVector<T,InputOrder>& u)
	{
		x_ = iterate(u);
		u_ = u;
		return x_;
	}

	const m_ColumnVector<T,SystemOrder>& operator () ()
	{
		return x_;
	}

	void reset (const m_ColumnVector<T,SystemOrder>& x0 = m_ColumnVector<T,SystemOrder>(0), const m_ColumnVector<T,InputOrder>& u0 = m_ColumnVector<T,InputOrder>(0))
	{
		x_ = x0;
		u_ = u0;
	}

	const T& operator[] (const uint16_t idx) const
	{
		return x_[idx];
	}
};


#endif /* CT_MATH_ODESOLVERS_M_ODESOLVERBASE_HPP_ */
