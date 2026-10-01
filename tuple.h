#ifndef TUPLE_H
#define TUPLE_H

#include <format>
#include <cassert>
#include <cmath>

#include "helpers.h"

struct tuple_t {
public:
    tuple_t(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0)
        : _x(x), _y(y), _z(z), _w(w) {}

    inline double x() const {
        return _x;
    }

    inline double y() const {
        return _y;
    }

    inline double z() const {
        return _z;
    }

    inline double w() const {
        return _w;
    }
    
    static inline bool is_point(tuple_t t) {
        return equalf(t.w(), 1.0);
    }

    static inline bool is_vector(tuple_t t) {
        return equalf(t.w(), 0.0);
    }

    static inline tuple_t point(double x, double y, double z) {
        return tuple_t(x, y, z, 1.0);
    }

    static inline tuple_t vec3(double x, double y, double z) {
        return tuple_t(x, y, z, 0.0);
    }

    tuple_t& operator+=(const tuple_t& other) {
        this->_x += other._x;
        this->_y += other._y;
        this->_z += other._z;
        this->_w += other._w;

        return *this;
    }

    tuple_t& operator-=(const tuple_t& other) {
        this->_x -= other._x;
        this->_y -= other._y;
        this->_z -= other._z;
        this->_w -= other._w;

        return *this;
    }

    tuple_t operator-() const {
        return tuple_t(-x(), -y(), -z(), -w());
    }

    tuple_t& operator*=(double scalar) {
        this->_x *= scalar;
        this->_y *= scalar;
        this->_z *= scalar;
        this->_w *= scalar;

        return *this;
    }

    tuple_t& operator/=(double scalar) {
        this->_x /= scalar;
        this->_y /= scalar;
        this->_z /= scalar;
        this->_w /= scalar;

        return *this;
    }

    bool operator==(const tuple_t& other) const {
        return equalf(x(), other.x()) && equalf(y(), other.y()) && equalf(z(), other.z()) && equalf(w(), other.w());
    }

    double& operator()(std::size_t n) {
        assert(( n >= 0 && n <= 3 ) && "ERROR: index for tuple is out of bounds");

        if (n == 0) {
            return _x;
        } else if (n == 1) {
            return _y;
        } else if (n == 2) {
            return _z;
        }
        return _w;
    }

    double operator()(std::size_t n) const {
        assert(( n >= 0 && n <= 3 ) && "ERROR: index for tuple is out of bounds");

        if (n == 0) {
            return _x;
        } else if (n == 1) {
            return _y;
        } else if (n == 2) {
            return _z;
        }
        return _w;
    }

private:
    double _x, _y, _z, _w;
};


using vec3_t = tuple_t;
using point_t = tuple_t;


inline tuple_t operator+(tuple_t lhs, const tuple_t& rhs) {
    lhs += rhs;
    return lhs;
}

inline tuple_t operator-(tuple_t lhs, const tuple_t& rhs) {
    lhs -= rhs;
    return lhs;
}

inline tuple_t operator*(tuple_t lhs, double scalar) {
    lhs *= scalar;
    return lhs;
}

inline tuple_t operator*(double scalar, tuple_t rhs) {
    return rhs * scalar;
}

inline tuple_t operator/(tuple_t lhs, double scalar) {
    lhs /= scalar;
    return lhs;
}
 

template<>
struct std::formatter<tuple_t> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const tuple_t& t, std::format_context& ctx) const {
        if (tuple_t::is_point(t) || tuple_t::is_vector(t)) {
            return std::format_to(ctx.out(), "({:.3f}, {:.3f}, {:.3f})", t.x(), t.y(), t.z(), t.w());
        }
        return std::format_to(ctx.out(), "({:.3f}, {:.3f}, {:.3f}, {:.3f})", t.x(), t.y(), t.z(), t.w());
    }
};

inline double magnitude(const tuple_t& v) {
    assert(tuple_t::is_vector(v) && "ERROR: trying to find the magnitude of a non-vector");

    return std::sqrt(
        v.x() * v.x() + v.y() * v.y() + v.z() * v.z() + v.w() * v.w()
    );
}

inline tuple_t normalize(const tuple_t& v) {
    assert(tuple_t::is_vector(v) && "ERROR: trying to normalize a non-vector");

    auto m = magnitude(v);

    return tuple_t(v.x() / m, v.y() / m, v.z() / m, v.w() / m);
}

inline double dot(const tuple_t& v, const tuple_t& u) {
    assert(tuple_t::is_vector(v) && "ERROR: lhs is not a vector in dot product");
    assert(tuple_t::is_vector(u) && "ERROR: rhs is not a vector in dot product");

    return v.x() * u.x() + v.y() * u.y() + v.z() * u.z() + v.w() * u.w();
}

inline tuple_t cross(const tuple_t& v, const tuple_t& u) {
    assert(tuple_t::is_vector(v) && "ERROR: lhs is not a vector in cross product");
    assert(tuple_t::is_vector(u) && "ERROR: rhs is not a vector in cross product");

    return tuple_t::vec3(
        v.y() * u.z() - v.z() * u.y(),
        v.z() * u.x() - v.x() * u.z(),
        v.x() * u.y() - v.y() * u.x()
    );
}

#endif // !TUPLE_H
