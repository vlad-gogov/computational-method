#include "Spline.h"

Spline::Spline(const std::vector<double>& x, const std::vector<double>& y) : x(x) {
    if (x.size() != y.size())
        throw "Invalid data";
    countPoint = x.size();
    N = countPoint - 1;

    std::vector<double> h(N);
    for (size_t k = 0; k < N; k++) {
        h[k] = x[k + 1] - x[k];
        if (h[k] <= 0)
            throw "Invalid data";
    }

    std::vector<double> mainDiagonal(N - 1); // Главная диагональ матрицы
    std::vector<double> aboveDiagonal(N - 2); // Диагональ, лежащая над главной
    std::vector<double> belowDiagonal(N - 2); // Диагональ, лежащая под главной
    std::vector<double> f(N - 1);

    for (size_t k = 0; k < N - 1; k++)
    {
        f[k] = 6 * (h[k] * (y[k + 2] - y[k + 1]) - h[k + 1] * (y[k + 1] - y[k])) / (h[k + 1] * h[k] * (h[k + 1] + h[k]));
        mainDiagonal[k] = 2;
    }

    for (size_t k = 0; k < N - 2; k++)
    {
        aboveDiagonal[k] = h[k + 2] / (h[k + 1] + h[k + 2]);
        belowDiagonal[k] = h[k + 1] / (h[k + 1] + h[k + 2]);
    }

    std::vector<double> p(N - 2), q(N - 1);

    for (size_t k = 0; k < N - 2; k++)
    {
        if (k != 0) {
            double temp = belowDiagonal[k - 1] * p[k - 1] + mainDiagonal[k];
            p[k] = -aboveDiagonal[k] / temp;
        }
        else {
            p[k] = -aboveDiagonal[k] / mainDiagonal[k];
        }
    }

    for (size_t k = 0; k < N - 1; k++)
    {
        if (k != 0) {
            double temp = belowDiagonal[k - 1] * p[k - 1] + mainDiagonal[k];
            q[k] = (f[k] - belowDiagonal[k - 1] * q[k - 1]) / temp;
        }
        else
            q[k] = f[k] / mainDiagonal[k];
    }

    this->a.resize(countPoint);
    this->b.resize(countPoint);
    this->c.resize(countPoint);
    this->d.resize(countPoint);

    c[0] = c[N] = 0.0f;
    c[N - 1] = q[N - 2];

    for (size_t k = N - 2; k > 0; k--)
    {
        c[k] = p[k - 1] * c[k + 1] + q[k - 1];
    }

    for (size_t k = 0; k < N + 1; k++)
    {
        if(k != 0)
            d[k] = c[k] - c[k - 1];
        else
            d[k] = c[k + 1] / h[k];
    }

    for (size_t k = 0; k < N + 1; k++)
    {
        if(k != 0)
            b[k] = c[k] * h[k - 1] / 3 + c[k - 1] * h[k - 1] / 6 + ((y[k] - y[k - 1]) / h[k - 1]);
        else
            b[k] = c[k + 1] * h[k] / 3 + ((y[k + 1] - y[k]) / h[k]);
    }

    for (size_t k = 0; k < N + 1; k++) {
        a[k] = y[k];
    }
}

double Spline::getSplineValue(size_t index, double x)
{
    if (index > N + 1)
        throw "Invalid index";
    double epsilon = x - this->x[index];
    double value = (a[index] + b[index] * epsilon + (c[index] / 2) * epsilon * epsilon +
        (d[index] / 6) * epsilon * epsilon * epsilon);
    return value;
}

size_t Spline::getN() {
    return N;
}

size_t Spline::getCountPoint() {
    return countPoint;
}