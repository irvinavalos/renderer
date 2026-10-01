#include <cmath>

#include "doctest.h"
#include "tuple.h"

TEST_SUITE("tuple") {

TEST_CASE("a tuple with w=1.0 is a point") {
    tuple_t a(4.3, -4.2, 3.1, 1.0);
    CHECK(a.x() == doctest::Approx(4.3));
    CHECK(a.y() == doctest::Approx(-4.2));
    CHECK(a.z() == doctest::Approx(3.1));
    CHECK(a.w() == doctest::Approx(1.0));
    CHECK(tuple_t::is_point(a));
    CHECK_FALSE(tuple_t::is_vector(a));
}

TEST_CASE("a tuple with w=0 is a vector") {
    tuple_t a(4.3, -4.2, 3.1, 0.0);
    CHECK(a.x() == doctest::Approx(4.3));
    CHECK(a.y() == doctest::Approx(-4.2));
    CHECK(a.z() == doctest::Approx(3.1));
    CHECK(a.w() == doctest::Approx(0.0));
    CHECK_FALSE(tuple_t::is_point(a));
    CHECK(tuple_t::is_vector(a));
}

TEST_CASE("point() creates tuples with w=1") {
    auto p = tuple_t::point(4, -4, 3);
    CHECK(p == tuple_t(4, -4, 3, 1));
}

TEST_CASE("vec3() creates tuples with w=0") {
    auto v = tuple_t::vec3(4, -4, 3);
    CHECK(v == tuple_t(4, -4, 3, 0));
}

TEST_CASE("adding two tuples") {
    tuple_t a1(3, -2, 5, 1);
    tuple_t a2(-2, 3, 1, 0);
    CHECK(a1 + a2 == tuple_t(1, 1, 6, 1));
}

TEST_CASE("subtracting two points") {
    auto p1 = tuple_t::point(3, 2, 1);
    auto p2 = tuple_t::point(5, 6, 7);
    CHECK(p1 - p2 == tuple_t::vec3(-2, -4, -6));
}

TEST_CASE("subtracting a vector from a point") {
    auto p = tuple_t::point(3, 2, 1);
    auto v = tuple_t::vec3(5, 6, 7);
    CHECK(p - v == tuple_t::point(-2, -4, -6));
}

TEST_CASE("subtracting two vectors") {
    auto v1 = tuple_t::vec3(3, 2, 1);
    auto v2 = tuple_t::vec3(5, 6, 7);
    CHECK(v1 - v2 == tuple_t::vec3(-2, -4, -6));
}

TEST_CASE("subtracting a vector from the zero vector") {
    auto zero = tuple_t::vec3(0, 0, 0);
    auto v = tuple_t::vec3(1, -2, 3);
    CHECK(zero - v == tuple_t::vec3(-1, 2, -3));
}

TEST_CASE("negating a tuple") {
    tuple_t a(1, -2, 3, -4);
    CHECK(-a == tuple_t(-1, 2, -3, 4));
}

TEST_CASE("multiplying a tuple by a scalar") {
    tuple_t a(1, -2, 3, -4);
    CHECK(a * 3.5 == tuple_t(3.5, -7, 10.5, -14));
}

TEST_CASE("multiplying a tuple by a fraction") {
    tuple_t a(1, -2, 3, -4);
    CHECK(a * 0.5 == tuple_t(0.5, -1, 1.5, -2));
}

TEST_CASE("dividing a tuple by a scalar") {
    tuple_t a(1, -2, 3, -4);
    CHECK(a / 2 == tuple_t(0.5, -1, 1.5, -2));
}

TEST_CASE("computing the magnitude of vector(1, 0, 0)") {
    auto v = tuple_t::vec3(1, 0, 0);
    CHECK(magnitude(v) == doctest::Approx(1));
}

TEST_CASE("computing the magnitude of vector(0, 1, 0)") {
    auto v = tuple_t::vec3(0, 1, 0);
    CHECK(magnitude(v) == doctest::Approx(1));
}

TEST_CASE("computing the magnitude of vector(0, 0, 1)") {
    auto v = tuple_t::vec3(0, 0, 1);
    CHECK(magnitude(v) == doctest::Approx(1));
}

TEST_CASE("computing the magnitude of vector(1, 2, 3)") {
    auto v = tuple_t::vec3(1, 2, 3);
    CHECK(magnitude(v) == doctest::Approx(std::sqrt(14.0)));
}

TEST_CASE("computing the magnitude of vector(-1, -2, -3)") {
    auto v = tuple_t::vec3(-1, -2, -3);
    CHECK(magnitude(v) == doctest::Approx(std::sqrt(14.0)));
}

TEST_CASE("normalizing vector(4, 0, 0) gives (1, 0, 0)") {
    auto v = tuple_t::vec3(4, 0, 0);
    CHECK(normalize(v) == tuple_t::vec3(1, 0, 0));
}

TEST_CASE("normalizing vector(1, 2, 3)") {
    auto v = tuple_t::vec3(1, 2, 3);
    // vector(1/√14, 2/√14, 3/√14)
    CHECK(normalize(v) == tuple_t::vec3(0.26726, 0.53452, 0.80178));
}

TEST_CASE("the magnitude of a normalized vector") {
    auto v = tuple_t::vec3(1, 2, 3);
    auto norm = normalize(v);
    CHECK(magnitude(norm) == doctest::Approx(1));
}

TEST_CASE("the dot product of two tuples") {
    auto a = tuple_t::vec3(1, 2, 3);
    auto b = tuple_t::vec3(2, 3, 4);
    CHECK(dot(a, b) == doctest::Approx(20));
}

TEST_CASE("the cross product of two vectors") {
    auto a = tuple_t::vec3(1, 2, 3);
    auto b = tuple_t::vec3(2, 3, 4);
    CHECK(cross(a, b) == tuple_t::vec3(-1, 2, -1));
    CHECK(cross(b, a) == tuple_t::vec3(1, -2, 1));
}

} // TEST_SUITE("tuple")
