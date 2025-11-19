
#include "math/Matrix.h"
#include <stdexcept>
#include <iomanip>
#include <random>
#include <cmath>

namespace Math {
    // --- Constructors ---
    Matrix::Matrix(const size_t r, const size_t c, const double val)
        : data(r, std::vector(c, val)), rows(r), cols(c) {}

    Matrix::Matrix(const std::vector<std::vector<double>>& values)
        : data(values), rows(values.size()), cols(values[0].size()) {}


    // --- Filling methods ---
    Matrix Matrix::Identity(const size_t n) {
        Matrix I(n, n);
        for (size_t i = 0; i < n; i++) I(i, i) = 1.0;
        return I;
    }

    Matrix Matrix::Random(const size_t r, const size_t c, const double min, const double max) {
        Matrix M(r, c);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(min, max);

        for (size_t i = 0; i < r; i++)
            for (size_t j = 0; j < c; j++)
                M(i, j) = dist(gen);
        return M;
    }

    Matrix Matrix::rotationX(double a) {
        double c=cos(a), s=sin(a);
        return Matrix({{1,0,0},{0,c,-s}, {0,s,c}});
    }
    Matrix Matrix::rotationY(double a) {
        double c=cos(a), s=sin(a);
        return Matrix({{c,0,s}, {0,1,0}, {-s,0,c}});
    }
    Matrix Matrix::rotationZ(double a) {
        double c=cos(a), s=sin(a);
        return Matrix({{c,-s,0}, {s,c,0}, {0,0,1}});
    }

    // --- Arithmetic ---
    Matrix Matrix:: operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::runtime_error("Matrix size mismatch for addition");

        Matrix res(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                res(i, j) = data[i][j] + other(i, j);
        return res;
    }

    Matrix Matrix::operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols)
            throw std::runtime_error("Matrix size mismatch for subtraction");

        Matrix res(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                res(i, j) = data[i][j] - other(i, j);
        return res;
    }

    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols != other.rows)
            throw std::runtime_error("Matrix size mismatch for multiplication");

        Matrix res(rows, other.cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < other.cols; j++)
                for (size_t k = 0; k < cols; k++)
                    res(i, j) += data[i][k] * other(k, j);
        return res;
    }

    Matrix Matrix::operator*(const double scalar) const {
        Matrix res(rows, cols);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                res(i, j) = data[i][j] * scalar;
        return res;
    }


    // --- Transpose ---
    Matrix Matrix::transpose() const {
        Matrix res(cols, rows);
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                res(j, i) = data[i][j];
        return res;
    }


    // --- Determinant and inverse ---
    double Matrix::determinant() const {
        if (rows != cols)
            throw std::runtime_error("Determinant only for square matrices");

        Matrix temp = *this;
        double det = 1.0;

        for (size_t i = 0; i < rows; i++) {
            size_t pivot = i;
            for (size_t j = i + 1; j < rows; j++) {
                if (fabs(temp(j, i)) > fabs(temp(pivot, i)))
                    pivot = j;
            }
            if (fabs(temp(pivot, i)) < 1e-12) return 0.0;
            if (pivot != i) {
                std::swap(temp.data[i], temp.data[pivot]);
                det *= -1;
            }
            det *= temp(i, i);
            for (size_t j = i + 1; j < rows; j++) {
                const double factor = temp(j, i) / temp(i, i);
                for (size_t k = i; k < cols; k++)
                    temp(j, k) -= factor * temp(i, k);
            }
        }
        return det;
    }

    Matrix Matrix::inverse() const {
        if (rows != cols)
            throw std::runtime_error("Inverse only for square matrices");

        Matrix A = *this;
        Matrix I = Identity(rows);

        for (size_t i = 0; i < rows; i++) {
            const double diag = A(i, i);
            if (fabs(diag) < 1e-12)
                throw std::runtime_error("Matrix is singular!");

            for (size_t j = 0; j < cols; j++) {
                A(i, j) /= diag;
                I(i, j) /= diag;
            }

            for (size_t r = 0; r < rows; r++) {
                if (r != i) {
                    const double factor = A(r, i);
                    for (size_t c = 0; c < cols; c++) {
                        A(r, c) -= factor * A(i, c);
                        I(r, c) -= factor * I(i, c);
                    }
                }
            }
        }
        return I;
    }


    // --- Access ---
    double& Matrix::operator()(const size_t r, const size_t c) {
        return data.at(r).at(c);
    }

    double Matrix::operator()(const size_t r, const size_t c) const {
        return data.at(r).at(c);
    }

    size_t Matrix::rowCount() const { return rows; }
    size_t Matrix::colCount() const { return cols; }

    void Matrix::print(std::ostream& os) const {
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++)
                os << std::setw(10) << data[i][j] << " ";
            os << "\n";
        }
    }
}