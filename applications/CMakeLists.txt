cmake_minimum_required(VERSION 3.16)
project(applications)

#include_directories(../src)

add_library(
        applications

        cookbook/Chapter_1/CB_Chapter1_app.h
        cookbook/Chapter_1/CB_Chapter1_app.cpp
        cookbook/Chapter_1/CB_Chapter1_blob_app.h
        cookbook/Chapter_1/CB_Chapter1_blob_app.cpp
        cookbook/Chapter_2/ADSShadingApp.h
        cookbook/Chapter_2/ADSShadingApp.cpp
        cookbook/Chapter_2/DiffuseShadingApp.h
        cookbook/Chapter_2/DiffuseShadingApp.cpp
        cookbook/Chapter_2/DiscardShadingApp.h
        cookbook/Chapter_2/DiscardShadingApp.cpp
        cookbook/Chapter_2/FlatADSShadingApp.h
        cookbook/Chapter_2/FlatADSShadingApp.cpp
        cookbook/Chapter_2/SubroutineApp.h
        cookbook/Chapter_2/SubroutineApp.cpp
        cookbook/Chapter_2/TwoSideShadingApp.h
        cookbook/Chapter_2/TwoSideShadingApp.cpp
)

#target_link_libraries(applications engine)
target_link_libraries(applications extern)
target_link_libraries(applications engine)