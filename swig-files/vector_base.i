%module gem
%{
#include <gem/vector_base.h>
%};

%include "stl.i"
%include "std_string.i"
%include "std_vector.i"

%include "../src/gem/vector_base.h"

%extend gem::vector_base {
        std::string __str__() {
            return $self->to_string();
        }

        T __getitem__(int i) const {
            return $self->get(i);
        }

        void __setitem__(int i, T t) {
            $self->set(i, t);
        }
};

%template(vector_base2i) gem::vector_base<int, 2>;
%template(vector_base2f) gem::vector_base<float, 2>;
%template(vector_base3i) gem::vector_base<int, 3>;
%template(vector_base3f) gem::vector_base<float, 3>;
%template(vector_base4i) gem::vector_base<int, 4>;
%template(vector_base4f) gem::vector_base<float, 4>;