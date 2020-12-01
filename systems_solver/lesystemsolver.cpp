#include "lesystemsolver.h"
#include <iostream>

bool LESystemSolver::converge(const Column& xk, const Column& xkp, double eps)
{
    double norm = 0;
    size_t size = xk.size();
    for (size_t i = 0; i < size; i++)
        norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
    return (sqrt(norm) < eps);
}

bool LESystemSolver::diagonal(const Matrix& a)
{
    size_t size = a.size();
    double sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum = 0;
        for (size_t j = 0; j < size; j++)
            sum += abs(a[i][j]);
        sum -= abs(a[i][i]);
        if (sum > a[i][i]) {
            return false;
        }
    }
    return true;
}

bool LESystemSolver::hasZerosDiagonal(const Matrix& A) {
    size_t size = A.size();
    for(size_t i = 0; i < size; i++) {
        if(A[i][i] == 0)
            return true;
    }
    return false;
}

int LESystemSolver::countNonzeroRows(const Matrix &A)
{
    int k = 0;
    for (const auto& row : A)
    {
        for (const auto& el: row)
        {
            if (el != 0)
            {
                k++;
                break;
            }
        }
    }
    return k;
}

Matrix LESystemSolver::doGaussElimination(Matrix A)
{
    // This method was not tested with non-square matrices!
    size_t n = A[0].size();
    for (size_t j = 0; j < n; j++)
    {
        double alfa = 0;
        for (size_t i = j + 1; i < n; i++)
        {
            alfa = A[i][j] / A[j][j];
            for (size_t k = j; k < n; k++)
            {
                A[i][k] -= alfa * A[j][k];
            }
        }
    }
    return A;
}

int LESystemSolver::rank(const Matrix &A)
{
    auto gauss = doGaussElimination(A);
    return countNonzeroRows(gauss);
}

double LESystemSolver::determinant(const Matrix& A) {
    size_t size = A.size();
    if (size == 1)
        return A[0][0];
    if (size == 2)
        return  A[0][0] * A[1][1] - A[1][0] * A[0][1];
    double det = 0;
    for (size_t i = 0; i < size; i++) {
        Matrix tmp = A;
        tmp.erase(tmp.begin());
        for (size_t j = 0; j < tmp.size(); j++) {
            tmp[j].erase(tmp[j].begin() + i);
        }
          det += pow(-1, static_cast<int>(i) + 2) * A[0][i] * determinant(tmp);
        }
    return det;
}

Column LESystemSolver::mul_R(Matrix A, Column v, const double& coeff) {
  size_t size = v.size();
  Column res(size);
  for (size_t i = 0; i < size; i++) {
    double sum = 0;
    for (size_t j = 0; j < size; j++) {
      sum += A[i][j] * v[j];
    }
    res[i] = coeff * sum;
  }
  return res;
}

double LESystemSolver::secondVectorNorm(const Column& v) {
  double tmpSum = 0;
  for (double val : v) {
    tmpSum += pow(val, 2);
  }
  return sqrt(tmpSum);
}
