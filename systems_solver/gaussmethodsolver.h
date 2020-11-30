#ifndef GAUSSMETHOD_H
#define GAUSSMETHOD_H

#include "lesystemsolver.h"

class GaussMethodSolver : public LESystemSolver
{
public:
    Column solve(const Matrix& A, const Column& b, const Column&) override;
};

#endif // GAUSSMETHOD_H
