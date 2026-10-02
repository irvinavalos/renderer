#include "doctest.h"
#include "color.h"
#include "test_helpers.h"

TEST_SUITE("color") {

TEST_CASE("colors are (red, green, blue) tuples") {
    color_t c(-0.5, 0.4, 1.7);
    CHECK(c.r() == doctest::Approx(-0.5));
    CHECK(c.g() == doctest::Approx(0.4));
    CHECK(c.b() == doctest::Approx(1.7));
}

TEST_CASE("adding colors") {
    color_t c1(0.9, 0.6, 0.75);
    color_t c2(0.7, 0.1, 0.25);
    CHECK(same_color(c1 + c2, color_t(1.6, 0.7, 1.0)));
}

TEST_CASE("subtracting colors") {
    color_t c1(0.9, 0.6, 0.75);
    color_t c2(0.7, 0.1, 0.25);
    CHECK(same_color(c1 - c2, color_t(0.2, 0.5, 0.5)));
}

TEST_CASE("multiplying a color by a scalar") {
    color_t c(0.2, 0.3, 0.4);
    CHECK(same_color(c * 2, color_t(0.4, 0.6, 0.8)));
}

TEST_CASE("multiplying colors") {
    color_t c1(1, 0.2, 0.4);
    color_t c2(0.9, 1, 0.1);
    CHECK(same_color(c1 * c2, color_t(0.9, 0.2, 0.04)));
}

} // TEST_SUITE("color")
