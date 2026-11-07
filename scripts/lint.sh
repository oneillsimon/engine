#!/usr/bin/env bash
set -euo pipefail

project_files() {
    git ls-files \
        'applications/*.cpp' 'applications/*.h' \
        'src/*.cpp' 'src/*.h' \
        'swig/*.cpp' 'swig/*.h' \
        'tests/*.cpp' 'tests/*.h' \
        'main.cpp'
}

# C++ Tools
project_files | xargs clang-format --dry-run --Werror

cmake -S . -B build-tidy -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
project_files | xargs run-clang-tidy -p build-tidy -header-filter='^(src|tests|applications|swig)/'

swig -lua -c++ -Werror -o /tmp/swig_wrap.cxx swig/swig.i

# CMake Tools
cmakefmt --check --path-regex "^(?!(build-ci|build-tidy)/).*" .
cmakelint

# Config and Assets
git ls-files '*.glsl' | xargs glslangValidator
git ls-files '*.lua' | xargs luacheck
actionlint