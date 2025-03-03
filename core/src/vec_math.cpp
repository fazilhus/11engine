#include "vec_math.h"
#include <array>
#include <cmath>

std::array<int, 2>& operator+=(std::array<int, 2>& a, const std::array<int, 2>& b) {
    a[0] += b[0];
    a[1] += b[1];
    return a;
}

std::array<int, 2>& operator-=(std::array<int, 2>& a, const std::array<int, 2>& b) {
    a[0] -= b[0];
    a[1] -= b[1];
    return a;
}

std::array<int, 2> operator+(const std::array<int, 2>& a, const std::array<int, 2>& b) {
    return {
        a[0] + b[0],
        a[1] + b[1]
    };
}

std::array<int, 2> operator+(const std::array<int, 2>& a, int b) {
    return {
        a[0] + b,
        a[1] + b
    };
}

std::array<int, 2> operator-(const std::array<int, 2>& a) {
    return {
        -a[0],
        -a[1]
    };
}

std::array<int, 2> operator-(const std::array<int, 2>& a, const std::array<int, 2>& b) {
    return {
        a[0] - b[0],
        a[1] - b[1]
    };
}

std::array<int, 2> operator-(const std::array<int, 2>& a, int b) {
    return {
        a[0] - b,
        a[1] - b
    };
}

std::array<int, 2> operator*(const std::array<int, 2>& a, int n) {
    return {
        a[0] * n,
        a[1] * n
    };
}

namespace core::math {

    std::array<int, 2> norm(std::array<int, 2> a) {
        return {
            a[0] == 0 ? 0 : a[0] / abs(a[0]),
            a[1] == 0 ? 0 : a[1] / abs(a[1]),
        };
    }

    std::array<int, 2> min(std::array<int, 2> a, std::array<int, 2> b) {
        return a[0] < b[0] && a[1] < b[1] ? a : b;
    }

    std::array<int, 2> max(std::array<int, 2> a, std::array<int, 2> b) {
        return a[0] < b[0] && a[1] < b[1] ? b : a;
    }

    std::array<int, 2> clamp(std::array<int, 2> a, std::array<int, 2> b) {
        return min(max(a, -b), b);
    }

    bool point_inside_square(std::array<int, 2> sp1, std::array<int, 2> sp2, std::array<int, 2> p) {
        return p[0] >= sp1[0] && p[1] >= sp1[1] && p[0] < sp2[0] && p[1] < sp2[1];
    }

} // namespace core::math