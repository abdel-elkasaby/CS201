cmake_minimum_required(VERSION 3.16)
project(random LANGUAGES C)

add_compile_options(
    -Wall
)

add_executable(asm asm.c)
add_executable(fork fork.c)
add_executable(fork2 fork2.c)
add_executable(fork3 fork3.c)
add_executable(process process.c)
add_executable(zomb zomb.c)
add_executable(argv argv.c)
add_executable(signal signal.c)

set_property(TARGET asm fork fork2 fork3 process zomb argv signal PROPERTY RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})