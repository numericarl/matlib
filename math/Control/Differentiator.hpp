/*
 * PIStateSpace.hpp
 *
 *  Created on: 12.01.2018
 *      Author: Lukas
 */

#ifndef UTILS_MATH_CONTROL_DIFFERENTIATOR_HPP_
#define UTILS_MATH_CONTROL_DIFFERENTIATOR_HPP_


#include "../matrix/matrix.hpp"

template<typename T, uint32_t n, const ControlClock::duration *const& Td>
class Differentiator
{
private:

  m_ColumnVector<T,n> u_km1_;
  m_ColumnVector<T,n> y_k_;

  ControlClock::time_point nextExecutionTime_;

public:
  Differentiator()
    :u_km1_(T(0)),y_k_(m_ColumnVector<T,n>(T(0))),nextExecutionTime_(ControlClock::now())
  {

  }

  void reset (const m_ColumnVector<T,n>& u_0 = m_ColumnVector<T,n>(T(0)))
  {
    u_km1_ = u_0;
    y_k_ = m_ColumnVector<T,n>(T(0));
    nextExecutionTime_ = ControlClock::now();
  }

  ControlClock::time_point operator () (const m_ColumnVector<T,n>& u_k)
  {
    if(ControlClock::now() >= nextExecutionTime_)
    {
      T td = T(Td->count())*T(ControlClock::duration::period::num)/T(ControlClock::duration::period::den);
      y_k_ = (u_k-u_km1_)/td;
      u_km1_ = u_k;
      nextExecutionTime_ += (*Td);
    }
    return nextExecutionTime_;
  }

  operator const m_ColumnVector<T,n>& () const
  {
    return y_k_;
  }


  static const uint32_t getTd () {return Td;}
};

#endif /* UTILS_MATH_CONTROL_DIFFERENTIATOR_HPP_ */
