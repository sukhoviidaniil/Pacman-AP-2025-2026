/***************************************************************
 * Project:       Pacman
 * File:          Point2.cpp
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-12-13
 * Modified:      []
 *
 * Description:   []
 *
 * Contact:
 *   Email:       sukhovii.daniil@gmail.com
 *
 * Disclaimer:
 *   This file is part of Pacman.
 *   Unauthorized use, reproduction, or distribution is prohibited.
***************************************************************/

#include <string>
#include "infra/math/Point2.h"

namespace infra::math {

    constexpr Point2::Point2() = default;


    Point2 Point2::operator*(const float scalar) const {
        return {x * scalar, y * scalar};
    }

    Point2 Point2::operator/(const float scalar) const {
        return {x / scalar, y / scalar};
    }

    Point2 Point2::operator+(const Point2 &other) const {
        return {x + other.x, y + other.y};
    }

    Point2 Point2::operator-(const Point2 &other) const {
        return {x - other.x, y - other.y};
    }

    Point2 Point2::operator*(const Point2 &other) const {
        return {x * other.x, y * other.y};
    }

    Point2 Point2::operator/(const Point2 &other) const {
        return {x / other.x, y / other.y};
    }

    Point2 & Point2::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Point2 & Point2::operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Point2 & Point2::operator+=(const Point2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point2 & Point2::operator-=(const Point2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    bool Point2::operator==(const Point2 &other) const {
        return x == other.x && y == other.y;
    }

    std::ostream & operator<<(std::ostream &os, const Point2 &vector) {
        const std::string out = "Point2(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
        os << out;
        return os;
    }
}
