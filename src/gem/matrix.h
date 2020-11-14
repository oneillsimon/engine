//
// Created by simon on 11/04/2020.
//

#include <algorithm>
#include <array>
#include <cstring>
#include <numeric>
#include <sstream>

#include "angle.h"
#include "vector.h"

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

namespace gem {
template <typename T, size_t Rows, size_t Columns>
class matrix {
private:
    vector<vector<T, Columns>, Rows> values;

public:
    matrix() {
        fill(0);
    };

    explicit matrix(const std::initializer_list<std::initializer_list<T>>& list) {
        auto index = 0;

        for (auto l : list) {
            std::copy(l.begin(), l.end(), values[index++].begin());
        }
    }

    void fill(T value) {
        std::for_each(
                values.begin(), values.end(), [value](auto& column) {
                  std::fill(column.begin(), column.end(), value);
                }
        );
    }

    T get(size_t row, size_t column) const {
        return values[row][column];
    }

    void set(size_t row, size_t column, const T& value) {
        values[row][column] = value;
    }

    typename vector<vector<T, Columns>, Rows>::vector_base_iterator begin() {
        return values.begin();
    }

    typename vector<vector<T, Columns>, Rows>::const_vector_base_iterator begin() const {
        return values.begin();
    }

    typename vector<vector<T, Columns>, Rows>::vector_base_iterator end() {
        return values.end();
    }

    typename vector<vector<T, Columns>, Rows>::const_vector_base_iterator end() const {
        return values.end();
    }

    vector<T, Columns> operator [](size_t index) const {
        return values[index];
    }

    vector<T, Columns>& operator [](size_t index) {
        return values[index];
    }

    template <typename U>
    bool operator ==(const matrix<U, Rows, Columns>& m) const {
        for (auto i = 0; i < Rows; ++i) {
            if (values[i] != m[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename U>
    bool operator !=(const matrix<U, Rows, Columns>& m) const {
        return !(*this == m);
    }

    template <typename U>
    matrix<T, Rows, Columns> operator +(const matrix<U, Rows, Columns>& m) const {
        auto result = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i] + m[i];
        }
        return result;
    }

    template <typename U>
    matrix<T, Rows, Columns> operator -(const matrix<U, Rows, Columns>& m) const {
        auto result = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i] - m[i];
        }
        return result;
    }

    template <typename U, size_t R, size_t C>
    matrix<T, Rows, C> operator *(const matrix<U, R, C>& m) const {
        auto result = matrix<T, Rows, C>();

        for (auto i = 0; i < Rows; ++i) {
            for (auto j = 0; j < C; ++j) {
                result[i][j] = row(i).dot(m.column(j));
            }
        }
        return result;
    }

    template <typename U>
    void operator +=(const matrix<U, Rows, Columns>& m) {
        *this = *this + m;
    }

    template <typename U>
    void operator -=(const matrix<U, Rows, Columns>& m) {
        *this = *this - m;
    }

    matrix<T, Rows, Columns> operator +(const T& scalar) const {
        auto result = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i] + scalar;
        }
        return result;
    }

    matrix<T, Rows, Columns> operator -(const T& scalar) const {
        auto result = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i] - scalar;
        }
        return result;
    }

    matrix<T, Rows, Columns> operator *(const T& scalar) const {
        auto result = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i] * scalar;
        }
        return result;
    }

    matrix<T, Rows, Columns> operator /(const T& scalar) const {
        auto result = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i] / scalar;
        }
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

    static matrix<T, Rows, Columns> identity() {
        auto identity = matrix<T, Rows, Columns>();
        for (auto i = 0; i < Rows; i++) {
            identity[i][i] = static_cast<T>(1);
        }
        return identity;
    }

    vector<T, Columns> row(size_t index) const {
        return values[index];
    }

    vector<T, Rows> column(size_t index) const {
        auto result = gem::vector<T, Rows>();
        for (auto i = 0; i < Rows; ++i) {
            result[i] = values[i][index];
        }
        return result;
    }

    std::string to_string() const {
        std::ostringstream os;

        for (auto i = 0; i < Rows; ++i) {
            os << std::endl << "{ ";
            for (auto j = 0; j < Columns; ++j) {
                os << values[i][j] << " ";
            }
            os << "}";
        }
        return std::string(os.str());
    }
};

template <typename T>
class matrix2 : public matrix<T, 2, 2> {
public:
    using matrix<T, 2, 2>::matrix;
};

template <typename T>
class matrix3 : public matrix<T, 3, 3> {
public:
    using matrix<T, 3, 3>::matrix;
};

typedef matrix2<float> matrix2f;
typedef matrix2<int> matrix2i;

typedef matrix3<float> matrix3f;
typedef matrix3<int> matrix3i;
}

#endif //UNTITLED_MATRIX_H
