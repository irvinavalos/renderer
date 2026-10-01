#include "doctest.h"
#include "tuple.h"

TEST_CASE("a tuple with w=1.0 is a point") {
    tuple_t a(4.3, -4.2, 3.1, 1.0);

    CHECK(a.x() == doctest::Approx(4.3));
    CHECK(tuple_t::is_point(a));
    CHECK_FALSE(tuple_t::is_vector(a));
}
