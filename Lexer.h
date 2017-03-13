//
// Created by dylan on 27/02/2017.
//

#ifndef LAB2_LEXER_H
#define LAB2_LEXER_H

#include <iostream>

enum TOKENS {
    TOK_Number = -1, TOK_ArithmeticOP = -2, TOK_EOF = -3
};

class Lexer {

    struct Token {
        TOKENS tokenType;
        std::string tokenName;
    };
};


#endif //LAB2_LEXER_H
