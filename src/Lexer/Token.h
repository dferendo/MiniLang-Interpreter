//
// Created by dylan on 15/03/2017.
//

#ifndef COMPILERTHEORY_TOKEN_H
#define COMPILERTHEORY_TOKEN_H

#include <iostream>
#include "State.h"

namespace lexer {

    /**
     * All tokens that will be in the Lexer.
     * TOK_EOF: Marks the end of the file.
     * TOK_LeftCurlyBracket: Contains '{'.
     * TOK_RightCurlyBracket: Contains '}'.
     *
     */
    enum TOKEN {
        TOK_EOF = -1, TOK_LeftCurlyBracket = -2, TOK_RightCurlyBracket = -3, TOK_Number = -4, TOK_ArithmeticOP = -5
    };

    class Token {
    public:
        TOKEN tokenType;

        std::string tokenName = "";

        double tokenValue = 0;

        Token(TOKEN tokenType);

        Token(TOKEN tokenType, double tokenValue);

        Token(TOKEN tokenType, const std::string &tokenName);

        Token(TOKEN tokenType, const std::string &tokenName, double tokenValue);
    };

    Token determineToken(std::string &lexeme, STATE &acceptState);
}


#endif //COMPILERTHEORY_TOKEN_H
