#ifndef LESYSTEMSOLVER_H
#define LESYSTEMSOLVER_H

#include "matrix.h"

constexpr double LE_EPSILON = 1e-4;

class LESystemSolver
{
public:
    virtual Column solve(const Matrix& A, const Column& b, const Column& x = Column()) = 0;

    static double determinant(const Matrix& A);
    static Column subtr(const Column& v1, const Column& v2);
    static Column mul_Z(Matrix A, Column v);
    static Column mul_R(Matrix A, Column v, const double& coeff);
    static Column sum(Column v1, Column v2);
    static double secondVectorNorm(const Column& v);
    static bool converge(const Matrix& A);
};

#endif // LESYSTEMSOLVER_H
