#ifndef UPPERRELAXATIONMETHODSOLVER_H
#define UPPERRELAXATIONMETHODSOLVER_H

#include <random>
#include <ctime>
#include "lesystemsolver.h"

class UpperRelaxationMethodSolver : public LESystemSolver
{
public:
    Column solve(const Matrix& A, const Column& b, const Column& x = Column()) override;
};

const Column operator*(const double& left, const Column& right);

#endif // UPPERRELAXATIONMETHODSOLVER_H
