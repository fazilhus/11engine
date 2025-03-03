#pragma once

#include <array>

std::array<int, 2>& operator+=(std::array<int, 2>& a, const std::array<int, 2>& b);
std::array<int, 2>& operator-=(std::array<int, 2>& a, const std::array<int, 2>& b);
std::array<int, 2> operator+(const std::array<int, 2>& a, const std::array<int, 2>& b);
std::array<int, 2> operator+(const std::array<int, 2>& a, int b);
std::array<int, 2> operator-(const std::array<int, 2>& a);
std::array<int, 2> operator-(const std::array<int, 2>& a, const std::array<int, 2>& b);
std::array<int, 2> operator-(const std::array<int, 2>& a, int b);
std::array<int, 2> operator*(const std::array<int, 2>& a, int n);

namespace core::math {

    std::array<int, 2> norm(std::array<int, 2> a);
    std::array<int, 2> min(std::array<int, 2> a, std::array<int, 2> b);
    std::array<int, 2> max(std::array<int, 2> a, std::array<int, 2> b);
    std::array<int, 2> clamp(std::array<int, 2> a, std::array<int, 2> b);
    bool point_inside_square(std::array<int, 2> sp1, std::array<int, 2> sp2, std::array<int, 2> p);

} // namespace core::math