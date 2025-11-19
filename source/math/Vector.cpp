#include "math/Vector.h"

#include <cmath>
#include <stdexcept>

namespace Math {
    void Vector::same_dimension(const Vector &other, const std::string &op) const {
        if (this->dimension() != other.dimension()) {
            const std::string err = "Vectors are not in the same dimension at the time the statement is executed:" + op + ";";
            throw std::invalid_argument(err);
        }
    }

    Vector::~Vector() = default;

    Vector::Vector() {
        data = {0,0,0};
    }

    Vector::Vector(const std::vector<double> &vec) {
        data = vec;
    }

    Vector Vector::Zeros_Vector(const std::size_t n) {
        const std::vector <double> vec (n,0);
        return Vector(vec);
    }

    Vector Vector::Ones_Vector(const std::size_t n){
        const std::vector <double> vec (n,1);
        return Vector(vec);
    }

    int Vector::dimension() const {
        return data.size();
    }

    Vector Vector::operator+(const Vector &other) const {
        this->same_dimension(other, "Vector::operator+");
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] + other.data[i];
        }
        return res;
    }

    Vector Vector::operator-(const Vector &other) const {
        this->same_dimension(other, "Vector::operator-");
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] - other.data[i];
        }
        return res;
    }

    Vector Vector::operator*(const Vector &other) const {
        this->same_dimension(other, "Vector::operator*");
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] * other.data[i];
        }
        return res;
    }

    Vector Vector::operator/(const Vector &other) const {
        this->same_dimension(other, "Vector::operator/");
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] / other.data[i];
        }
        return res;
    }

    Vector Vector::operator*(double scalar) const {
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] * scalar;
        }
        return res;
    }

    Vector Vector::operator/(double scalar) const {
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] / scalar;
        }
        return res;
    }

    Vector & Vector::operator+=(const Vector &other) {
        this->same_dimension(other, "Vector::operator+=");
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] + other.data[i];
        }
        return *this;
    }

    Vector & Vector::operator-=(const Vector &other) {
        this->same_dimension(other, "Vector::operator-=");
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] - other.data[i];
        }
        return *this;
    }

    Vector & Vector::operator*=(double scalar) {
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] * scalar;
        }
        return *this;
    }

    Vector & Vector::operator/=(double scalar) {
        Vector res = Vector();
        for (size_t i = 0; i < this->dimension(); i++) {
            res.data[i] = data[i] / scalar;
        }
        return *this;
    }

    bool Vector::operator==(const Vector &other) const {
        this->same_dimension(other, "Vector::operator==");
        for (size_t i = 0; i < this->dimension(); i++) {
            if (data[i] == other.data[i]) {
                return false;
            }
        }
        return true;
    }

    std::ostream & operator<<(std::ostream &os, const Vector &Vector) {
        // TODO
    }

    void Vector::normalize() {
        if (const double len = length(); len > 1e-8) {
            for (size_t i = 0; i < this->dimension(); i++) {
                data[i] /= len;
            }
        }
    }

    double Vector::length() const {
        double res = 0;
        for (size_t i = 0; i < this->dimension(); i++) {
            res += data[i] * data[i];
        }
        return std::sqrt(res);
    }

    double Vector::dot(const Vector &other) const {
        this->same_dimension(other, "Vector::dot");
        double res = 0;
        for (size_t i = 0; i < this->dimension(); i++) {
            res += data[i] * other.data[i];
        }
        return res;
    }

    Vector Vector::cross(const Vector &other) const {
        // TODO
    }

    double Vector::angle_between(const Vector &other) const {
        const double cos_fi = this->dot(other)/(this->length()*other.length());
        return acos(cos_fi);
    }
}
