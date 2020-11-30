#ifndef KRAMERMETHODSOLVER_H
#define KRAMERMETHODSOLVER_H

#include "lesystemsolver.h"

class KramerMethodSolver : public LESystemSolver
{
public:
    Column solve(const Matrix& A, const Column& b, const Column&) override;
};

#endif // KRAMERMETHODSOLVER_H
