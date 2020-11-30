#include "seidelmethodsolver.h"

Column SeidelMethodSolver::solve(const Matrix& A, const Column& b, const Column& x)
{
    Matrix alpha;
    Column beta, result = x;
    size_t size = A.size();
    for (size_t i = 0; i < size; i++) {
        beta.push_back(b[i] / A[i][i]);
      }

      for (const std::vector<double>& v : A) {
        alpha.push_back(v);
      }
      for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
          if (i != j) alpha[i][j] = -(A[i][j] / A[i][i]);
          else alpha[i][j] = 0;
        }
      }

      if (converge(alpha)) {
        int iterCounter = 0;
        double currentEps = secondVectorNorm(subtr(b, mul_Z(A, result)));
        while (currentEps > LE_EPSILON) {
          result = sum(beta, mul_Z(alpha, result));
          iterCounter++;
          currentEps = secondVectorNorm(subtr(b, mul_Z(A, result)));
        }
      }
      else; // TODO
      return result;
}
