#ifndef SEIDELMETHODSOLVER_H
#define SEIDELMETHODSOLVER_H

#include "lesystemsolver.h"

class SeidelMethodSolver : public LESystemSolver
{
public:
    Column solve(const Matrix& A, const Column& b, const Column& x = Column()) override;
};

#endif // SEIDELMETHODSOLVER_H
