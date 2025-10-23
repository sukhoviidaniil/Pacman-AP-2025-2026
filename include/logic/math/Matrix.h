//
// Created by Kaede on 2025-08-31.
//

#ifndef GENGINE_MATRIX_H
#define GENGINE_MATRIX_H
#include <iosfwd>
#include <iostream>
#include <vector>

namespace Math {
    class Matrix {
        std::vector<std::vector<double>> data;
        size_t rows, cols;
    public:
        // --- Constructors ---
        Matrix(size_t r, size_t c, double val = 0.0);
        explicit Matrix(const std::vector<std::vector<double>>& values);

        // --- Filling methods ---
        static Matrix Identity(size_t n);
        static Matrix Random(size_t r, size_t c, double min = 0.0, double max = 1.0);

        static Matrix rotationX(double a);
        static Matrix rotationY(double a);
        static Matrix rotationZ(double a);


        // --- Arithmetic ---
        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;
        Matrix operator*(const Matrix& other) const;
        Matrix operator*(double scalar) const;

        // --- Transpose ---
        [[nodiscard]] Matrix transpose() const;

        // --- Determinant and inverse ---
        [[nodiscard]] double determinant() const;
        [[nodiscard]] Matrix inverse() const;

        // --- Access ---
        double& operator()(size_t r, size_t c);
        double operator()(size_t r, size_t c) const;
        [[nodiscard]] size_t rowCount() const;
        [[nodiscard]] size_t colCount() const;
        void print(std::ostream& os = std::cout) const;
    };
}


#endif //GENGINE_MATRIX_H