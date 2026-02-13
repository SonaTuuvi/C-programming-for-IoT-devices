cmake_minimum_required(VERSION 4.1)
project(IoT_laitteiden_C_ohjelmointi C)

set(CMAKE_C_STANDARD 23)

add_executable(IoT_laitteiden_C_ohjelmointi main.c
        Exercise_1/Exercise_1.h
        Exercise_1/Exercise_1.c
        Exercise_2/Exercise_2.h
        Exercise_2/Exercise_2.c
        Exercise_3/Exercise_3.c
        Exercise_3/Exercise_3.h
        Exercise_4/Exercise_4.c
        Exercise_4/Exercise_4.h
        Exercise_5/Exercise_5.c
        Exercise_5/Exercise_5.h
        Exercise_6/Exercise_6.c
        Exercise_6/Exercise_6.h
        Exercise_7/Exercise_7.c
        Exercise_7/Exercise_7.h
        Exercise_8/Exercise_8.c
        Exercise_8/Exercise_8.h
        Exercise_9/Exercise_9.c
        Exercise_9/Exercise_9.h
        menu.c
        menu.h
        Exercise_10/Exercise_10.c
        Exercise_10/Exercise_10.h
        Exercise_11/Exersice_11.c
        Exercise_12/Exercise_12.c
        Exercise_11/Exercise_11.h
        Exercise_12/Exercise_12.h
)
