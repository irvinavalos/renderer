#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <fstream>
#include <print>
#include <string>

#include "color.h"

class canvas {
public:
    canvas(int width, int height, color_t color = color_t::black())
        : _width(width), _height(height), _canvas(width * height, color) {}

    inline void write_pixel(int x, int y, color_t color) {
        auto canvas_idx = from2dIdxTo1dIdx(x, y);
        _canvas.at(canvas_idx) = color;
    }

    inline color_t pixel_at(int x, int y) const {
        auto canvas_idx = from2dIdxTo1dIdx(x, y);
        return _canvas.at(canvas_idx);
    }

    inline int width() const {
        return _width;
    }

    inline int height() const {
        return _height;
    }

private:
    int _width, _height;

    std::vector<color_t> _canvas;

    inline int from2dIdxTo1dIdx(int w, int h) const {
        return w * _height + h;
    }
};

inline void ppm_line_check_length(std::ofstream& out, const std::string& src, std::string& dst) {
    // If the sum of the lengths between the two strings exceeds 70,
    // then we are safe to wrap around to the next line
    if (src.length() + dst.length() >= 70) {
        if (!dst.empty() && dst.back() == ' ') {
            dst.pop_back();
        }
        std::print(out, "{}\n", dst);
        dst = "";
    }
}

inline void ppm_line_add_string(std::ofstream& out, const std::string& src, std::string& dst) {
    ppm_line_check_length(out, src, dst);
    dst += src;
}


inline void canvas_to_ppm(const canvas& canvas) {
    auto width = canvas.width();
    auto height = canvas.height();

    std::ofstream out("image.ppm");

    std::print(out, "P3\n");
    std::print(out, "{} {}\n", width, height);
    std::print(out, "255\n");

    std::string line = "";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto cur_color = canvas.pixel_at(x, y);

            auto r = get_color_value(cur_color.r());
            auto g = get_color_value(cur_color.g());
            auto b = get_color_value(cur_color.b());

            auto r_str = get_color_string(r) + " ";
            auto g_str = get_color_string(g) + " ";
            auto b_str = get_color_string(b);

            if (x < width - 1) { b_str += " "; }

            ppm_line_add_string(out, r_str, line);
            ppm_line_add_string(out, g_str, line);
            ppm_line_add_string(out, b_str, line);
        }
        std::print(out, "{}\n", line);
        line = "";
    }

    std::print(out, "\n");
}

#endif // !CANVAS_H
