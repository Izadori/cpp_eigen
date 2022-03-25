//
// diff.cpp
//
// Copyright (c) 2021 Izadori
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include <Eigen/Eigen>

template <typename Derived>
const Eigen::MatrixXd Diff(const Eigen::MatrixBase<Derived> & m, const unsigned int n = 1)
{
    Eigen::MatrixXd mr = m;

    for(unsigned int i = 0; i < n; i++){
        mr = (mr.bottomRows(mr.rows() - 1) - mr.topRows(mr.rows() - 1)).eval();
    }

    return mr;
}

template <typename Derived>
const Eigen::SparseMatrix<double> Diff(const Eigen::SparseMatrixBase<Derived> & m, const unsigned int n = 1)
{
    Eigen::SparseMatrix<double> mr = m;

    for(unsigned int i = 0; i < n; i++){
        mr = (mr.bottomRows(mr.rows() - 1) - mr.topRows(mr.rows() - 1)).eval();
    }

    return mr;
}
