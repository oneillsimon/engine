//
// Created by simon on 09/05/2020.
//

#ifndef UNTITLED_VECTOR4_H
#define UNTITLED_VECTOR4_H

#include "vector_base.h"

namespace gem {
template <typename T, size_t N>
class vector;

template <typename T>
class vector2;

template <typename T>
class vector3;

template <typename T>
class vector4 : public vector_base<T, 4> {
public:
    T x;
    T y;
    T z;
    T w;

    vector4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {};

    explicit vector4(const T& scalar): vector4<T>(scalar, scalar, scalar, scalar) {};

    explicit vector4(const std::array<T, 4>& array): vector4<T>(array[0], array[1], array[2], array[3]) {}

    vector4(): vector4<T>(0) {};

    virtual T& operator [](size_t index) override {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            default:
                throw std::out_of_range("No such index '" + std::to_string(index) + "' in vector4");
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
            case 3:
                return w;
            default:
                throw std::out_of_range("No such index '" + std::to_string(index) + "' in vector4");
        }
    }

    template <typename U, size_t M>
    vector4<T> operator +(const vector<U, M>& v) const {
        return vector3<T>(x + v.get(0), y + v.get(1), z + v.get(2), w + v.get(3));
    }

    template <typename U, size_t M>
    vector4<T> operator -(const vector<U, M>& v) const {
        return vector3<T>(x - v.get(0), y - v.get(1), z - v.get(2), w - v.get(3));
    }

    template <typename U, size_t M>
    vector4<T> operator *(const vector<U, M>& v) const {
        return vector3<T>(x * v.get(0), y * v.get(1), z * v.get(2), w * v.get(3));
    }

    template <typename U, size_t M>
    vector4<T> operator /(const vector<U, M>& v) const {
        return vector3<T>(x / v.get(0), y / v.get(1), z / v.get(2), w / v.get(3));
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
    vector4<T> operator +(const vector2<U>& v) const {
        return vector4<T>(x + v.x, y + v.y, z, w);
    }

    template <typename U>
    vector4<T> operator -(const vector2<U>& v) const {
        return vector4<T>(x - v.x, y - v.y, z, w);
    }

    template <typename U>
    vector4<T> operator *(const vector2<U>& v) const {
        return vector4<T>(x * v.x, y * v.y, z, w);
    }

    template <typename U>
    vector4<T> operator /(const vector2<U>& v) const {
        return vector4<T>(x / v.x, y / v.y, z, w);
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
    vector4<T> operator +(const vector3<U>& v) const {
        return vector4<T>(x + v.x, y + v.y, z + v.z, w);
    }

    template <typename U>
    vector4<T> operator -(const vector3<U>& v) const {
        return vector4<T>(x - v.x, y - v.y, z - v.z, w);
    }

    template <typename U>
    vector4<T> operator *(const vector3<U>& v) const {
        return vector4<T>(x * v.x, y * v.y, z * v.z, w);
    }

    template <typename U>
    vector4<T> operator /(const vector3<U>& v) const {
        return vector4<T>(x / v.x, y / v.y, z / v.z, w);
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
    vector4<T> operator +(const vector4<U>& v) const {
        return vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    template <typename U>
    vector4<T> operator -(const vector4<U>& v) const {
        return vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
    }

    template <typename U>
    vector4<T> operator *(const vector4<U>& v) const {
        return vector4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
    }

    template <typename U>
    vector4<T> operator /(const vector4<U>& v) const {
        return vector4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
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

    vector4<T> operator +(const T& scalar) const {
        return vector4<T>(x + scalar, y + scalar, z + scalar, w + scalar);
    }

    vector4<T> operator -(const T& scalar) const {
        return vector4<T>(x - scalar, y - scalar, z - scalar, w - scalar);
    }

    vector4<T> operator *(const T& scalar) const {
        return vector4<T>(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    vector4<T> operator /(const T& scalar) const {
        return vector4<T>(x / scalar, y / scalar, z / scalar, w / scalar);
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

    vector4<T> normalise() const {
        return *this / this->length();
    }
};
}

#endif //UNTITLED_VECTOR4_H
