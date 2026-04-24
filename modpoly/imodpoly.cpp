#include "imodpoly.h"

const Eigen::VectorXd BackgroundEstimation_IModPoly(
	const Eigen::VectorXd & y, const int order, const int max_loop
)
{
	int n = y.size();
	Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(n, 0, 1);
	Eigen::VectorXd z = y;
	Eigen::VectorXd baseline(n);

	// ヴァンデルモンド行列の構築
	Eigen::MatrixXd vandermonde(n, order + 1);
	for (int i = 0; i < n; i++) {
		double val = 1.0;
		for (int j = 0; j <= order; j++) {
			vandermonde(i, j) = val;
			val *= x(i);
		}
	}

	for (int loop = 0; loop < max_loop; loop++) {
		// 最小二乗法で多項式係数を算出
		Eigen::VectorXd coeff = vandermonde.colPivHouseholderQr().solve(z);

		// 多項式（ベースライン）の評価
		baseline = vandermonde * coeff;

		// 残差の標準偏差を計算
		Eigen::VectorXd residual = y - baseline;
		double mean = residual.mean();
		double sd = std::sqrt((residual.array() - mean).square().sum() / n);

		// 修正ステップ: y_i > baseline_i + sd の点のみ置き換え
		z = (z.array() > (baseline.array() + sd)).select(baseline, z);
	}

	return baseline;
}
