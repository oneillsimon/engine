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

cmake_files() {
  git ls-files -z -- ':(glob)**/CMakeLists.txt' ':(glob)**/*.cmake' ':!**/build-*/**'
}

# C++ Tools
project_files | xargs clang-format --dry-run --Werror

cmake -S . -B build-tidy -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
project_files | xargs run-clang-tidy -p build-tidy -header-filter='^(src|tests|applications|swig)/'
rm -rf build-tidy

swig -lua -c++ -Werror -o /tmp/swig_wrap.cxx swig/swig.i

# CMake Tools
cmake_files | cmakefmt --in-place --files-from -
cmake_files | xargs -0 cmakelint --filter=-whitespace/indent

# Config and Assets
git ls-files '*.glsl' | xargs glslangValidator
git ls-files '*.lua' | xargs luacheck
git ls-files "*.sh" | xargs shellcheck
actionlint