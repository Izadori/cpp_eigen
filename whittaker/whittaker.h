//
// whittaker.h
//
// Copyright (c) 2022 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_WHITTAKER_H__
#define __IZADORI_EIGEN_WHITTAKER_H__

#include <cassert>

#include "diff.h"

// Whittaker Smootherを実施する
//
// y      : 実際の観測データ
// w      : 各点に対応する重みベクトル(0 <= w <= 1)
// lambda : 平滑化のためのペナルティ係数
// s      : 差分の階数(s = 1, 2, 3)
const Eigen::VectorXd WhittakerSmoother(
	const Eigen::VectorXd & y, const Eigen::VectorXd & w, const double lambda, const unsigned int s
);

#endif // __IZADORI_EIGEN_WHITTAKER_H__
