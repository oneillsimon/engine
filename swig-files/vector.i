%module gem
%{
#include <gem/vector.h>
%};

%ignore gem::vector::vector();
%ignore gem::vector::vector(std::array<T, N> const &);
%ignore gem::vector::vector(std::initializer_list<T> const &);

%include "../src/gem/vector.h"

//%template(vector2i) gem::vector<int, 2>;
//%template(vector2f) gem::vector<float, 2>;
//%template(vector3i) gem::vector<int, 3>;
//%template(vector3f) gem::vector<float, 3>;
