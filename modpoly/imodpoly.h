#ifndef __IZADORI_EIGEN_IMODPOLY_H__
#define __IZADORI_EIGEN_IMODPOLY_H__

#include <Eigen/Eigen>

// IModPoly法によるバックグラウンド推定
//
// y        : 実際の観測データ
// order    : フィットする多項式の次数
// max_loop : 最大繰返し回数
const Eigen::VectorXd BackgroundEstimation_IModPoly(
	const Eigen::VectorXd & y, const int order, const int max_loop
);

#endif // __IZADORI_EIGEN_IMODPOLY_H__
