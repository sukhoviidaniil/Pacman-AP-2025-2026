#include "math/Vector3.h"

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace Math {
    Vector3::~Vector3() = default;

    Vector3::Vector3() = default;

    Vector3::Vector3(const double x, const double y, const double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3::Vector3(const std::vector<double> &vec) {
        if (vec.size() == 3) {
            this->x = vec[0];
            this->y = vec[1];
            this->z = vec[2];
            return;
        }
        if (vec.size() == 2) {
            this->x = vec[0];
            this->y = vec[1];
            this->z = 0.0;
            return;
        }
        throw std::runtime_error("Not enough/too many parameters were passed to create a Vector3.");
    }

    Vector3::Vector3(const Cartesian &c) {
        this->x = c.x;
        this->y = c.y;
        this->z = c.z;
    }

    Vector3::Vector3(const Spherical &s) {
        this->x = s.distance * std::cos(s.elevation) * std::cos(s.azimuth);
        this->y = s.distance * std::cos(s.elevation) * std::sin(s.azimuth);
        this->z = s.distance * std::sin(s.elevation);
    }

    // ========== Arithmetic operators ==========

    Vector3 Vector3::operator+(const Vector3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 Vector3::operator-(const Vector3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 Vector3::operator*(const Vector3 &other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    Vector3 Vector3::operator/(const Vector3 &other) const {
        return {x / other.x, y / other.y, z / other.z};
    }

    Vector3 Vector3::operator*(double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vector3 Vector3::operator/(double scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }

    // ========== Compound Operators ==========

    Vector3 &Vector3::operator+=(const Vector3 &other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vector3 &Vector3::operator-=(const Vector3 &other) {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    Vector3 &Vector3::operator*=(double scalar) {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    Vector3 &Vector3::operator/=(double scalar) {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    // == Comparison ==========

    bool Vector3::operator==(const Vector3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    // ========== Output to stream ==========

    std::ostream &operator<<(std::ostream &os, const Vector3 &vector3) {
        const std::string out = "Vector3(" + std::to_string(vector3.x) + ", " + std::to_string(vector3.y) + ", " + std::to_string(vector3.z) + ")";
        os << out;
        return os;
    }

    // ========== Vector Operations ==========

    void Vector3::normalize() {
        if (const double len = length(); len > 1e-8) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    double Vector3::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double Vector3::dot(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 Vector3::cross(const Vector3 &other) const {
        double t_x = y * other.z - z * other.y;
        double t_y = z * other.x - x * other.z;
        double t_z = x * other.y - y * other.x;
        return {t_x, t_y, t_z};
    }
}
