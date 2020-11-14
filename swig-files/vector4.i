%module gem
%{
#include <gem/vector4.h>
%};

%include "../src/gem/vector4.h"

%template(vector4i) gem::vector4<int>;
%template(vector4f) gem::vector4<float>;