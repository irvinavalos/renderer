#include "doctest.h"
#include "matrix.h"
#include "tuple.h"

TEST_SUITE("matrix") {

TEST_CASE("constructing and inspecting a 4x4 matrix") {
    matrix_t<4> m = {
        {1,    2,    3,    4},
        {5.5,  6.5,  7.5,  8.5},
        {9,    10,   11,   12},
        {13.5, 14.5, 15.5, 16.5},
    };
    CHECK(m(0, 0) == doctest::Approx(1));
    CHECK(m(0, 3) == doctest::Approx(4));
    CHECK(m(1, 0) == doctest::Approx(5.5));
    CHECK(m(1, 2) == doctest::Approx(7.5));
    CHECK(m(2, 2) == doctest::Approx(11));
    CHECK(m(3, 0) == doctest::Approx(13.5));
    CHECK(m(3, 2) == doctest::Approx(15.5));
}

TEST_CASE("a 2x2 matrix ought to be representable") {
    matrix_t<2> m = {
        {-3, 5},
        {1, -2},
    };
    CHECK(m(0, 0) == doctest::Approx(-3));
    CHECK(m(0, 1) == doctest::Approx(5));
    CHECK(m(1, 0) == doctest::Approx(1));
    CHECK(m(1, 1) == doctest::Approx(-2));
}

TEST_CASE("a 3x3 matrix ought to be representable") {
    matrix_t<3> m = {
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1},
    };
    CHECK(m(0, 0) == doctest::Approx(-3));
    CHECK(m(1, 1) == doctest::Approx(-2));
    CHECK(m(2, 2) == doctest::Approx(1));
}

TEST_CASE("matrix equality with identical matrices") {
    matrix_t<4> a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2},
    };
    matrix_t<4> b = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2},
    };
    CHECK(a == b);
}

TEST_CASE("matrix equality with different matrices") {
    matrix_t<4> a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2},
    };
    matrix_t<4> b = {
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1},
    };
    CHECK(a != b);
}

TEST_CASE("multiplying two matrices") {
    matrix_t<4> a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2},
    };
    matrix_t<4> b = {
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8},
    };
    matrix_t<4> expected = {
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42},
    };
    CHECK(a * b == expected);
}

TEST_CASE("a matrix multiplied by a tuple") {
    matrix_t<4> a = {
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1},
    };
    tuple_t b(1, 2, 3, 1);
    CHECK(a * b == tuple_t(18, 24, 33, 1));
}

TEST_CASE("multiplying a matrix by the identity matrix") {
    matrix_t<4> a = {
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32},
    };
    CHECK(a * matrix_t<4>::identity_matrix() == a);
}

TEST_CASE("multiplying the identity matrix by a tuple") {
    tuple_t a(1, 2, 3, 4);
    CHECK(matrix_t<4>::identity_matrix() * a == a);
}

TEST_CASE("transposing a matrix") {
    matrix_t<4> a = {
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8},
    };
    matrix_t<4> expected = {
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8},
    };
    CHECK(transpose(a) == expected);
}

TEST_CASE("transposing the identity matrix") {
    auto ident = matrix_t<4>::identity_matrix();
    CHECK(transpose(ident) == ident);
}

TEST_CASE("calculating the determinant of a 2x2 matrix") {
    matrix_t<2> a = {
        {1, 5},
        {-3, 2},
    };
    CHECK(determinant(a) == doctest::Approx(17));
}

TEST_CASE("a submatrix of a 3x3 matrix is a 2x2 matrix") {
    matrix_t<3> a = {
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3},
    };
    matrix_t<2> expected = {
        {-3, 2},
        {0, 6},
    };
    CHECK(submatrix(a, 0, 2) == expected);
}

TEST_CASE("a submatrix of a 4x4 matrix is a 3x3 matrix") {
    matrix_t<4> a = {
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1},
    };
    matrix_t<3> expected = {
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1},
    };
    CHECK(submatrix(a, 2, 1) == expected);
}

