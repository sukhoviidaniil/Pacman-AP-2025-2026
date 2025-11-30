#include "math/Vector2.h"

#include <cmath>
#include <string>

namespace Math {
    Vector2::~Vector2() = default;

    Vector2::Vector2() = default;

    Vector2::Vector2(const float x, const float y) : x(x), y(y) {
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

    Vector2 Vector2::operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2 Vector2::operator/(float scalar) const {
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

    Vector2& Vector2::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& Vector2::operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // == Comparison ==========

    bool Vector2::operator==(const Vector2& other) const {
        constexpr double EPS = 1e-9;
        return std::fabs(x - other.x) < EPS && std::fabs(y - other.y) < EPS;
    }

    bool Vector2::is_between(const Vector2 &start, const Vector2 &end) const {
        // Vector from start to end
        const Vector2 segVec = end - start;
        // Vector from start to current point
        const Vector2 pointVec = *this - start;

        // Checking collinearity using cross product (should be close to 0)
        double crossProd = segVec.cross(pointVec);
        if (std::abs(crossProd) > 1e-8) // small error for double
            return false;

        // Check that the point lies between start and end on x and y
        const float dotProd = segVec.dot(pointVec);
        if (dotProd < 0) return false; // “before” start
        if (dotProd > segVec.dot(segVec)) return false; // “after” end
        return true; // point on a segment
    }

    bool Vector2::is_within_radius(const Vector2 &other, const float radius) const {
        // Difference in coordinates
        const float dx = other.x - x;
        const float dy = other.y - y;

        // Square of the distance between points
        const float distanceSquared = dx * dx + dy * dy;

        // Compare with the square of the radius
        return distanceSquared <= radius * radius;
    }

    // ========== Output to stream ==========

    std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        const std::string out = "Vector2(" + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ")";
        os << out;
        return os;
    }

    // ========== Vector Operations ==========

    void Vector2::normalize() {
        float len = length();
        if (len != 0.0) {
            x /= len;
            y /= len;
        }
    }

    float Vector2::length() const {
        return std::sqrt(x * x + y * y);
    }

    float Vector2::dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // For 2D vectors, cross typically returns a pseudoscalar (the Z-component of the 3D cross product)
    float Vector2::cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }
}
