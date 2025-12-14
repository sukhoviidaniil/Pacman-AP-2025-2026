/***************************************************************
 * Project:       Pacman
 * File:          Point2.h
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
#ifndef PACMAN_POINT2_H
#define PACMAN_POINT2_H

#include <iosfwd>

namespace math {
    class Point2 {
    public:
        float x=0.0, y=0.0;

        virtual ~Point2();
        [[nodiscard]] Point2();
        [[nodiscard]] Point2(float x, float y);

        // ========== Arithmetic operators ==========
        Point2 operator*(float scalar) const;
        Point2 operator/(float scalar) const;
        Point2 operator+(const Point2& other) const;
        Point2 operator-(const Point2& other) const;
        Point2 operator*(const Point2& other) const;
        Point2 operator/(const Point2& other) const;

        // ========== Compound Operators ==========
        Point2& operator*=(float scalar);
        Point2& operator/=(float scalar);
        Point2& operator+=(const Point2& other);
        Point2& operator-=(const Point2& other);

        // == Comparison ==========
        bool operator==(const Point2& other) const;

        // ========== Output to stream ==========
        friend std::ostream& operator<<(std::ostream& os, const Point2& vector);
    };
}

#endif //PACMAN_POINT2_H