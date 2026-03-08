//
// convolve.h
//
// Copyright (c) 2026 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_CONVOLVE_H__
#define __IZADORI_EIGEN_CONVOLVE_H__

#include <algorithm>
#include <Eigen/Eigen>

// 計算モード
enum class ConvolveMode
{
    Full, Same, Valid
};

// NumPyのconvolve()関数っぽいもの
//
// v1  : 1次元ベクトル(VectorX<Scalar>またはRowVectorX<Scalar>)
// v2  : 1次元ベクトル(VectorX<Scalar>またはRowVectorX<Scalar>)
// mode: 計算モード(Full, Same, Valid)
template <typename Derived1, typename Derived2>
const typename Derived1::PlainObject
Convolve(
    const Eigen::MatrixBase<Derived1> & v1,
    const Eigen::MatrixBase<Derived2> & v2,
    const ConvolveMode mode = ConvolveMode::Full
)
{
    // MatrixBase<Derived>で受けているが、有効なクラスはベクトルのみとする
    // それ以外はコンパイル時に弾く
    static_assert(Derived1::IsVectorAtCompileTime, "Error: v1 is not vector.");
    static_assert(Derived2::IsVectorAtCompileTime, "Error: v2 is not vector.");

    int length, start_index, max_size, min_size;
    typename Derived1::PlainObject result;

    max_size = std::max(v1.size(), v2.size());
    min_size = std::min(v1.size(), v2.size());

    length = v1.size() + v2.size() - 1;
    start_index = 0;
    result = Derived1::PlainObject::Zero(length);

    for(int j = 0; j < v2.size(); j++) {
        for(int i = 0; i < v1.size(); i++) {
            result(i + j) += v1(i) * v2(j);
        }
    }

    if (mode == ConvolveMode::Valid) {
        length = max_size - min_size + 1;
        start_index = min_size - 1;
    }
    else if(mode == ConvolveMode::Same) {
        length = max_size;
        start_index = (int)(min_size / 2.0 + 0.5) - 1;
    }

    if(result.rows() == 1) {
        return result.block(0, start_index, 1, length);
    }
    else {
        return result.block(start_index, 0, length, 1);
    }
}

#endif // __IZADORI_EIGEN_CONVOLVE_H__
