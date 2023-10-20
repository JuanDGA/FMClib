cmake_minimum_required(VERSION 3.26)
project(FMClib C)

set(CMAKE_C_STANDARD 11)

add_executable(FMClib main.c
        FMClib/utils/utils.h
        FMClib/utils/utils.c
        FMClib/fmc.h
        FMClib/fmc.c)
