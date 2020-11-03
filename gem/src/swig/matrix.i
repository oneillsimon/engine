%module gem
%{
#include <gem/matrix.h>
%};

%import <gem/matrix.h>

%include "std_string.i"
%include <gem/vector.h>
%include <gem/vector_iterator.h>

%extend gem::matrix {
        std::string __str__() {
            return $self->to_string();
        }

        template<typename T, size_t N>
        gem::vector<T, N> __getitem__ (int index) const {
            printf("Woohoo");
            return $self->row(index);
        }
};

%template(matrix2i) gem::matrix<int, 2, 2>;
%template(matrix2f) gem::matrix<float, 2, 2>;
%template(matrix3i) gem::matrix<int, 3, 3>;
%template(matrix3f) gem::matrix<float, 3, 3>;
