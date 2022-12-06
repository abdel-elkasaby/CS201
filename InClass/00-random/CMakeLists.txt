cmake_minimum_required(VERSION 3.16)
project(random LANGUAGES C)

add_compile_options(
    -Wall
)

add_executable(asm asm.c)
add_executable(fork fork.c)
add_executable(process process.c)
add_executable(zomb zomb.c)

set_property(TARGET asm fork process zomb PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})