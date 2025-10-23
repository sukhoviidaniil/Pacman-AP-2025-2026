//
// Created by Kaede on 2025-10-23.
//

/***************************************************************
 * Project:   ${PROJECT_NAME}
 * File:      ${FILE_NAME}
 *
 * Author:    $USER_NAME
 * #if ($ORGANIZATION_NAME && $ORGANIZATION_NAME != "")
 * Copyright (c) $YEAR ${ORGANIZATION_NAME}#if (!$ORGANIZATION_NAME.endsWith(".")).#end All rights reserved.
 * Created:   $DATE
 * Modified:  []
 *
 * Description:
 *   []
 *
 * Contact:
 *   Email:    sukhovii.daniil@gmail.com
 *
 * Disclaimer:
 *   This file is part of ${PROJECT_NAME}.
 *   Unauthorized use, reproduction, or distribution is prohibited.
***************************************************************/


#ifndef MY_SFML_VECTOR2_H
#define MY_SFML_VECTOR2_H
#include <iosfwd>


namespace Math {
    class Vector2 {
        double x=0.0, y=0.0;
    public:
        virtual ~Vector2();
        [[nodiscard]] Vector2();
        [[nodiscard]] Vector2(double x, double y);

        // ========== Arithmetic operators ==========
        Vector2 virtual operator+(const Vector2& other) const;
        Vector2 virtual operator-(const Vector2& other) const;
        Vector2 virtual operator*(const Vector2& other) const;
        Vector2 virtual operator/(const Vector2& other) const;
        Vector2 virtual operator*(double scalar) const;
        Vector2 virtual operator/(double scalar) const;

        // ========== Compound Operators ==========
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(double scalar);
        Vector2& operator/=(double scalar);

        // == Comparison ==========
        bool virtual operator==(const Vector2& other) const;

        // ========== Output to stream ==========
        friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

        // ========== Vector Operations ==========
        void virtual normalize();
        [[nodiscard]] double virtual length() const;
        [[nodiscard]] double virtual dot(const Vector2& other) const;
        [[nodiscard]] double virtual cross(const Vector2& other) const;
    };
}

#endif //MY_SFML_VECTOR2_H

