cmake_minimum_required(VERSION 3.28)
project(FOK_GYEM_Tetris_native)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(NONARDUINO)

include_directories(include)
include_directories(lib/econio)

add_executable(FOK_GYEM_Tetris_native
        src/main.cpp

        include/config.h
        include/common.h
        include/field.h
        include/io.h
        include/tetrimino.h

        src/common.pc.cpp
        src/field.cpp
        src/io.pc.cpp
        src/tetrimino.cpp

        lib/econio/econio.h
        lib/econio/econio.c
)
