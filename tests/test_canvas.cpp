#include <sstream>
#include <string>
#include <vector>

#include "doctest.h"
#include "canvas.h"
#include "test_helpers.h"

// Renders a canvas to PPM in memory and splits the output into lines.
static std::vector<std::string> ppm_lines(const canvas& c) {
    std::ostringstream out;
    canvas_to_ppm(c, out);

    std::istringstream in(out.str());
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

TEST_SUITE("canvas") {

TEST_CASE("creating a canvas") {
    canvas c(10, 20);
    CHECK(c.width() == 10);
    CHECK(c.height() == 20);

    bool all_black = true;
    for (int y = 0; y < c.height(); y++) {
        for (int x = 0; x < c.width(); x++) {
            if (!same_color(c.pixel_at(x, y), color_t(0, 0, 0))) {
                all_black = false;
            }
        }
    }
    CHECK(all_black);
}

TEST_CASE("writing pixels to a canvas") {
    canvas c(10, 20);
    color_t red(1, 0, 0);
    c.write_pixel(2, 3, red);
    CHECK(same_color(c.pixel_at(2, 3), red));
}

TEST_CASE("constructing the PPM header") {
    auto lines = ppm_lines(canvas(5, 3));
    REQUIRE(lines.size() >= 3);
    CHECK(lines[0] == "P3");
    CHECK(lines[1] == "5 3");
    CHECK(lines[2] == "255");
}

TEST_CASE("constructing the PPM pixel data") {
    canvas c(5, 3);
    c.write_pixel(0, 0, color_t(1.5, 0, 0));
    c.write_pixel(2, 1, color_t(0, 0.5, 0));
    c.write_pixel(4, 2, color_t(-0.5, 0, 1));

    auto lines = ppm_lines(c);
    REQUIRE(lines.size() >= 6);
    CHECK(lines[3] == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    CHECK(lines[4] == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
    CHECK(lines[5] == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST_CASE("splitting long lines in PPM files") {
    canvas c(10, 2);
    for (int y = 0; y < c.height(); y++) {
        for (int x = 0; x < c.width(); x++) {
            c.write_pixel(x, y, color_t(1, 0.8, 0.6));
        }
    }

    auto lines = ppm_lines(c);
    REQUIRE(lines.size() >= 7);
    CHECK(lines[3] == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
    CHECK(lines[4] == "153 255 204 153 255 204 153 255 204 153 255 204 153");
    CHECK(lines[5] == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
    CHECK(lines[6] == "153 255 204 153 255 204 153 255 204 153 255 204 153");
}

TEST_CASE("PPM files are terminated by a newline character") {
    std::ostringstream out;
    canvas_to_ppm(canvas(5, 3), out);
    auto ppm = out.str();
    REQUIRE_FALSE(ppm.empty());
    CHECK(ppm.back() == '\n');
}

} // TEST_SUITE("canvas")
