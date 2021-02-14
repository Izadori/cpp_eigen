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
const Eigen::Block<typename Derived::PlainObject>
Diff(const Eigen::MatrixBase<Derived> & m0, const int n = 1, const int dim = 0)
{
    Derived::PlainObject m = m0;
    int rows = m.rows(), columns = m.cols();

    if(dim == 1)
    {
        for(int i = 0; i < n ; i++)
        {
            int col_counts = columns - i - 1;
            m.leftCols(col_counts) = m.leftCols(col_counts) - m.block(0, 1, rows, col_counts);
        }

        return m.leftCols(columns - n);
    }
    else
    {
        for(int i = 0; i < n ; i++)
        {
            int row_counts = rows - i - 1;
            m.topRows(row_counts) = m.topRows(row_counts) - m.block(1, 0, row_counts, columns);
        }

        return m.topRows(rows - n);
    }
}

template <typename Derived>
const Eigen::Block<typename Derived::PlainObject>
Diff(const Eigen::SparseMatrixBase<Derived> & m0, const int n = 1, const int dim = 0)
{
    Derived::PlainObject m = m0;
    int rows = m.rows(), columns = m.cols();

    if(dim == 1)
    {
        for(int i = 0; i < n ; i++)
        {
            int col_counts = columns - i - 1;
            m.leftCols(col_counts) = m.leftCols(col_counts) - m.block(0, 1, rows, col_counts);
        }

        return m.leftCols(columns - n);
    }
    else
    {
        for(int i = 0; i < n ; i++)
        {
            int row_counts = rows - i - 1;
            m.topRows(row_counts) = m.topRows(row_counts) - m.block(1, 0, row_counts, columns);
        }

        return m.topRows(rows - n);
    }
}

#endif // __IZADORI_EIGEN_DIFF_H__
