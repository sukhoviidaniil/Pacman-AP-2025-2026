/***************************************************************
 * Project:       Pacman
 * File:          Vector2.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-10-23
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
#ifndef MY_SFML_VECTOR2_H
#define MY_SFML_VECTOR2_H

#include "Point2.h"
#include <functional>

namespace math {
    class Vector2{
    public:
        float x=0.0, y=0.0;

        virtual ~Vector2();
        [[nodiscard]] Vector2();
        [[nodiscard]] Vector2(float x, float y);
        [[nodiscard]] explicit Vector2(const Point2& p);

        [[nodiscard]] Point2 to_Point2() const;

        // ========== Arithmetic operators ==========
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(const Vector2& other) const;
        Vector2 operator/(const Vector2& other) const;
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;

        // ========== Compound Operators ==========
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(float scalar);
        Vector2& operator/=(float scalar);

        // == Comparison ==========
        bool operator==(const Vector2& other) const;
        [[nodiscard]] bool is_between(const Vector2& start, const Vector2& end) const;
        [[nodiscard]] bool is_within_radius(const Vector2& other, float radius) const;
        [[nodiscard]] bool has_same_direction(const Vector2& other) const;

        // ========== Output to stream ==========
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

        // ========== Vector Operations ==========
        void normalize();
        [[nodiscard]] float length() const;
        [[nodiscard]] float dot(const Vector2& other) const;
        [[nodiscard]] float cross(const Vector2& other) const;
    };

    struct Vector2Hash {
        std::size_t operator()(const Vector2& v) const noexcept {
            return std::hash<int>{}(static_cast<int>(v.x)) ^ std::hash<int>{}(static_cast<int>(v.y)) << 1;
        }
    };
}

#endif //MY_SFML_VECTOR2_H

