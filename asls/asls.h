//
// asls.h
//
// Copyright (c) 2024 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_ASLS_H__
#define __IZADORI_EIGEN_ASLS_H__

#include "whittaker.h"

// AsLS法によるバックグラウンド推定
//
// y       : 実際の観測データ
// lambda  : 平滑化のためのペナルティ係数
// p       : 重み
// maxloop : 最大繰返し回数
// loop    : 実際の繰返し回数（戻り値）
const Eigen::VectorXd BackgroundEstimation_AsLS(
	const Eigen::VectorXd & y, const double lambda, const double p,
	const unsigned int maxloop, unsigned int & loop
);

#endif // __IZADORI_EIGEN_ASLS_H__
