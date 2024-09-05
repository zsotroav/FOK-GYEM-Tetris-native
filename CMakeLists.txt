cmake_minimum_required(VERSION 3.28)
project(FOK_GYEM_Tetris_native)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(NONARDUINO)

add_executable(FOK_GYEM_Tetris_native
        include/common.h
        include/io.h
        include/field.h
        include/config.h
        include/tetrimino.h

        src/tetrimino.cpp
        src/main.cpp
        src/common.cpp
        src/io.cpp
        src/field.cpp

        lib/econio/econio.h
        lib/econio/econio.c
)
