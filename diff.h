//
// diff.h
//
// Copyright (c) 2021 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#ifndef __IZADORI_EIGEN_DIFF_H__
#define __IZADORI_EIGEN_DIFF_H__

#include <Eigen/Eigen>

template <typename Derived>
const typename Derived::PlainObject
Diff(const Eigen::MatrixBase<Derived> & m0, const int n = 1, const int dim = 0)
{
    typename Derived::PlainObject m = m0;
    int rows = m.rows(), columns = m.cols();

    if(dim == 1){
        for(int i = 0; i < n ; i++){
            int col_counts = columns - i - 1;
            m.leftCols(col_counts) = m.block(0, 1, rows, col_counts) - m.leftCols(col_counts);
        }

        return m.leftCols(columns - n);
    }
    else{
        for(int i = 0; i < n ; i++){
            int row_counts = rows - i - 1;
            m.topRows(row_counts) = m.block(1, 0, row_counts, columns) - m.topRows(row_counts);
        }

        return m.topRows(rows - n);
    }
}

template <typename Derived>
const typename Derived::PlainObject
Diff(const Eigen::SparseMatrixBase<Derived> & m0, const int n = 1, const int dim = 0)
{
    typename Derived::PlainObject m = m0;

    if(dim == 1){
        for(int i = 0; i < n; i++){
            m = (m.rightCols(m.cols() - 1) - m.leftCols(m.cols() - 1)).eval();
        }
    }
    else{
        for(int i = 0; i < n; i++){
            m = (m.bottomRows(m.rows() - 1) - m.topRows(m.rows() - 1)).eval();
        }
    }

    return m;
}

#endif // __IZADORI_EIGEN_DIFF_H__
