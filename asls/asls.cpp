//
// asls.cpp
//
// Copyright (c) 2024 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "asls.h"

const Eigen::VectorXd BackgroundEstimation_AsLS(
	const Eigen::VectorXd & y, const double lambda, const double p,
	const unsigned int maxloop, unsigned int & loop
)
{
	size_t m = y.size();

	loop = 0;
	Eigen::VectorXd w, w0, z, pv(m), npv;

	w.setOnes(m);
	w0.setZero(m);
	pv.fill(p); npv = (1 - pv.array()).matrix();

	while(loop < maxloop)
	{
		z = WhittakerSmoother(y, w, lambda, 2);

		// 重みwの更新
		w = (y.array() > z.array()).select(pv, npv);

		// 収束判定
		if(((w.array() - w0.array()).abs() < 1e-6).all())
		{
			break;
		}

		w0 = w;
		loop++;
	}

	return z;
}
