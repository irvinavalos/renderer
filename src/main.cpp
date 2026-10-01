#include <print>

#include "tuple.h"
#include "matrix.h"
#include "canvas.h"

struct projectile {
    projectile(point_t p, vec3_t v) : position(p), velocity(v) {}

    point_t position;
    vec3_t velocity;
};

struct environment{
    environment(vec3_t g, vec3_t w) : gravity(g), wind(w) {}

    vec3_t gravity;
    vec3_t wind;
};

projectile tick(environment e, projectile p) {
    auto position = p.position + p.velocity;
    auto velocity = p.velocity + e.gravity + e.wind;
    return projectile(position, velocity);
}

void environment_test() {
    auto p = projectile(tuple_t::point(0, 1, 0), normalize(tuple_t::vec3(1, 1, 0)));
    auto e = environment(tuple_t::vec3(0, -0.1, 0), tuple_t::vec3(-0.01, 0, 0));

    for (int i = 0; i < 100; i++) {
        std::println("#{}: {}", i + 1, p.position);
        if (p.position.y() <= 0) {
            std::println("num_iterations: {}", i + 1);
            break;
        }
        p = tick(e, p);
    }
}

int main() {
    // auto c = canvas(5, 3);
    // auto c1 = color_t(1.5, 0, 0);
    // auto c2 = color_t(0, 0.5, 0);
    // auto c3 = color_t(-0.5, 0, 1.0);
    // c.write_pixel(0, 0, c1);
    // c.write_pixel(2, 1, c2);
    // c.write_pixel(4, 2, c3);
    // canvas_to_ppm(c);

    // auto color = color_t(1.0, 0.8, 0.6);
    // auto c = canvas(10, 2, color);
    // canvas_to_ppm(c);

    // matrix_t<3> m1 = {
    //     {-1.0, -1.0, 4.0}, 
    //     {0.0, 3.0, -3.0}, 
    //     {2.0, -1.0, -2.0}, 
    // };
    //
    // matrix_t<3> m2 = {
    //     {3.0, 2.0, 3.0}, 
    //     {2.0, 2.0, 1.0}, 
    //     {2.0, 1.0, 1.0}, 
    // };
    //
    // matrix_t<3> res = {
    //     {3, 0, 0},
    //     {0, 3, 0},
    //     {0, 0, 3},
    // };

    matrix_t<4> m = {
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1},
    };

    tuple_t t = tuple_t(1, 2, 3, 1);

    std::println("{}", m * t == tuple_t(18, 24, 33, 1));
    std::println("{}", m * matrix_t<4>::identity_matrix() == m);
    std::println("{}", matrix_t<4>::identity_matrix() * t == t);

    matrix_t<3> a = {
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3},
    };

    matrix_t<2> sub_a = {
        {-3, 2},
        {0, 6}
    };

    std::println("A = SUB_MATRRIX(A, 0, 2): {}", submatrix(a, 0, 2) == sub_a);

    matrix_t<4> b = {
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1},
    };

    matrix_t<3> sub_b = {
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1},
    };

    std::println("B = SUB_MATRRIX(B, 2, 1): {}", submatrix(b, 2, 1) == sub_b);

    matrix_t<3> c = {
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4},
    };

    std::println("cofactor(c, 0, 0) = {}", cofactor(c, 0, 0));
    std::println("cofactor(c, 0, 1) = {}", cofactor(c, 0, 1));
    std::println("cofactor(c, 0, 2) = {}", cofactor(c, 0, 2));
    std::println("determinant(c) = {}", determinant(c));

    matrix_t<4> d = {
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9},
    };

    std::println("cofactor(d, 0, 0) = {}", cofactor(d, 0, 0));
    std::println("cofactor(d, 0, 1) = {}", cofactor(d, 0, 1));
    std::println("cofactor(d, 0, 2) = {}", cofactor(d, 0, 2));
    std::println("cofactor(d, 0, 3) = {}", cofactor(d, 0, 3));
    std::println("determinant(d) = {}", determinant(d));

    matrix_t<4> e = {
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0},
    };

    std::println("e should not be invertible, {}", !e.is_invertible());

    return 0;
}
