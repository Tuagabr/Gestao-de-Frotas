cmake_minimum_required(VERSION 3.30)
project(GestaoDeFrotas C)

set(CMAKE_C_STANDARD 99)

add_executable(GestaoDeFrotas main.c
        BasicGestaoFrotas.c
        BasicGestaoFrotas.h)
