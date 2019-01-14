/*
 * m_nelderMeade.hpp
 *
 *  Created on: 17.11.2018
 *      Author: Lukas
 */

#ifndef CT_MATH_OPTIMIZER_M_NELDERMEAD_HPP_
#define CT_MATH_OPTIMIZER_M_NELDERMEAD_HPP_

#include <stdint.h>
#include <functional>
#include "../matrix/matrix.hpp"

enum class eNelderMeadResults_t
{
	OPTIMUM_REACHED = 1,
	MAX_ITER_REACHED = -1,
	NO_FEASABLE_SOLUTION = -2,
	MAYBE_LOCAL_MINIMUM = -3
};


template<typename T, uint32_t N>
struct m_NelderMeadResult
{
	m_ColumnVector<T,N> x_opt;
	T f_opt;
	uint32_t iter;
	eNelderMeadResults_t result;
};


template<typename T, uint32_t N>
m_NelderMeadResult<T,N> m_nelderMead (std::function<T(const m_ColumnVector<T,N>&)> costFunction,
										const m_ColumnVector<T,N> (&x0)[N], const T& tolerance,
										uint64_t maxIter = 1000)
{
	static constexpr T alpha = 0.9, gamma = 4, beta = T(2)/T(3), sigma = T(2)/T(3);

	struct testpoint
	{
		m_ColumnVector<T,N> x_test;
		T f_test;
	};



	testpoint test[N+1];
	testpoint* best = nullptr;
	testpoint* worst = nullptr;
	testpoint* secondWorst = nullptr;

	std::function<void(testpoint&)> insertNewTestpoint = [&best,&worst,&secondWorst](testpoint& testp)
			{
				if(worst==nullptr||best==nullptr||secondWorst==nullptr)
				{
					best = &testp;
					worst = &testp;
					secondWorst = &testp;
					return;
				}
				if(testp.f_test < best->f_test)
				{
					best = &testp;
				}
				else if(testp.f_test > worst->f_test)
				{
					worst = &testp;
				}
				else if(testp.f_test > secondWorst->f_test)
				{
					secondWorst = &testp;
				}
			};

	std::function<void(testpoint&)> replaceWorstTestpoint = [&test,&best,&worst,&secondWorst,insertNewTestpoint](testpoint& testp)
			{
				worst->f_test = testp.f_test;
				worst->x_test = testp.x_test;
				worst=nullptr;
				best=nullptr;
				secondWorst=nullptr;
				for(uint32_t i = 0; i < N+1; i++)
				{
					insertNewTestpoint(test[i]);
				}

			};
	std::function<void()> resortTestpoints = [&test,&best,&worst,&secondWorst,insertNewTestpoint]()
			{
				worst=nullptr;
				best=nullptr;
				secondWorst=nullptr;
				for(uint32_t i = 0; i < N+1; i++)
				{
					insertNewTestpoint(test[i]);
				}

			};

	std::function<bool()> isConverged = [&test,&best,&tolerance]()->bool
			{

				T delta = best->x_test.norm2squared();
				T dist_max = 0;

				for(uint32_t i = 0; i < N+1; i++)
				{
					if(&(test[i]) != best)
					{
						T dist = static_cast<m_ColumnVector<T,N>>(test[i].x_test-best->x_test).norm2squared();
						dist_max = dist_max<dist?dist:dist_max;
					}
				}

				return dist_max/delta>(tolerance*tolerance)? false:true;
			};
	for(uint32_t i = 0; i < N; i++)
	{
		for(uint32_t j = 0; j < N; j++)
		{
			test[i].x_test[j] = x0[i][j];
		}
		test[i].f_test = costFunction(test[i].x_test);

		insertNewTestpoint(test[i]);
	}
	for(uint32_t j = 0; j < N; j++)
	{
		test[N].x_test[j] = x0[j][j];
	}
	test[N].f_test = costFunction(test[N].x_test);

	insertNewTestpoint(test[N]);

	uint32_t iter;
	for(iter = 0; (iter < maxIter) && !isConverged(); iter++)
	{
		m_ColumnVector<T,N> m;
		for(uint32_t i = 0; i < N+1; i++)
		{
			m += test[i].x_test;
		}
		m -= worst->x_test;

		m = m/N;

		testpoint r;
		r.x_test = (T(1)+alpha)*m-alpha*worst->x_test;
		r.f_test = costFunction(r.x_test);
		if(r.f_test<best->f_test)
		{
			testpoint e;
			e.x_test = (T(1)+gamma)*m-gamma*worst->x_test;
			e.f_test = costFunction(e.x_test);
			replaceWorstTestpoint(r.f_test<e.f_test?r:e);
			continue;
		}
		if(r.f_test<secondWorst->f_test)
		{
			replaceWorstTestpoint(r);
			continue;
		}
		testpoint* h = r.f_test<worst->f_test?&r:worst;
		testpoint c;
		c.x_test = beta*m+(T(1)-beta)*h->x_test;
		c.f_test = costFunction(c.x_test);
		if(c.f_test<worst->f_test)
		{
			replaceWorstTestpoint(c);
			continue;
		}
		for(uint32_t i = 0; i<N+1;i++)
		{
			if(best!=&test[i])
			{
				test[i].x_test = sigma*best->x_test+(T(1)-sigma)*test[i].x_test;
				test[i].f_test = costFunction(test[i].x_test);
			}
		}
		resortTestpoints();
	}

	m_NelderMeadResult<T,N> res;
	res.iter = iter;
	res.x_opt = best->x_test;
	res.result = isConverged()?eNelderMeadResults_t::OPTIMUM_REACHED:(res.iter==maxIter?eNelderMeadResults_t::MAX_ITER_REACHED:eNelderMeadResults_t::MAYBE_LOCAL_MINIMUM);
	res.f_opt = best->f_test;
	return res;
}



#endif /* CT_MATH_OPTIMIZER_M_NELDERMEAD_HPP_ */
