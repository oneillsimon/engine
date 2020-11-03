//
// Created by simon on 10/05/2020.
//

#ifndef UNTITLED_VECTOR_ITERATOR_H
#define UNTITLED_VECTOR_ITERATOR_H

#include <iterator>

template <typename T, typename vector_type>
class vector_iterator_base {
private:
    vector_type vector;
    size_t index;
public:
    using difference_type = T;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::output_iterator_tag;

    explicit vector_iterator_base(vector_type v, size_t index = 0): vector(v), index(index) {}

    vector_iterator_base& operator ++() {
        index++;
        return *this;
    }

    vector_iterator_base operator ++(int) {
        auto iter = *this;
        ++(*this);
        return iter;
    }

    bool operator ==(const vector_iterator_base& other) const {
        return index == other.index;
    }

    bool operator !=(const vector_iterator_base& other) const {
        return !(*this == other);
    }

    T& operator *() {
        return (*vector)[index];
    }

    const T& operator *() const {
        return (*vector)[index];
    }
};

#endif //UNTITLED_VECTOR_ITERATOR_H
