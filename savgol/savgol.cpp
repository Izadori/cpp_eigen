//
// savgol.cpp
//
// Copyright (c) 2021 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "savgol.h"

//
// Savitzky-Golay法の係数を求める
//
const Eigen::RowVectorXd CalcSavGolCoeff(const size_t window, const unsigned int polyorder, const unsigned derive)
{
    assert(window % 2 == 1);
    assert(window > polyorder && window > derive && polyorder > derive);

    int n = (int)window / 2;
    double p = 1;

    // 行列Xの生成
    Eigen::VectorXd v = Eigen::VectorXd::LinSpaced(window, -n, n);
    Eigen::MatrixXd x = Eigen::MatrixXd::Ones(window, polyorder + 1);

    for(unsigned int i = 1; i <= polyorder; i++){
        x.col(i) = (x.col(i - 1).array() * v.array()).matrix();
    }

    // (X^T * X)^-1 * X^Tを計算する
    Eigen::MatrixXd coeff_mat = (x.transpose() * x).inverse() * x.transpose();

    // 階乗の計算
    if(derive > 0){
        for(unsigned int i = 1; i <= derive; i++){
            p *= i;
        }
    }

    return coeff_mat.row(derive) * p;
}
