#pragma once
#include <vector>
#include <QPointF>
#include <algorithm>

class Spline {
	private:
		std::vector<double> a, b, c, d;
        std::vector<double> x, y;
        size_t countPoint, N;

    public:
        Spline();
        Spline(const size_t N_, const size_t countPoint_);
        void addPoint(const QPointF& temp);
        void solve();
        double Spline::getSplineValue(const size_t index, const double x);
        size_t getN();
        size_t getCountPoint();
        void deleteSpline();

        friend class mainWindow;
};