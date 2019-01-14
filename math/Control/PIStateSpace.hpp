/*
 * PIStateSpace.hpp
 *
 *  Created on: 12.01.2018
 *      Author: Lukas
 */

#ifndef UTILS_MATH_CONTROL_PISTATESPACE_HPP_
#define UTILS_MATH_CONTROL_PISTATESPACE_HPP_


#include "../matrix/matrix.hpp"

template<typename T,uint32_t n>
struct PIStateSpace_Param
{
  m_LineVector<T,n> C;
  m_LineVector<T,n> K;
  T K_i;
  T K_p;

  T u_min;
  T u_max;
};

template<typename T, uint32_t n, const PIStateSpace_Param<T,n> *const& parameter, const ControlClock::duration *const& Td>
class PIStateSpace
{
private:
  T u_i_km1_;
  T e_km1_;

  T u_k_;
  T aw_i_km1_;

  ControlClock::time_point nextExecutionTime_;;

public:
  PIStateSpace(const T& u_i_0 = T(0), const T& e_0 = T(0))
    :u_i_km1_(u_i_0),e_km1_(e_0),u_k_(0),aw_i_km1_(0),nextExecutionTime_(ControlClock::now())
  {

  }

  void reset (const T& u_i_0 = T(0), const T& e_0 = T(0))
  {
    aw_i_km1_ = T(0);
    u_i_km1_ = u_i_0;
    e_km1_ = e_0;
    nextExecutionTime_ = ControlClock::now();
  }

  ControlClock::time_point operator () (const m_ColumnVector<T,n>& x, const T& r)
  {
    if(ControlClock::now() >= nextExecutionTime_)
    {
      T td = T(Td->count())*T(ControlClock::duration::period::num)/T(ControlClock::duration::period::den);
      u_i_km1_ = (u_i_km1_+(e_km1_*parameter->K_i-aw_i_km1_)*td);

      e_km1_ = r-T(parameter->C*x);

      u_k_ = -u_i_km1_ -T(parameter->K*x) - e_km1_*parameter->K_p;

      if (u_k_ > parameter->u_max)
      {
        aw_i_km1_ = u_k_ - parameter->u_max;
      }
      else if(u_k_ < parameter->u_min)
      {
        aw_i_km1_ = u_k_ - parameter->u_min;
      }
      else
      {
        aw_i_km1_ = 0;
      }
      nextExecutionTime_ += (*Td);
    }
    return nextExecutionTime_;
  }

  operator const T& () const
  {
    return u_k_;
  }


  static const uint32_t getTd () {return Td;}
};

#endif /* UTILS_MATH_CONTROL_PISTATESPACE_HPP_ */
