#include "seidelmethodsolver.h"

Column SeidelMethodSolver::solve(const Matrix& A, const Column& b, const Column& x, double epsilon)
{
    if(hasZerosDiagonal(A))
        throw std::runtime_error("Матрица имеет по крайней мере 1 ноль по диагонали.");
    if (!diagonalPredominant(A))
        throw std::runtime_error("Матрица не обладает свойством диагонального преобладания.");
    Column x_curr = x;
    Column x_prev;
    size_t size = A.size();
    do
    {
        x_prev = x_curr;
        for (size_t i = 0; i < size; i++)
        {
            double var = 0;
            for (size_t j = 0; j < i; j++)
                var += A[i][j] * x_curr[j];
            for (size_t j = i + 1; j < size; j++)
                var += A[i][j] * x_prev[j];
            x_curr[i] = (b[i] - var) / A[i][i];
        }
    } while (!converge(x_curr, x_prev, epsilon));
    return x_curr;
}

bool SeidelMethodSolver::needApproximation()
{
    return true;
}
