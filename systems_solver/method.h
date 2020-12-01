#ifndef METHOD_H
#define METHOD_H

enum Method
{
    GaussMethod = 0,
    KramerMethod = 1,
    SeidelMethod = 2,
    UpperRelaxationMethod = 3,
    SimpleIterationMethod = 4,
    JacobiMethod = 5
};

constexpr int METHODS_COUNT = 6;

#endif // METHOD_H
