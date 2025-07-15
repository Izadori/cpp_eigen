//
// airpls.h
//
// Copyright (c) 2025 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_ARPLS_H__
#define __IZADORI_EIGEN_ARPLS_H__

#include "whittaker.h"

// arPLS法によるバックグラウンド推定
//
// y       : 実際の観測データ
// lambda  : 平滑化のためのペナルティ係数
// ratio   : 収束判定のしきい値
// maxloop : 最大繰返し回数
// loop    : 実際の繰返し回数（戻り値）
const Eigen::VectorXd BackgroundEstimation_arPLS(
	const Eigen::VectorXd & y, const double lambda, const double ratio,
	const unsigned int maxloop, unsigned int & loop
);

#endif // __IZADORI_EIGEN_ARPLS_H__
