#ifndef LESYSTEMSOLVER_H
#define LESYSTEMSOLVER_H

#include "matrix.h"

class LESystemSolver
{
public:
    LESystemSolver() = default;
    virtual ~LESystemSolver() = default;

    virtual Column solve(const Matrix& A,
                         const Column& b,
                         const Column& x = Column(),
                         double epsilon = 0) = 0;
    virtual bool needApproximation() = 0;
    bool converge(const Column& xk, const Column& xkp, double eps);
    bool diagonal(const Matrix& a);
    static int countNonzeroRows(const Matrix& A);
    static bool hasZerosDiagonal(const Matrix& A);
    static Matrix doGaussElimination(Matrix A);
    static int rank(const Matrix& A);
    static double determinant(const Matrix& A);
    static Column mul_R(Matrix A, Column v, const double& coeff);
    static double secondVectorNorm(const Column& v);
};

#endif // LESYSTEMSOLVER_H
