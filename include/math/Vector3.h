/***************************************************************
 * Project:       Pacman
 * File:          Vector.h
 *
 * Author:        Sukhovii Daniil
 * Created:       2025-08-31
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
#ifndef GENGINE_Vector3_H
#define GENGINE_Vector3_H
#include <iosfwd>
#include <vector>

namespace Math {
    struct Cartesian {
        double x=0.0, y=0.0, z=0.0;
    };

    struct Spherical {
        double distance=0.0, elevation=0.0, azimuth=0.0;
    };

    class Vector3 : public Cartesian {
        //double x=0.0, y=0.0, z=0.0;
        public:

        virtual ~Vector3();
        [[nodiscard]] Vector3();
        [[nodiscard]] Vector3(double x, double y, double z);
        [[nodiscard]] explicit Vector3(const std::vector<double> &vec);
        [[nodiscard]] explicit Vector3(const Cartesian& c);
        [[nodiscard]] explicit Vector3(const Spherical& s);

        // ========== Arithmetic operators ==========
        Vector3 virtual operator+(const Vector3& other) const;
        Vector3 virtual operator-(const Vector3& other) const;
        Vector3 virtual operator*(const Vector3& other) const;
        Vector3 virtual operator/(const Vector3& other) const;
        Vector3 virtual operator*(double scalar) const;
        Vector3 virtual operator/(double scalar) const;

        // ========== Compound Operators ==========
        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator*=(double scalar);
        Vector3& operator/=(double scalar);

        // == Comparison ==========
        bool virtual operator==(const Vector3& other) const;

        // ========== Output to stream ==========
        friend std::ostream& operator<<(std::ostream& os, const Vector3& vector3);

        // ========== Vector Operations ==========
        void virtual normalize();
        [[nodiscard]] double virtual length() const;
        [[nodiscard]] double virtual dot(const Vector3& other) const;
        [[nodiscard]] Vector3 virtual cross(const Vector3& other) const;
    };
}

#endif //GENGINE_Vector3_H