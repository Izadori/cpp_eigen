#include "modpoly.h"

const Eigen::VectorXd BackgroundEstimation_ModPoly(
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

		// 修正ステップ: z_i = min(z_i, baseline_i)
		z = (z.array() > baseline.array()).select(baseline, z);
	}

	return baseline;
}
