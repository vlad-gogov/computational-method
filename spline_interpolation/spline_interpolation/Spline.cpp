#include "Spline.h"

#define MIN_POINT_SPLINE 3

Spline::Spline() {
    N = countPoint = 0;
}

Spline::Spline(const size_t N_, const size_t countPoint_) {
    N = N_;
    countPoint = countPoint_;
    a = std::vector<double>(countPoint, 0);
    b = std::vector<double>(countPoint, 0);
    c = std::vector<double>(countPoint, 0);
    d = std::vector<double>(countPoint, 0);
}

void Spline::addPoint(const QPointF& temp) {
    size_t index;
    for (index = 0; index < x.size(); index++) {
        if(x[index] == temp.x())
            throw "A point with this x coordinate already exists";
        if (x[index] > temp.x()) {
            break;
        }
    }
    if (index == countPoint)
        throw "Spline is full";
    x.insert(x.begin() + index, temp.x());
    y.insert(y.begin() + index, temp.y());
}

void Spline::solve() {

    if (x.size() < MIN_POINT_SPLINE) {
        return;
    }

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

    p[0] = -aboveDiagonal[0] / mainDiagonal[0];

    for (size_t k = 1; k < N - 2; k++) {
        double temp = belowDiagonal[k - 1] * p[k - 1] + mainDiagonal[k];
        p[k] = -aboveDiagonal[k] / temp;
    }

    q[0] = f[0] / mainDiagonal[0];

    for (size_t k = 1; k < N - 1; k++) {
        double temp = belowDiagonal[k - 1] * p[k - 1] + mainDiagonal[k];
        q[k] = (f[k] - belowDiagonal[k - 1] * q[k - 1]) / temp;
    }

    c[0] = c[N] = 0.0f;
    c[N - 1] = q[N - 2];

    for (size_t k = N - 2; k > 0; k--) {
        c[k] = p[k - 1] * c[k + 1] + q[k - 1];
    }

    d[0] = c[1] / h[0];

    for (size_t k = 1; k < N + 1; k++) {
            d[k] = (c[k] - c[k - 1]) / h[k - 1];
    }

    b[0] = c[1] * h[0] / 3 + ((y[1] - y[0]) / h[0]);

    for (size_t k = 1; k < N + 1; k++) {
        b[k] = c[k] * h[k - 1] / 3 + c[k - 1] * h[k - 1] / 6 + ((y[k] - y[k - 1]) / h[k - 1]);
    }

    for (size_t k = 0; k < N + 1; k++) {
        a[k] = y[k];
    }
}

void Spline::deleteSpline() {
    N = 0;
    countPoint = 0;
    x.clear();
    y.clear();
    a.clear();
    b.clear();
    c.clear();
    d.clear();
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