cmake_minimum_required(VERSION 3.16)

find_package(Lua 5.3.5 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

add_library(
        engine
        scripting/lua.h
        scripting/lua.cpp
)

target_link_libraries(engine PUBLIC ${LUA_LIBRARIES})