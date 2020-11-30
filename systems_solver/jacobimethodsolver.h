#ifndef JACOBIMETHODSOLVER_H
#define JACOBIMETHODSOLVER_H

#include "lesystemsolver.h"

class JacobiMethodSolver : public LESystemSolver
{
public:
    Column solve(const Matrix& A, const Column& b, const Column& x) override;
};

#endif // JACOBIMETHODSOLVER_H
