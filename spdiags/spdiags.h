//
// convolve.h
//
// Copyright (c) 2026 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_SPDIAGS_H__
#define __IZADORI_EIGEN_SPDIAGS_H__

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <Eigen/Eigen>

// SciPyのspdiags()関数っぽいもの
//
// data : 対角に配置する要素を列に持つ行列
// diags: dataの各列について配置する位置を指定します。
//        (0: 対角、正の値: 上三角側、負の値：下三角側)
// m    : 出力する疎行列の行数（省略時または負の値はdataに一致）
// n    : 出力する疎行列の列数（省略時または負の値はdataに一致）
template <typename Derived>
Eigen::SparseMatrix<typename Derived::PlainObject::Scalar>
Spdiags(const Eigen::MatrixBase<Derived> & data, const Eigen::VectorXi & diags, const int m = -1, const int n = -1)
{
	using Scalar = typename Derived::PlainObject::Scalar;
	using T = Eigen::Triplet<Scalar>;

	if(diags.size() > data.rows()) {
		throw std::invalid_argument("diags size is larger than rows of data.");
	}

	int row_size, column_size;
	Eigen::SparseMatrix<Scalar> a;
	std::vector<T> triplets;

	row_size = (m <= 0) ? (int)data.rows() : m;
	column_size = (n <= 0) ? (int)data.cols() : n;

	a.resize(row_size, column_size);
	triplets.resize(row_size * diags.size());

	for (int k = 0; k < diags.size(); k++) {
		int start_index = std::max(0, diags(k));
		int end_index = std::min((int)data.cols(), column_size);

		for(int i = start_index; i < end_index; i++) {
			if(i - diags(k) < row_size && i < column_size) {
				triplets.push_back(T(i - diags(k), i, data(k, i)));
			}
		}
	}

	a.setFromTriplets(triplets.begin(), triplets.end());

	return a;
}

// SciPyのspdiags()関数っぽいもの（diagsがstd::vector<int>のバージョン）
//
// data : 対角に配置する要素を列に持つ行列
// diags: dataの各列について配置する位置を指定します。
//        (0: 対角、正の値: 上三角側、負の値：下三角側)
// m    : 出力する疎行列の行数（省略時または負の値はdataに一致）
// n    : 出力する疎行列の列数（省略時または負の値はdataに一致）
template <typename Derived>
inline Eigen::SparseMatrix<typename Derived::PlainObject::Scalar>
Spdiags(const Eigen::MatrixBase<Derived> & data, const std::vector<int> & diags, const int m = -1, const int n = -1)
{
	return Spdiags(
		data,
		Eigen::Map<Eigen::VectorXi>((int *)diags.data(), diags.size()),
		m, n
	);
}

// SciPyのspdiags()関数っぽいもの（diagsがstd::initializer_list<int>のバージョン）
//
// data : 対角に配置する要素を列に持つ行列
// diags: dataの各列について配置する位置を指定します。
//        (0: 対角、正の値: 上三角側、負の値：下三角側)
// m    : 出力する疎行列の行数（省略時または負の値はdataに一致）
// n    : 出力する疎行列の列数（省略時または負の値はdataに一致）
template <typename Derived>
inline Eigen::SparseMatrix<typename Derived::PlainObject::Scalar>
Spdiags(const Eigen::MatrixBase<Derived> & data, const std::initializer_list<int> & diags, const int m = -1, const int n = -1)
{
	return Spdiags(data, std::vector<int>{diags}, m, n);
}

#endif // __IZADORI_EIGEN_SPDIAGS_H__
