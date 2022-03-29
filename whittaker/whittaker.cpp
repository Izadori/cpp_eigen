//
// whittaker.cpp
//
// Copyright (c) 2022 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "whittaker.h"

const Eigen::VectorXd WhittakerSmoother(
	const Eigen::VectorXd & y, const Eigen::VectorXd & w, const double lambda, const unsigned int s
)
{
	size_t m = y.size();

	Eigen::VectorXd z;
	Eigen::SparseMatrix<double> I, W, D;
	Eigen::SimplicialCholesky< Eigen::SparseMatrix<double> > solver;

	I.resize(m, m);
	I.setIdentity();
	D = Diff(I, s);
	D = lambda * (D.transpose() * D);
	W = w.asDiagonal();

	// W + lambda * D' * D は対称行列なので、Cholesky分解で連立方程式を解く
	solver.compute(W + D);

	assert(solver.info() == Eigen::Success);

	// (I + lambda * D' * D) * z = W * y を解く
	z = solver.solve(W * y);

	assert(solver.info() == Eigen::Success);

	return z;
}
