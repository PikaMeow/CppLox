cmake_minimum_required(VERSION 3.23)
project(CppLox)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE ALL_SRC
        src/ast/*.h
        src/common/*.h
        src/common/*.cpp
        src/interpreter/*.h
        src/interpreter/*.cpp
)

add_executable(
        CppLox src/main.cpp ${ALL_SRC}
)
