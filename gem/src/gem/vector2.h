//
// Created by simon on 09/05/2020.
//

#ifndef UNTITLED_VECTOR2_H
#define UNTITLED_VECTOR2_H

#include "vector_base.h"
#include "vector_iterator.h"

namespace gem {
template <typename T, size_t N>
class vector;

template <typename T>
class vector3;

template <typename T>
class vector4;

template <typename T>
class vector2 : public vector_base<T, 2> {
public:
    T x;
    T y;

    explicit vector2(const vector_base<T, 2>& v): x(v[0]), y(v[1]) {}

    explicit vector2(const std::array<T, 2>& array): vector2<T>(array[0], array[1]) {}

    explicit vector2(const T& scalar): vector2<T>(scalar, scalar) {};

    vector2(T x, T y): x(x), y(y) {};

    vector2(): vector2<T>(0) {};

    T& operator [](size_t index) override {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                throw std::out_of_range("No such index '" + std::to_string(index) + "' in vector2");
        }
    }

    const T& operator [](size_t index) const override {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                throw std::out_of_range("No such index '" + std::to_string(index) + "' in vector2");
        }
    }

    template <typename U, size_t M>
    vector2<T> operator +(const vector<U, M>& v) const {
        return vector2<T>(x + v.get(0), y + v.get(1));
    }

    template <typename U, size_t M>
    vector2<T> operator -(const vector<U, M>& v) const {
        return vector2<T>(x - v.get(0), y - v.get(1));
    }

    template <typename U, size_t M>
    vector2<T> operator *(const vector<U, M>& v) const {
        return vector2<T>(x * v.get(0), y * v.get(1));
    }

    template <typename U, size_t M>
    vector2<T> operator /(const vector<U, M>& v) const {
        return vector2<T>(x / v.get(0), y / v.get(1));
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
    vector2<T> operator +(const vector2<U>& v) const {
        return vector2<T>(x + v.x, y + v.y);
    }

    template <typename U>
    vector2<T> operator -(const vector2<U>& v) const {
        return vector2<T>(x - v.x, y - v.y);
    }

    template <typename U>
    vector2<T> operator *(const vector2<U>& v) const {
        return vector2<T>(x * v.x, y * v.y);
    }

    template <typename U>
    vector2<T> operator /(const vector2<U>& v) const {
        return vector2<T>(x / v.x, y / v.y);
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
    vector2<T> operator +(const vector3<U>& v) const {
        return vector2<T>(x + v.x, y + v.y);
    }

    template <typename U>
    vector2<T> operator -(const vector3<U>& v) const {
        return vector2<T>(x - v.x, y - v.y);
    }

    template <typename U>
    vector2<T> operator *(const vector3<U>& v) const {
        return vector2<T>(x * v.x, y * v.y);
    }

    template <typename U>
    vector2<T> operator /(const vector3<U>& v) const {
        return vector2<T>(x / v.x, y / v.y);
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
    vector2<T> operator +(const vector4<U>& v) const {
        return vector2<T>(x + v.x, y + v.y);
    }

    template <typename U>
    vector2<T> operator -(const vector4<U>& v) const {
        return vector2<T>(x - v.x, y - v.y);
    }

    template <typename U>
    vector2<T> operator *(const vector4<U>& v) const {
        return vector2<T>(x * v.x, y * v.y);
    }

    template <typename U>
    vector2<T> operator /(const vector4<U>& v) const {
        return vector2<T>(x / v.x, y / v.y);
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

    vector2<T> operator +(const T& scalar) const {
        return vector2<T>(x + scalar, y + scalar);
    }

    vector2<T> operator -(const T& scalar) const {
        return vector2<T>(x - scalar, y - scalar);
    }

    vector2<T> operator *(const T& scalar) const {
        return vector2<T>(x * scalar, y * scalar);
    }

    vector2<T> operator /(const T& scalar) const {
        return vector2<T>(x / scalar, y / scalar);
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

    vector2<T> normalise() const {
        return *this / this->length();
    }
};
}

#endif //UNTITLED_VECTOR2_H
