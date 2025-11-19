/***************************************************************
 * Project:       Pacman
 * File:          Vector.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-09-24
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

#ifndef MAL_VECTOR_H
#define MAL_VECTOR_H
#include <iosfwd>
#include <vector>

namespace Math {
    class Vector {
        std::vector<double> data;
        void same_dimension(const Vector& other, const std::string &op) const;
        public:
        virtual ~Vector();
        [[nodiscard]] Vector();
        [[nodiscard]] explicit Vector(const std::vector<double> &vec);

        // --- Filling methods ---
        static Vector Zeros_Vector(std::size_t n);
        static Vector Ones_Vector(std::size_t n);

        [[nodiscard]] int dimension() const;
        // Operators
        Vector virtual operator+(const Vector& other) const;
        Vector virtual operator-(const Vector& other) const;
        Vector virtual operator*(const Vector& other) const;
        Vector virtual operator/(const Vector& other) const;
        Vector virtual operator*(double scalar) const;
        Vector virtual operator/(double scalar) const;
        Vector& operator+=(const Vector& other);
        Vector& operator-=(const Vector& other);
        Vector& operator*=(double scalar);
        Vector& operator/=(double scalar);
        bool virtual operator==(const Vector& other) const;

        friend std::ostream &operator<<(std::ostream &os, const Vector &Vector);

        // Vector operation, normalization and length
        void virtual normalize();
        [[nodiscard]] double virtual length() const;

        /** Inner product of two vectors
         *
         * @param other
         * @return
         */
        [[nodiscard]] double virtual dot(const Vector& other) const;
        [[nodiscard]] Vector virtual cross(const Vector& other) const;
        [[nodiscard]] double virtual angle_between(const Vector& other) const;

    };
}


#endif //MAL_VECTOR_H