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
                {S_01, S_ERR},
                {S_ERR, S_ERR},
                {S_ERR, S_ERR}
        };

        void tokenization(std::string &program);

        Token nextWord(std::string &program, int &charIndex);

        char nextChar(std::string &program, int &charIndex);

        void printTokens();

        void clear(std::stack<STATE> &filledStack);
    };
}


#endif //LAB2_LEXER_H
