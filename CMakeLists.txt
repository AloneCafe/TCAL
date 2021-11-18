cmake_minimum_required(VERSION 3.20)
project(TCAL C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-O3)

add_executable(TCAL_test main.c prio_queue.h vec.h config.h vec.c utils.c utils.h)
