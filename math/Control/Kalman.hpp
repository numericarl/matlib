/*
 * Kalman.hpp
 *
 *  Created on: 10.01.2018
 *      Author: Lukas
 */

#ifndef APPLICATION_MIDDLEWARE_CONTROLLER_KALMAN_HPP_
#define APPLICATION_MIDDLEWARE_CONTROLLER_KALMAN_HPP_

#include "../matrix/matrix.hpp"
#include "ControlClock.hpp"

template<typename T,uint32_t n, uint32_t m, uint32_t p>
struct Kalman_Param
{
  m_Matrix<T,n,n> Phi;
  m_Matrix<T,n,m> H;
  m_Matrix<T,p,n> C;
  m_Matrix<T,n,n> Q;
  m_Matrix<T,p,p> R;
  m_Matrix<T,n,n> P_stern_0;
};


template<typename T,                              // Type for all internal calculations
uint32_t n,                                       // System order
uint32_t m,                                       // Number of inputs
uint32_t p,                                       // Number of measurements
const Kalman_Param<T,n,m,p> *const& parameter,    // Pointer to structure with kalman parameters
const ControlClock::duration *const& Td>                        // Discretisation time
class KalmanFilter
{
private:
  m_Matrix<T,n,n> P_km1_;
  m_ColumnVector<T,n> x_dach_km1_;
  bool init_;
  ControlClock::time_point nextExecutionTime_;

public:

  KalmanFilter(const m_ColumnVector<T,n>& x_dach_0 = m_ColumnVector<T,n>()):x_dach_km1_(x_dach_0),init_(true),nextExecutionTime_(ControlClock::now())
  {
  }

  void reset (const m_ColumnVector<T,n>& x_dach_0 = m_ColumnVector<T,n>())
  {
    x_dach_km1_ = x_dach_0;
    init_ = true;
    nextExecutionTime_ = ControlClock::now();
  }

  ControlClock::time_point operator () (const m_ColumnVector<T,p>& y_k,const m_ColumnVector<T,m>& u_km1)
  {
    static const m_DiagonalMatrix<T,n> E = m_DiagonalMatrix<T,n>(1.);

    if(ControlClock::now() >= nextExecutionTime_)
    {
      // Predict ----------------------------------------------------------------
      m_ColumnVector<T,n> x_stern_k = parameter->Phi*x_dach_km1_+parameter->H*u_km1;

      m_Matrix<T,n,n> P_stern_k;
      if(init_)
      {
        init_ = false;
        P_stern_k = parameter->P_stern_0;
      }
      else
      {
        P_stern_k = parameter->Phi*P_km1_*parameter->Phi.transpose()+parameter->Q;
      }
      // ---------------------------------------------------------------- Predict

      // Correct ----------------------------------------------------------------
      m_Matrix<T,n,p> K_k = P_stern_k*parameter->C.transpose()*(parameter->C*P_stern_k*parameter->C.transpose()+parameter->R).inverse();

      m_Matrix<T,n,n> P_k = (E-K_k*parameter->C)*(P_stern_k);

      m_ColumnVector<T,n> x_dach_k = x_stern_k+K_k*(y_k-parameter->C*x_stern_k);
      // ---------------------------------------------------------------- Correct

      // Store results ----------------------------------------------------------
      P_km1_ = P_k;
      x_dach_km1_ = x_dach_k;
      // ---------------------------------------------------------- Store results
      nextExecutionTime_ += (*Td);
    }
    return nextExecutionTime_;
  }

  operator const m_ColumnVector<T,n>&() const
  {
    return x_dach_km1_;
  }

  static const uint32_t getTd () {return Td;}
};





#endif /* APPLICATION_MIDDLEWARE_CONTROLLER_KALMAN_HPP_ */
