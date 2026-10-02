#ifndef MATRIX_H
#define MATRIX_H

#include <format>
#include <cassert>
#include <cstddef>
#include <array>
#include <initializer_list>
#include <string>

#include "tuple.h"
#include "helpers.h"

template <std::size_t N>
class matrix_t;

template <std::size_t N>
inline matrix_t<N> transpose(const matrix_t<N>& mat);

template <std::size_t N>
inline double determinant(const matrix_t<N>& mat);

template <std::size_t N>
inline matrix_t<N - 1> submatrix(const matrix_t<N>& mat, std::size_t row_to_exclude, std::size_t col_to_exclude);

template <std::size_t N>
inline double minor(const matrix_t<N>& mat, std::size_t row, std::size_t col);

template <std::size_t N>
inline double cofactor(const matrix_t<N>& mat, std::size_t row, std::size_t col);

template <std::size_t N>
class matrix_t {
public:
    static_assert((N >= 1 && N <= 4) && "ERROR: incorrect matrix dimensions");

    matrix_t() = default;

    matrix_t(std::initializer_list<std::initializer_list<double>> rows) {
        assert(rows.size() == N && "ERROR: wrong number of rows");
        
        int r = 0;
        for (const auto& row : rows) {
            assert(row.size() == N && "ERROR: wrong row length");

            int c = 0;
            for (double v : row) {
                _matrix[r][c++] = v;
            }
            r += 1;
        }
    }

    static inline matrix_t identity_matrix() {
        matrix_t ident{};

        for (std::size_t r = 0; r < N; r++) {
            for (std::size_t c = 0; c < N; c++) {
                if (r == c) {
                    ident(r, c) = 1.0;
                }
            }
        }

        return ident;
    }

    inline int size() const { return N; }

    inline bool is_invertible() const { return !equalf(determinant(*this), 0.0); }

    bool operator==(const matrix_t& other) const {
        for (std::size_t r = 0; r < N; r++) {
            for (std::size_t c = 0; c < N; c++) {
                if (!equalf((*this)(r, c) , other(r, c))) {
                    return false;
                }
            }
        }

        return true;
    }


    double& operator()(std::size_t row, std::size_t col) {
        return _matrix[row][col];
    }

    double operator()(std::size_t row, std::size_t col) const {
        return _matrix[row][col];
    }

private:
    std::array<std::array<double, N>, N> _matrix{};
};

template <std::size_t N>
struct std::formatter<matrix_t<N>> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const matrix_t<N>& m, std::format_context& ctx) const {
        std::string matrix_str = "";

        for (std::size_t r = 0; r < N; r++) {
            matrix_str += "|";
            for (std::size_t c = 0; c < N; c++) {
                matrix_str += std::format(" {:^9.3f}", m(r, c));
            }
            matrix_str += " |\n";
        }

        return std::format_to(ctx.out(), "{}", matrix_str);
    }
};

template <std::size_t N>
inline matrix_t<N> operator*(const matrix_t<N>& lhs, const matrix_t<N>& rhs) {
    matrix_t<N> prod{};

    for (std::size_t r = 0; r < N; r++) {
        for (std::size_t c = 0; c < N; c++) {
            double sum = 0.0;
            for (std::size_t k = 0; k < N; k++) {
                sum += lhs(r, k) * rhs(k, c);
            }
            prod(r, c) = sum;
        }
    }

    return prod;
}

inline tuple_t operator*(const matrix_t<4>& lhs, const tuple_t& rhs) {
    tuple_t t{};

    for (std::size_t r = 0; r < 4; r++) {
        double sum = 0.0;
        for (std::size_t k = 0; k < 4; k++) {
            sum += lhs(r, k) * rhs(k);
        }
        t(r) = sum;
    }

    return t;
}

template <std::size_t N>
inline matrix_t<N> transpose(const matrix_t<N>& mat) {
    matrix_t<N> transposed{};


    for (std::size_t r = 0; r < N; r++) {
        for (std::size_t c = 0; c < N; c++) {
            transposed(r, c) = mat(c, r);
        }
    }

    return transposed;
}

template <std::size_t N>
inline double determinant(const matrix_t<N>& mat) {
    double det = 0.0;

    if constexpr (N == 2) {
        det += (mat(0, 0) * mat(1, 1)) - (mat(0, 1) * mat(1, 0));
    } else {
        for (std::size_t c = 0; c < N; c++) {
            det += mat(0, c) * cofactor(mat, 0, c);
        }
    }

    return det;
}

template <std::size_t N>
inline matrix_t<N - 1> submatrix(const matrix_t<N>& mat, std::size_t row_to_exclude, std::size_t col_to_exclude) {
    static_assert(((N == 3) || (N == 4)) && "ERROR: trying to compute submatrix of a 2x2 matrix");

    matrix_t<N - 1> submat{};

    std::size_t s_row = 0;
    for (std::size_t r = 0; r < N; r++) {
        if (r == row_to_exclude) { continue; }
        std::size_t s_col = 0;
        for (std::size_t c = 0; c < N; c++) {
            if (c == col_to_exclude) { continue; }
            submat(s_row, s_col) = mat(r, c);
            s_col += 1;
        }
        s_row += 1;
    }

    return submat;
}

template <std::size_t N>
inline double minor(const matrix_t<N>& mat, std::size_t row, std::size_t col) {
    static_assert(((N == 3) || (N == 4)) && "ERROR: trying to compute the minor of a 2x2 matrix");

    return determinant(submatrix(mat, row, col));
}

template <std::size_t N>
inline double cofactor(const matrix_t<N>& mat, std::size_t row, std::size_t col) {
    static_assert(((N == 3) || (N == 4)) && "ERROR: trying to compute the cofactor of a 2x2 matrix");

    if ((row + col) % 2 != 0) {
        return -minor(mat, row, col);
    }
    return minor(mat, row, col);
}

template <std::size_t N>
inline matrix_t<N> inverse(const matrix_t<N>& mat) {
    assert(mat.is_invertible() && "ERROR: trying to find the inverse of a non-invertible matrix");

    matrix_t<N> res{};
    double det = determinant(mat);

    for (std::size_t r = 0; r < N; r++) {
        for (std::size_t c = 0; c < N; c++) {
            res(c, r) = cofactor(mat, r, c) / det;
        }
    }

    return res;
}

#endif // !MATRIX_H
