cmake_minimum_required(VERSION 3.6)
project(CompilerTheory)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Lexer.cpp Lexer.h)
add_executable(CompilerTheory ${SOURCE_FILES})