TEST_CASE("calculating a minor of a 3x3 matrix") {
    matrix_t<3> a = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    };
    auto b = submatrix(a, 1, 0);
    CHECK(determinant(b) == doctest::Approx(25));
    CHECK(minor(a, 1, 0) == doctest::Approx(25));
}

TEST_CASE("calculating a cofactor of a 3x3 matrix") {
    matrix_t<3> a = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    };
    CHECK(minor(a, 0, 0) == doctest::Approx(-12));
    CHECK(cofactor(a, 0, 0) == doctest::Approx(-12));
    CHECK(minor(a, 1, 0) == doctest::Approx(25));
    CHECK(cofactor(a, 1, 0) == doctest::Approx(-25));
}

TEST_CASE("calculating the determinant of a 3x3 matrix") {
    matrix_t<3> a = {
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4},
    };
    CHECK(cofactor(a, 0, 0) == doctest::Approx(56));
    CHECK(cofactor(a, 0, 1) == doctest::Approx(12));
    CHECK(cofactor(a, 0, 2) == doctest::Approx(-46));
    CHECK(determinant(a) == doctest::Approx(-196));
}

TEST_CASE("calculating the determinant of a 4x4 matrix") {
    matrix_t<4> a = {
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9},
    };
    CHECK(cofactor(a, 0, 0) == doctest::Approx(690));
    CHECK(cofactor(a, 0, 1) == doctest::Approx(447));
    CHECK(cofactor(a, 0, 2) == doctest::Approx(210));
    CHECK(cofactor(a, 0, 3) == doctest::Approx(51));
    CHECK(determinant(a) == doctest::Approx(-4071));
}

TEST_CASE("testing an invertible matrix for invertibility") {
    matrix_t<4> a = {
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6},
    };
    CHECK(determinant(a) == doctest::Approx(-2120));
    CHECK(a.is_invertible());
}

TEST_CASE("testing a noninvertible matrix for invertibility") {
    matrix_t<4> a = {
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0},
    };
    CHECK(determinant(a) == doctest::Approx(0));
    CHECK_FALSE(a.is_invertible());
}

TEST_CASE("calculating the inverse of a matrix") {
    matrix_t<4> a = {
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4},
    };
    auto b = inverse(a);

    CHECK(determinant(a) == doctest::Approx(532));
    CHECK(cofactor(a, 2, 3) == doctest::Approx(-160));
    CHECK(b(3, 2) == doctest::Approx(-160.0 / 532));
    CHECK(cofactor(a, 3, 2) == doctest::Approx(105));
    CHECK(b(2, 3) == doctest::Approx(105.0 / 532));

    matrix_t<4> expected = {
        { 0.21805,  0.45113,  0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361,  0.52068},
        {-0.07895, -0.22368, -0.05263,  0.19737},
        {-0.52256, -0.81391, -0.30075,  0.30639},
    };
    CHECK(b == expected);
}

TEST_CASE("calculating the inverse of another matrix") {
    matrix_t<4> a = {
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4},
    };
    matrix_t<4> expected = {
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692,  0.12308,  0.02564,  0.03077},
        { 0.35897,  0.35897,  0.43590,  0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308},
    };
    CHECK(inverse(a) == expected);
}

TEST_CASE("calculating the inverse of a third matrix") {
    matrix_t<4> a = {
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2},
    };
    matrix_t<4> expected = {
        {-0.04074, -0.07778,  0.14444, -0.22222},
        {-0.07778,  0.03333,  0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926,  0.12963},
        { 0.17778,  0.06667, -0.26667,  0.33333},
    };
    CHECK(inverse(a) == expected);
}

TEST_CASE("multiplying a product by its inverse") {
    matrix_t<4> a = {
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1},
    };
    matrix_t<4> b = {
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5},
    };
    auto c = a * b;
    CHECK(c * inverse(b) == a);
}

} // TEST_SUITE("matrix")
