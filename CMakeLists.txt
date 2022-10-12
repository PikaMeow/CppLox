cmake_minimum_required(VERSION 3.23)
project(CppLox)

set(CMAKE_CXX_STANDARD 17)


file(GLOB_RECURSE INTERPRETER_SRC
        src/ast/*.h
        src/common/*.h
        src/common/*.cpp
        src/interpreter/*.h
        src/interpreter/*.cpp
)

add_executable(
        CppLox src/main.cpp ${INTERPRETER_SRC}
        src/interpreter/Environment.h)

add_executable(
        AstGenerator src/tool/main.cpp
        src/tool/AstGenerator.h src/tool/AstGenerator.cpp
        src/common/Utils.h src/common/Utils.cpp
)
