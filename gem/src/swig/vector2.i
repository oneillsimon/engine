%module gem
%{
#include <gem/vector2.h>
%};

%include <gem/vector2.h>

%template(vector2i) gem::vector2<int>;
%template(vector2f) gem::vector2<float>;