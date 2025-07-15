//
// arpls.cpp
//
// Copyright (c) 2025 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include <limits>
#include "arpls.h"

const Eigen::VectorXd BackgroundEstimation_arPLS(
	const Eigen::VectorXd & y, const double lambda, const double ratio,
	const unsigned int maxloop, unsigned int & loop
)
{
	size_t m = y.size();

	loop = 0;
	Eigen::VectorXd w(m), wt, z, d, tmp;
	double mean, sd;
	Eigen::Index ct;

	// オーバーフロー対策
	const double overflow = std::log(std::numeric_limits<double>::max()) / 2;

	w.setOnes(m);

	while (loop < maxloop) {
		z = WhittakerSmoother(y, w, lambda, 2);

		d = y - z;

		ct = (d.array() < 0).count();
		mean = (d.array() < 0).select(d, 0).sum() / ct;
		sd = std::sqrt((d.array() < 0).select((d.array() - mean).matrix(), 0).squaredNorm() / (ct - 1));

		tmp = ((d.array() + mean - 2 * sd) / sd).matrix();
		tmp = (tmp.array() >= overflow).select(0, (1.0 / (1 + (2 * tmp).array().exp())).matrix());

		// 重みwの更新
		wt = (d.array() >= 0).select(tmp, 1);

		// 収束判定
		if ((w - wt).norm() / w.norm() < ratio) {
			break;
		}

		w = wt;
		loop++;
	}

	return z;
}
