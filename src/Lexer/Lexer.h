//
// Created by dylan on 27/02/2017.
//

#ifndef LAB2_LEXER_H
#define LAB2_LEXER_H

#include <iostream>
#include <stack>
#include <vector>
#include "State.h"
#include "Classifier.h"
#include "Token.h"

namespace lexer {

    class Lexer {
    public:
        Lexer(std::string program);

        std::vector<Token> allTokens;

    private:
        STATE miniLangTable[S_TOTAL][CLASSIFIER_TOTAL] = {
                {S_01,	S_02,	S_03,	S_05,	S_05,	S_06,	S_ERR,	S_14,	S_08,	S_15,	S_00,	S_15,	S_17,	S_19,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_03,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_04, S_ERR},
                {S_ERR,	S_ERR,	S_03,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_05,	S_05,	S_05,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_06,	S_ERR,	S_06,	S_06,	S_06,	S_07,	S_06,	S_06,	S_06,	S_06,	S_ERR,	S_06,	S_06,	S_06,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_11,	S_09,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_09,	S_ERR,	S_09,	S_09,	S_09,	S_09,	S_09,	S_09,	S_09,	S_09,	S_10,	S_09,	S_09,	S_09,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_11,	S_ERR,	S_11,	S_11,	S_11,	S_11,	S_11,	S_12,	S_11,	S_11,	S_11,	S_11,	S_11,	S_11,  S_ERR, S_ERR},
                {S_11,	S_ERR,	S_11,	S_11,	S_11,	S_11,	S_11,	S_12,	S_13,	S_11,	S_11,	S_11,	S_11,	S_11,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_18,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_18,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_18,  S_ERR, S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR, S_ERR}
        };

        void tokenization(std::string &program);

        Token nextWord(std::string &program, int &charIndex);

        char nextChar(std::string &program, int &charIndex, std::string &lexeme);

        void printTokens();

        void clear(std::stack<STATE> &filledStack);
    };
}


#endif //LAB2_LEXER_H
