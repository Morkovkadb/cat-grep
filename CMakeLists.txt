cmake_minimum_required(VERSION 3.27)
project(Cat_s21 C)

set(CMAKE_C_STANDARD 11)

add_executable(Cat_s21 main.c
        cat_struct.h
        test.c)
