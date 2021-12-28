//
// marquardt.h
//
// Copyright (c) 2021 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_MARQUARDT_H__
#define __IZADORI_EIGEN_MARQUARDT_H__

#include <Eigen/Eigen>

//---------------------------------------------
// 関数fのJacobianを計算する
//---------------------------------------------
template <typename Grad>
Eigen::MatrixXd CalcJacobian(
    Grad & g, Eigen::VectorXd & a, Eigen::VectorXd & x
)
{
    Eigen::MatrixXd ret;

    ret.resize(x.size(), a.size());

    for (unsigned int i = 0; i < x.size(); i++){
        auto grad = g(a, x(i));
        for(unsigned int j = 0; j < a.size(); j++){
            ret.row(i) = grad;
        }
    }

    return ret;
}

//---------------------------------------------
// Levenberg-Marquardt法の計算
//---------------------------------------------
template <typename Func, typename Grad>
bool LevenbergMarquardt(
    Func & f, Grad & g, Eigen::VectorXd & a, Eigen::VectorXd & x, Eigen::VectorXd & y,
    const double eps, const unsigned int max_loop
)
{
    // ループ回数
    unsigned int loop = 0;

	// ステップ数の初期値
	double alpha = 1;
	// ステップ数の係数
	double c = 10;

    // 残差二乗和
    double s_new, s_old = 0;

    while(true){
        // 関数fのJacobianの計算
        Eigen::MatrixXd jac = CalcJacobian(g, a, x);

        // 関数fの計算
        Eigen::VectorXd fx(x.size());

        for(unsigned int i = 0; i < x.size(); i++){
            fx(i) = f(a, x(i));
        }

        // 残差ベクトルrの計算
        Eigen::VectorXd r = fx - y;
        // 残差二乗和の計算
        s_new = r.squaredNorm();

        // 収束判定
        if(std::fabs(s_new - s_old) < std::fabs(eps)){
            break;
        }

        alpha *= (s_old > s_new) ? (1 / c) : c;
        s_old = s_new;

        //---------------------------
        // パラメータaの更新
        //---------------------------

        // Δaの計算
        Eigen::MatrixXd h = jac.transpose() * jac + alpha * Eigen::MatrixXd::Identity(x.size(), x.size());
        Eigen::VectorXd delta_a = h.ldlt().solve(-jac.transpose() * r);

        // パラメータaの更新
        a += delta_a;

        // ループ回数のチェック
        if(loop >= max_loop){
            break;
        }

        loop++;
    }

    return (loop < max_loop);
}

#endif // __IZADORI_EIGEN_MARQUARDT_H__
