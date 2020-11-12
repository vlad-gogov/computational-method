#pragma once
#include <vector>

class Spline {
	private:
		std::vector<double> a, b, ñ, d;
        std::vector<double> x;
        size_t countPoint, N;

    public:
        Spline(const std::vector<double>& x, const std::vector<double>& y);
        double Spline::getSplineValue(size_t index, double x);
        size_t getN();
        size_t getCountPoint();
};