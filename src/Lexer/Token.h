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
        TOK_LeftParenthesis = 3,
        TOK_RightParenthesis = 4,
        TOK_Comma = 5,
        TOK_Colon = 6,
        TOK_SemiColon = 7,
        TOK_Period = 8,
        TOK_IntegerLiteral = 9,
        TOK_RealLiteral = 10,
        TOK_RealType = 11,
        TOK_IntType = 12,
        TOK_BoolType = 13,
        TOK_StringType = 14,
        TOK_BooleanLiteral = 15,
        TOK_Logic = 16,
        TOK_Set = 17,
        TOK_Var = 18,
        TOK_Print = 19,
        TOK_Return = 20,
        TOK_If = 21,
        TOK_Else = 22,
        TOK_While = 23,
        TOK_Def = 24,
        TOK_Identifier = 25,
        TOK_Printable = 26,
        TOK_MultiplicativeOperator = 27,
        TOK_Comment = 28,
        TOK_AdditiveOperator = 29,
        TOK_RelationalOperator = 30,
        TOK_Equals = 31,
        TOK_Error = 1000
    };

    const std::string TOKEN_STRING[] = {
            "TOK_EOF",
            "TOK_LeftCurlyBracket",
            "TOK_RightCurlyBracket",
            "TOK_LeftParenthesis",
            "TOK_RightParenthesis",
            "TOK_Comma",
            "TOK_Colon",
            "TOK_SemiColon",
            "TOK_Period",
            "TOK_IntegerLiteral",
            "TOK_RealLiteral",
            "TOK_RealType",
            "TOK_IntType",
            "TOK_BoolType",
            "TOK_StringType",
            "TOK_BooleanLiteral",
            "TOK_Logic",
            "TOK_Set",
            "TOK_Var",
            "TOK_Print",
            "TOK_Return",
            "TOK_If",
            "TOK_Else",
            "TOK_While",
            "TOK_Def",
            "TOK_Identifier",
            "TOK_Printable",
            "TOK_MultiplicativeOperator",
            "TOK_Comment",
            "TOK_AdditiveOperator",
            "TOK_RelationalOperator",
            "TOK_Equals",
            "TOK_Error"
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

    Token determinePunctuationToken(std::string &lexeme);

    Token determineDigit(std::string &lexeme);

    Token determineWords(std::string &lexeme);

    Token determinePrintable(std::string &lexeme);

}
#endif //COMPILERTHEORY_TOKEN_H
