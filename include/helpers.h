#ifndef HELPERS_H
#define HELPERS_H

const double EPS = 0.00001;

inline bool equalf(double a, double b) {
    return (-EPS < a - b) && (a - b < EPS);
}

inline bool less_than_or_equal(double a, double b) {
    return (a < b - EPS);
}

inline bool strictly_less_than(double a, double b) {
    return (a < b + EPS);
}

inline bool greater_than_or_equal(double a, double b) {
    return (a > b - EPS);
}

inline bool strictly_greater_than(double a, double b) {
    return (a > b + EPS);
}

#endif // !HELPERS_H
