//
// Created by simon on 08/05/2020.
//

#ifndef UNTITLED_VECTOR3_H
#define UNTITLED_VECTOR3_H

#include <ostream>
#include "vector_base.h"

namespace gem {
template <typename T, size_t N>
class vector;

template <typename T>
class vector2;

template <typename T>
class vector4;

template <typename T>
class vector3 : public vector_base<T, 3> {
public:
    T x;
    T y;
    T z;

    vector3(T x, T y, T z): x(x), y(y), z(z) {};

    explicit vector3(const T& scalar): vector3<T>(scalar, scalar, scalar) {};

    explicit vector3(const std::array<T, 3>& array): vector3<T>(array[0], array[1], array[2]) {}

    vector3(): vector3<T>(0) {};

    virtual T& operator [](size_t index) override {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw std::out_of_range("No such index '" + std::to_string(index) + "' in vector3");
        }
    }

    virtual const T& operator [](size_t index) const override {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw std::out_of_range("No such index '" + std::to_string(index) + "' in vector3");
        }
    }

    template <typename U, size_t M>
    vector3<T> operator +(const vector<U, M>& v) const {
        return vector3<T>(x + v.get(0), y + v.get(1), z + v.get(2));
    }

    template <typename U, size_t M>
    vector3<T> operator -(const vector<U, M>& v) const {
        return vector3<T>(x - v.get(0), y - v.get(1), z - v.get(2));
    }

    template <typename U, size_t M>
    vector3<T> operator *(const vector<U, M>& v) const {
        return vector3<T>(x * v.get(0), y * v.get(1), z * v.get(2));
    }

    template <typename U, size_t M>
    vector3<T> operator /(const vector<U, M>& v) const {
        return vector3<T>(x / v.get(0), y / v.get(1), z / v.get(2));
    }

    template <typename U, size_t M>
    void operator +=(const vector<U, M>& v) {
        *this = *this + v;
    }

    template <typename U, size_t M>
    void operator -=(const vector<U, M>& v) {
        *this = *this - v;
    }

    template <typename U, size_t M>
    void operator *=(const vector<U, M>& v) {
        *this = *this * v;
    }

    template <typename U, size_t M>
    void operator /=(const vector<U, M>& v) {
        *this = *this / v;
    }

    template <typename U>
    vector3<T> operator +(const vector2<U>& v) const {
        return vector3<T>(x + v.x, y + v.y, z);
    }

    template <typename U>
    vector3<T> operator -(const vector2<U>& v) const {
        return vector3<T>(x - v.x, y - v.y, z);
    }

    template <typename U>
    vector3<T> operator *(const vector2<U>& v) const {
        return vector3<T>(x * v.x, y * v.y, z);
    }

    template <typename U>
    vector3<T> operator /(const vector2<U>& v) const {
        return vector3<T>(x / v.x, y / v.y, z);
    }

    template <typename U>
    void operator +=(const vector2<U>& v) {
        *this = *this + v;
    }

    template <typename U>
    void operator -=(const vector2<U>& v) {
        *this = *this - v;
    }

    template <typename U>
    void operator *=(const vector2<U>& v) {
        *this = *this * v;
    }

    template <typename U>
    void operator /=(const vector2<U>& v) {
        *this = *this / v;
    }

    template <typename U>
    vector3<T> operator +(const vector3<U>& v) const {
        return vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    template <typename U>
    vector3<T> operator -(const vector3<U>& v) const {
        return vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    template <typename U>
    vector3<T> operator *(const vector3<U>& v) const {
        return vector3<T>(x * v.x, y * v.y, z * v.z);
    }

    template <typename U>
    vector3<T> operator /(const vector3<U>& v) const {
        return vector3<T>(x / v.x, y / v.y, z / v.z);
    }

    template <typename U>
    void operator +=(const vector3<U>& v) {
        *this = *this + v;
    }

    template <typename U>
    void operator -=(const vector3<U>& v) {
        *this = *this - v;
    }

    template <typename U>
    void operator *=(const vector3<U>& v) {
        *this = *this * v;
    }

    template <typename U>
    void operator /=(const vector3<U>& v) {
        *this = *this / v;
    }

    template <typename U>
    vector3<T> operator +(const vector4<U>& v) const {
        return vector3<T>(x + v.x, y + v.y, z + v.z);
    }

    template <typename U>
    vector3<T> operator -(const vector4<U>& v) const {
        return vector3<T>(x - v.x, y - v.y, z - v.z);
    }

    template <typename U>
    vector3<T> operator *(const vector4<U>& v) const {
        return vector3<T>(x * v.x, y * v.y, z * v.z);
    }

    template <typename U>
    vector3<T> operator /(const vector4<U>& v) const {
        return vector3<T>(x / v.x, y / v.y, z / v.z);
    }

    template <typename U>
    void operator +=(const vector4<U>& v) {
        *this = *this + v;
    }

    template <typename U>
    void operator -=(const vector4<U>& v) {
        *this = *this - v;
    }

    template <typename U>
    void operator *=(const vector4<U>& v) {
        *this = *this * v;
    }

    template <typename U>
    void operator /=(const vector4<U>& v) {
        *this = *this / v;
    }

    vector3<T> operator +(const T& scalar) const {
        return vector3<T>(x + scalar, y + scalar, z + scalar);
    }

    vector3<T> operator -(const T& scalar) const {
        return vector3<T>(x - scalar, y - scalar, z - scalar);
    }

    vector3<T> operator *(const T& scalar) const {
        return vector3<T>(x * scalar, y * scalar, z * scalar);
    }

    vector3<T> operator /(const T& scalar) const {
        return vector3<T>(x / scalar, y / scalar, z / scalar);
    }

    void operator +=(const T& scalar) {
        *this = *this + scalar;
    }

    void operator -=(const T& scalar) {
        *this = *this - scalar;
    }

    void operator *=(const T& scalar) {
        *this = *this * scalar;
    }

    void operator /=(const T& scalar) {
        *this = *this / scalar;
    }

    template <typename U>
    vector3<T> cross(const vector3<U>& v) const {
        return vector3<T>{ y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
    }

    vector3<T> normalise() const {
        return *this / this->length();
    }
};
}

#endif //UNTITLED_VECTOR3_H
