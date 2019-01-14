/*
 * ControlClock.hpp
 *
 *  Created on: 12.01.2018
 *      Author: Lukas
 */

#ifndef UTILS_MATH_CONTROL_CONTROLCLOCK_HPP_
#define UTILS_MATH_CONTROL_CONTROLCLOCK_HPP_

#include <stdint.h>
#include <ratio>
#include <chrono>

#ifdef USE_RTOS_SYSTICK
#include "FreeRTOS.h"
#endif



class ControlClock
{
public:
    typedef int64_t rep;
  #ifdef USE_RTOS_SYSTICK
    typedef std::ratio<1, configTICK_RATE_HZ> period;
  #endif
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<ControlClock> time_point;

    static constexpr bool is_steady = true;

  #ifdef USE_RTOS_SYSTICK
    static time_point now()
    {
        return time_point(duration(xTaskGetTickCount()));
    }
  #endif
};

#endif /* UTILS_MATH_CONTROL_CONTROLCLOCK_HPP_ */
