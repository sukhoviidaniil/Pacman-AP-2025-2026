#include "math/Vector2.h"

#include <cmath>
#include <string>

namespace Math {
    Vector2::~Vector2() = default;

    Vector2::Vector2() = default;

    Vector2::Vector2(const double x, const double y) : x(x), y(y) {
    }

    // ========== Arithmetic operators ==========
    Vector2 Vector2::operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 Vector2::operator*(const Vector2& other) const {
        return {x * other.x, y * other.y};
    }

    Vector2 Vector2::operator/(const Vector2& other) const {
        return {x / other.x, y / other.y};
    }

    Vector2 Vector2::operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2 Vector2::operator/(double scalar) const {
        return {x / scalar, y / scalar};
    }

    // ========== Compound Operators ==========

    Vector2& Vector2::operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& Vector2::operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& Vector2::operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // == Comparison ==========

    bool Vector2::operator==(const Vector2& other) const {
        constexpr double EPS = 1e-9;
        return std::fabs(x - other.x) < EPS && std::fabs(y - other.y) < EPS;
    }

    // ========== Output to stream ==========

    std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        const std::string out = "Vector2(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
        os << out;
        return os;
    }

    // ========== Vector Operations ==========

    void Vector2::normalize() {
        double len = length();
        if (len != 0.0) {
            x /= len;
            y /= len;
        }
    }

    double Vector2::length() const {
        return std::sqrt(x * x + y * y);
    }

    double Vector2::dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // For 2D vectors, cross typically returns a pseudoscalar (the Z-component of the 3D cross product)
    double Vector2::cross(const Vector2& other) const {
        double z = x * other.y - y * other.x;
        return z;
    }
}
