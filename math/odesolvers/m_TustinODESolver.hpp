/*
 * m_TustinODESolver.hpp
 *
 *  Created on: 03.11.2016
 *      Author: Lukas
 */

#ifndef MATH_ODESOLVERS_M_TUSTINODESOLVER_HPP_
#define MATH_ODESOLVERS_M_TUSTINODESOLVER_HPP_

#include "../matrix/matrix.hpp"
#include "m_odeSolverBase.hpp"

template<typename T, uint16_t SystemOrder, uint16_t InputOrder>
class m_TustinODESolver : public m_OdeSolverBase<T,SystemOrder,InputOrder>
{
private:

	typedef m_OdeSolverBase<T,SystemOrder,InputOrder> baseType_t;

protected:
	virtual m_ColumnVector<T,SystemOrder> iterate (const m_ColumnVector<T,InputOrder>& u) const
	{
		// Estimate \hat{x}_{n} = x_{n-1} + f(x_{n-1},u_{n-1}) \cdot Td
		m_ColumnVector<T,SystemOrder> x_n_hat = baseType_t::x_ + (baseType_t::rhs_(baseType_t::x_,baseType_t::u_,baseType_t::rhsArg_)*this->Td_);

		// x_{n} = x_{n-1} + \frac{f(\hat{x}_{n},u_{n})+x_{n-1}}{2} \cdot Td
		return baseType_t::x_ + (baseType_t::rhs_(baseType_t::x_,baseType_t::u_,baseType_t::rhsArg_)+baseType_t::rhs_(x_n_hat,u,baseType_t::rhsArg_))*this->Td_/T(2);
	}

public:

	m_TustinODESolver(typename m_OdeSolverBase<T,SystemOrder,InputOrder>::rightHandSide_t rhs, const T& Td, void* rhsArg = nullptr):
		baseType_t(rhs,Td,rhsArg)
	{

	}
	m_TustinODESolver(typename baseType_t::rightHandSide_t rhs, const m_ColumnVector<T,SystemOrder>& x0, const m_ColumnVector<T,InputOrder>& u0, const T& Td, void* rhsArg = nullptr):
		baseType_t(rhs,x0,u0,Td,rhsArg)
	{

	}


	virtual ~m_TustinODESolver(){}




};



#endif /* MATH_ODESOLVERS_SINGLESTEPMETHODS_M_EULERODESOLVER_HPP_ */
