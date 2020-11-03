//
// Created by simon on 03/03/2020.
//

#ifndef UNTITLED_VECTOR_BASE_H
#define UNTITLED_VECTOR_BASE_H

#include <cmath>
#include <functional>
#include <sstream>

#include "vector_iterator.h"

namespace gem {
template <typename T, size_t N>
class vector_base {
public:
    virtual T& operator [](size_t index) = 0;
    virtual const T& operator [](size_t index) const = 0;

    template <typename U>
    bool operator ==(const vector_base<U, N>& v) const {
        return std::equal(begin(), end(), v.begin());
    }

    template <typename U>
    bool operator !=(const vector_base<U, N>& v) const {
        return !(*this == v);
    }

    typedef vector_iterator_base<T, vector_base<T, N>*> vector_base_iterator;
    typedef vector_iterator_base<const T, const vector_base<T, N>*> const_vector_base_iterator;

    vector_base_iterator begin() { return vector_base_iterator(this, 0); }

    vector_base_iterator end() { return vector_base_iterator(this, N); }

    const_vector_base_iterator begin() const { return const_vector_base_iterator(this, 0); }

    const_vector_base_iterator end() const { return const_vector_base_iterator(this, N); }

    size_t size() const {
        return N;
    }

    template <typename U>
    T dot(const vector_base<U, N>& v) const {
        T dot = 0;
        for (auto i = 0; i < N; ++i) {
            dot += (*this)[i] * v[i];
        }
        return dot;
    }

    T length() const {
        return std::sqrt(dot(*this));
    }

    std::string to_string() const {
        std::ostringstream os;

        os << "{ ";

        for (auto e : *this) {
            os << e << " ";
        }

        os << "}";

        return std::string(os.str());
    }

    T get(const size_t& index) const {
        return (*this)[index];
    }

    void set(const size_t& index, T value) {
        (*this)[index] = value;
    }

    std::array<T, N> to_array() const {
        auto result = std::array<T, N>();
        std::copy(begin(), end(), result.begin());
        return result;
    }
};

}

#endif //UNTITLED_VECTOR_BASE_H
