//
// airpls.cpp
//
// Copyright (c) 2025 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "airpls.h"
#include <iostream>

const Eigen::VectorXd BackgroundEstimation_airPLS(
	const Eigen::VectorXd & y, const double lambda, const unsigned int diff,
	const unsigned int maxloop, unsigned int & loop
)
{
	size_t m = y.size();

	loop = 0;
	Eigen::VectorXd w(m), z, d;
	double y_abs_sum, d_sum_abs;

	w.setOnes(m);
	y_abs_sum = y.array().abs().matrix().sum();

	while (loop < maxloop)
	{
		z = WhittakerSmoother(y, w, lambda, diff);

		d = (y.array() >= z.array()).select(0, y - z);
		d_sum_abs = std::fabs(d.sum());

		// 収束判定
		if (d_sum_abs < 0.001 * y_abs_sum)
		{
			break;
		}

		// 重みwの更新
		loop++;
		w = (y.array() >= z.array()).select(0, ((loop * d.array().abs()) / d_sum_abs).exp());
		w(0) = w(w.size() - 1) = std::exp((loop * d.maxCoeff() / d_sum_abs));
	}

	return z;
}
