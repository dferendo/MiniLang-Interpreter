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
        TOK_EOF = 0,
        TOK_LeftCurlyBracket = 1,
        TOK_RightCurlyBracket = 2,

    };

    const std::string TOKEN_STRING[] = {
            "TOK_EOF", "TOK_LeftCurlyBracket", "TOK_RightCurlyBracket", "TOK_Number", "TOK_ArithmeticOP"
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

        std::string toString();
    };

    Token determineToken(std::string &lexeme, STATE &acceptState);
}


#endif //COMPILERTHEORY_TOKEN_H
