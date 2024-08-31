cmake_minimum_required(VERSION 3.28)
project(FOK_GYEM_Tetris_native)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(NONARDUINO)

add_executable(FOK_GYEM_Tetris_native
        main.cpp
        tetrimino.h
        config.h
        display.cpp
        display.h
        econio.c
        econio.h
        field.cpp
        field.h
        tetrimino.cpp
        common.cpp
        common.h)
