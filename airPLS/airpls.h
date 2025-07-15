//
// airpls.h
//
// Copyright (c) 2025 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_AIRPLS_H__
#define __IZADORI_EIGEN_AIRPLS_H__

#include "whittaker.h"

// airPLS法によるバックグラウンド推定
//
// y       : 実際の観測データ
// lambda  : 平滑化のためのペナルティ係数
// diff    : 差分の次数(1～3)
// maxloop : 最大繰返し回数
// loop    : 実際の繰返し回数（戻り値）
const Eigen::VectorXd BackgroundEstimation_airPLS(
	const Eigen::VectorXd & y, const double lambda, const unsigned int diff,
	const unsigned int maxloop, unsigned int & loop
);

#endif // __IZADORI_EIGEN_AIRPLS_H__
