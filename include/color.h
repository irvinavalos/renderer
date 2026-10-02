#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <cmath>

#include "helpers.h"

struct color_t {
public:
    color_t(double r, double g, double b)
        : _r(r), _g(g), _b(b) {}

    static const int MIN_COLOR = 0;
    static const int MAX_COLOR = 255;

    static inline color_t black() {
        return color_t(0.0, 0.0, 0.0);
    }

    inline double r() const {
        return _r;
    }

    inline double g() const {
        return _g;
    }

    inline double b() const {
        return _b;
    }

    color_t& operator+=(const color_t& other) {
        this->_r += other._r;
        this->_g += other._g;
        this->_b += other._b;

        return *this;
    }

    color_t& operator-=(const color_t& other) {
        this->_r -= other._r;
        this->_g -= other._g;
        this->_b -= other._b;

        return *this;
    }

    color_t& operator*=(double scalar) {
        this->_r *= scalar;
        this->_g *= scalar;
        this->_b *= scalar;

        return *this;
    }

    color_t& operator*=(const color_t& other) {
        // Hammard product
        this->_r *= other._r;
        this->_g *= other._g;
        this->_b *= other._b;

        return *this;
    }

private:
    double _r, _g, _b;
};

inline color_t operator+(color_t lhs, const color_t& rhs) {
    lhs += rhs;
    return lhs;
}

inline color_t operator-(color_t lhs, const color_t& rhs) {
    lhs -= rhs;
    return lhs;
}

inline color_t operator*(color_t lhs, double scalar) {
    lhs *= scalar;
    return lhs;
}

inline color_t operator*(double scalar, color_t rhs) {
    return rhs * scalar;
}

inline color_t operator*(color_t lhs, const color_t& rhs) {
    lhs *= rhs;
    return lhs;
}

inline int get_color_value(double color_channel) {
    if (less_than_or_equal(color_channel, 0.0)) {
        return color_t::MIN_COLOR;
    } else if (greater_than_or_equal(color_channel, 1.0)) {
        return color_t::MAX_COLOR;
    }
    return static_cast<int>(std::lround(color_channel * color_t::MAX_COLOR));
}

inline std::string get_color_string(int color_value) {
    return std::to_string(color_value);
}

#endif // !COLOR_H
