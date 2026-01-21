cmake_minimum_required(VERSION 4.1)
project(IoT_laitteiden_C_ohjelmointi C)

set(CMAKE_C_STANDARD 23)

add_executable(IoT_laitteiden_C_ohjelmointi main.c
        "Exercise_1.h"
        "Exercise_1.c"
)
