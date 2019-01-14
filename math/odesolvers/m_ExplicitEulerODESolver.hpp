/*
 * m_ExplicitEulerODESolver.hpp
 *
 *  Created on: 03.11.2016
 *      Author: Lukas
 */

#ifndef MATH_ODESOLVERS_M_EEULERODESOLVER_HPP_
#define MATH_ODESOLVERS_M_EEULERODESOLVER_HPP_

#include "../matrix/matrix.hpp"
#include "m_odeSolverBase.hpp"

template<typename T, uint16_t SystemOrder, uint16_t inputOrder>
class m_ExplicitEulerODESolver : public m_OdeSolverBase<T,SystemOrder,inputOrder>
{
private:

	typedef m_OdeSolverBase<T,SystemOrder,inputOrder> baseType_t;

protected:
	virtual m_ColumnVector<T,SystemOrder> iterate (const m_ColumnVector<T,inputOrder>& u) const
	{
		// x_{n} = x_{n-1} + f(x_{n-1},u_{n-1}) \cdot Td
		return baseType_t::x_ + (baseType_t::rhs_(baseType_t::x_,baseType_t::u_,baseType_t::rhsArg_)*this->Td_)/(T(1000));
	}

public:

	m_ExplicitEulerODESolver(typename m_OdeSolverBase<T,SystemOrder,inputOrder>::rightHandSide_t rhs, const T& Td, void* rhsArg = nullptr):
		baseType_t(rhs,Td,rhsArg)
	{

	}

	m_ExplicitEulerODESolver(typename baseType_t::rightHandSide_t rhs, const m_ColumnVector<T,SystemOrder>& x0, const m_ColumnVector<T,inputOrder>& u0, const T& Td, void* rhsArg = nullptr):
		baseType_t(rhs,x0,u0,Td,rhsArg)
	{

	}

	virtual ~m_ExplicitEulerODESolver(){}



};



#endif /* MATH_ODESOLVERS_SINGLESTEPMETHODS_M_EULERODESOLVER_HPP_ */
