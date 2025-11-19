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
#include <functional>
#include <iosfwd>


namespace Math {
    class Vector2 {
    public:
        float x=0.0, y=0.0;

        virtual ~Vector2();
        [[nodiscard]] Vector2();
        [[nodiscard]] Vector2(float x, float y);

        // ========== Arithmetic operators ==========
        virtual Vector2 operator+(const Vector2& other) const;
        virtual Vector2 operator-(const Vector2& other) const;
        virtual Vector2 operator*(const Vector2& other) const;
        virtual Vector2 operator/(const Vector2& other) const;
        virtual Vector2 operator*(float scalar) const;
        virtual Vector2 operator/(float scalar) const;

        // ========== Compound Operators ==========
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(float scalar);
        Vector2& operator/=(float scalar);

        // == Comparison ==========
        virtual bool operator==(const Vector2& other) const;
        [[nodiscard]] bool is_between(const Vector2& start, const Vector2& end) const;
        [[nodiscard]] bool is_within_radius(const Vector2& other, float radius) const;

        // ========== Output to stream ==========
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

        // ========== Vector Operations ==========
        virtual void normalize();
        [[nodiscard]] virtual float length() const;
        [[nodiscard]] virtual float dot(const Vector2& other) const;
        [[nodiscard]] virtual float cross(const Vector2& other) const;
    };

    // TODO Vector2Hash
    struct Vector2Hash {
        std::size_t operator()(const Vector2& v) const noexcept {
            return std::hash<int>{}(v.x) ^ (std::hash<int>{}(v.y) << 1);
        }
    };
}

#endif //MY_SFML_VECTOR2_H

