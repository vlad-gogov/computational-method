#ifndef SIMPLEITERATIONMETHODSOLVER_H
#define SIMPLEITERATIONMETHODSOLVER_H

#include "lesystemsolver.h"

class SimpleIterationMethodSolver : public LESystemSolver
{
public:
    Column solve(const Matrix& A, const Column& b, const Column& x = Column()) override;
};

#endif // SIMPLEITERATIONMETHODSOLVER_H
