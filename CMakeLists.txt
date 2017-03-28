cmake_minimum_required(VERSION 3.6)
project(CompilerTheory)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Lexer/Lexer.cpp src/Lexer/Lexer.h src/Lexer/State.cpp src/Lexer/State.h src/Lexer/Classifier.cpp src/Lexer/Classifier.h src/Lexer/Token.cpp src/Lexer/Token.h src/Parser/Parser.cpp src/Parser/Parser.h src/Parser/ASTNode.cpp src/Parser/ASTNode.h src/Parser/ASTExprNode.cpp src/Parser/ASTExprNode.h src/Parser/ASTStatementNode.cpp src/Parser/ASTStatementNode.h src/Exceptions/UnexpectedTokenWhileParsing.cpp src/Exceptions/UnexpectedTokenWhileParsing.h)
add_executable(CompilerTheory ${SOURCE_FILES})