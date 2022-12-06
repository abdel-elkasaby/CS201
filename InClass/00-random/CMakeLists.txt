cmake_minimum_required(VERSION 3.16)
project(random LANGUAGES C)

add_compile_options(
    -Wall
)

add_executable(asm asm.c)
add_executable(fork fork.c)
add_executable(process process.c)