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
        Exercise_13/Exercise_13.c
        Exercise_13/Exercise_13.h
        Exercise_14/Exercise_14.c
        Exercise_14/Exercise_14.h
        Exercise_15/Exercise_15.c
        Exercise_15/Exercise_15.h
        Exercise_16/Exercise_16.c
        Exercise_16/Exercise_16.h
        Exercise_17/Exercise_17.h
        Exercise_18/Exercise_18.c
        Exercise_18/Exercise_18.h
        Exercise_19/Exercise_19.h
        Exercise_19/Exercise_19.c
        Exercise_21/Exercise_21.c
        Exercise_21/Exercise_21.h
        Exercise_17/Exercise_17.c
        Exercise_19/menu_types.h
        Exercise_19/input_utils.h
        Exercise_19/input_utils.c
        Exercise_19/menu_io.h
        Exercise_19/menu_io.c
        Exercise_19/menu_sort.h
        Exercise_19/menu_sort.c
        Exercise_19/menu_print.h
        Exercise_19/menu_print.c
        Exercise_20/debug.c
        Exercise_20/debug.h
        Exercise_20/Exercise_20.c
        Exercise_20/Exercise_20.h
)