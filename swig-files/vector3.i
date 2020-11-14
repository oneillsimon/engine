%module gem
%{
#include <gem/vector3.h>
%};

%include "../src/gem/vector3.h"

%template(vector3i) gem::vector3<int>;
%template(vector3f) gem::vector3<float>;