//
// savgol.h
//
// Copyright (c) 2021 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_SAVGOL_H__
#define __IZADORI_EIGEN_SAVGOL_H__

#include <cassert>
#include <Eigen/Dense>

// Savitzky-Golay法の係数を求める
//
// window   : データ点数（2N+1点）
// polyorder: 近似多項式の次数
// derive   : 微分の次数
const Eigen::RowVectorXd CalcSavGolCoeff(const size_t window, const unsigned int polyorder, const unsigned derive);

#endif // __IZADORI_EIGEN_SAVGOL_H__
