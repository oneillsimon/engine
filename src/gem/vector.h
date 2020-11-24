//
// Created by simon on 09/05/2020.
//

#ifndef UNTITLED_VECTOR_H
#define UNTITLED_VECTOR_H

#include <algorithm>
#include <vector>

#include "vector_base.h"
#include "vector_iterator.h"

namespace gem {
template <typename T>
class vector2;

template <typename T>
class vector3;

template <typename T>
class vector4;

template <typename T, size_t N>
class vector : public vector_base<T, N> {
private:
    std::array<T, N> values;

    void assign_values(const std::vector<T>& values) {
        std::copy_n(values.begin(), N, this->values.begin());
    }

public:
    vector() = default;;

    explicit vector(const std::array<T, N>& values) {
        assign_values(std::vector<T>(values.begin(), values.end()));
    };

    explicit vector(const std::vector<T>& values) {
        assign_values(values);
    };

    explicit vector(const std::initializer_list<T>& values) {
        assign_values(values);
    };

    T& operator [](size_t index) override {
        return values[index];
    };

    const T& operator [](size_t index) const override {
        return values[index];
    };

    vector<T, N> operator -() const {
        auto result = vector<T, N>();
        std::transform(this->begin(), this->end(), result.begin(), std::negate<T>());
        return result;
    }

    template <typename U, size_t M>
    vector<T, N> operator +(const vector<U, M>& v) const {
        auto result = vector<T, N>();
        std::transform(this->begin(), this->end(), v.begin(), result.begin(), std::plus<T>());
        return result;
    }

    template <typename U, size_t M>
    vector<T, N> operator -(const vector<U, M>& v) const {
        auto result = vector<T, N>();
        std::transform(this->begin(), this->end(), v.begin(), result.begin(), std::minus<T>());
        return result;
    }

    template <typename U, size_t M>
    vector<T, N> operator *(const vector<U, M>& v) const {
        auto result = vector<T, N>();
        std::transform(this->begin(), this->end(), v.begin(), result.begin(), std::multiplies<T>());
        return result;
    }

    template <typename U, size_t M>
    vector<T, N> operator /(const vector<U, M>& v) const {
        auto result = vector<T, N>();
        std::transform(this->begin(), this->end(), v.begin(), result.begin(), std::divides<T>());
        return result;
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

    template <typename U, size_t M>
    vector<T, N> operator +(const vector_base<U, M>& v) const {
        return *this + vector<U, M>(v.to_array());
    }

    template <typename U, size_t M>
    vector<T, N> operator -(const vector_base<U, M>& v) const {
        return *this - vector<U, M>(v.to_array());
    }

    template <typename U, size_t M>
    vector<T, N> operator *(const vector_base<U, M>& v) const {
        return *this * vector<U, M>(v.to_array());
    }

    template <typename U, size_t M>
    vector<T, N> operator /(const vector_base<U, M>& v) const {
        return *this / vector<U, M>(v.to_array());
    }

    template <typename U, size_t M>
    void operator +=(const vector_base<U, M>& v) {
        *this = *this + v;
    }

    template <typename U, size_t M>
    void operator -=(const vector_base<U, M>& v) {
        *this = *this - v;
    }

    template <typename U, size_t M>
    void operator *=(const vector_base<U, M>& v) {
        *this = *this * v;
    }

    template <typename U, size_t M>
    void operator /=(const vector_base<U, M>& v) {
        *this = *this / v;
    }

    vector<T, N> operator +(const T& scalar) const {
        auto result = *this;
        std::transform(result.begin(), result.end(), result.begin(), [scalar](T& e) { e += scalar; return e; });
        return result;
    }

    vector<T, N> operator -(const T& scalar) const {
        auto result = *this;
        std::transform(result.begin(), result.end(), result.begin(), [scalar](T& e) { e -= scalar; return e; });
        return result;
    }

    vector<T, N> operator *(const T& scalar) const {
        auto result = *this;
        std::transform(result.begin(), result.end(), result.begin(), [scalar](T& e) { e *= scalar; return e; });
        return result;
    }

    vector<T, N> operator /(const T& scalar) const {
        auto result = *this;
        std::transform(result.begin(), result.end(), result.begin(), [scalar](T& e) { e /= scalar; return e; });
        return result;
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
};
}

#endif//UNTITLED_VECTOR_H
