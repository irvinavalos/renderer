#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H
 
#include "color.h"
#include "helpers.h"
 
// Approximate color comparison, so tests don't depend on color_t having operator==.
inline bool same_color(const color_t& a, const color_t& b) {
    return equalf(a.r(), b.r()) && equalf(a.g(), b.g()) && equalf(a.b(), b.b());
}
 
#endif // !TEST_HELPERS_H
