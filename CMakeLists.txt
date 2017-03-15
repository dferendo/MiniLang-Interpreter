cmake_minimum_required(VERSION 3.6)
project(CompilerTheory)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Lexer/Lexer.cpp src/Lexer/Lexer.h src/Lexer/State.cpp src/Lexer/State.h src/Lexer/Classifier.cpp src/Lexer/Classifier.h src/Lexer/Token.cpp src/Lexer/Token.h)
add_executable(CompilerTheory ${SOURCE_FILES})