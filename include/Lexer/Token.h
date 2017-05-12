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
     * TOK_LeftCurlyBracket: '{'.
     * TOK_RightCurlyBracket: '}'.
     * TOK_LeftParenthesis: '('.
     * TOK_RightParenthesis: ')'.
     * TOK_Comma: ','.
     * TOK_Colon: ':'.
     * TOK_SemiColon: ';'.
     * TOK_IntegerLiteral: Holds integer values.
     * TOK_RealLiteral: Holds floating numbers.
     * TOK_RealType: Declare a real variable using real keyword.
     * TOK_IntType: Declare a int variable using int keyword.
     * TOK_BoolType: Declare a bool variable using bool keyword.
     * TOK_StringType: Declare a string variable using string keyword.
     * TOK_BooleanLiteral: Holds type for boolean variable (true/false).
     * TOK_Logic: Holds Gate Logic (and/or/not).
     * TOK_Set: Keyword set.
     * TOK_Var: Keyword var.
     * TOK_Print: Keyword print.
     * TOK_Return: Keyword return.
     * TOK_If: Keyword if.
     * TOK_Else: Keyword else.
     * TOK_While: Keyword while.
     * TOK_Def: Keyword def.
     * TOK_Identifier: Holds the name of a variable. Can be any character from A-Za-z or '_'.
     * TOK_Printable: Contains characters from [\x20 - \x7E]. The double quotation marks before
     * the characters will be removed.
     * TOK_MultiplicativeOperator: '*' | '/'.
     * TOK_Comment: Either single or multi comments. These Tokens should not be passed to the Parser.
     * TOK_AdditiveOperator: '+' | '-'.
     * TOK_RelationalOperator: '<' | '>' | '!=' | '<=' | '>='.
     * TOK_Equals: '='.
     * TOK_Error: This should not happen. If this happens, someone made a mistake in the transition table.
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
        TOK_IntegerLiteral = 8,
        TOK_RealLiteral = 9,
        TOK_RealType = 10,
        TOK_IntType = 11,
        TOK_BoolType = 12,
        TOK_StringType = 13,
        TOK_BooleanLiteral = 14,
        TOK_Logic = 15,
        TOK_Set = 16,
        TOK_Var = 17,
        TOK_Print = 18,
        TOK_Return = 19,
        TOK_If = 20,
        TOK_Else = 21,
        TOK_While = 22,
        TOK_Def = 23,
        TOK_Identifier = 24,
        TOK_Printable = 25,
        TOK_MultiplicativeOperator = 26,
        TOK_Comment = 27,
        TOK_AdditiveOperator = 28,
        TOK_RelationalOperator = 29,
        TOK_Equals = 30,
        TOK_Error = 31
    };

    /**
     * Used to get the token in string type.
     */
    const std::string TOKEN_STRING[] = {
            "TOK_EOF",
            "TOK_LeftCurlyBracket",
            "TOK_RightCurlyBracket",
            "TOK_LeftParenthesis",
            "TOK_RightParenthesis",
            "TOK_Comma",
            "TOK_Colon",
            "TOK_SemiColon",
            "TOK_IntegerLiteral",
            "TOK_RealLiteral",
            "real",
            "int",
            "bool",
            "string",
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

    /**
     * Tokens to be passed to the parser. TOKEN is necessary for every Token, tokenName and tokenValue are
     * optional.
     */
    class Token {
    public:
        /**
         * Holds the tokenType.
         */
        TOKEN tokenType;

        /**
         * Holds any other necessary information.
         */
        std::string tokenName = "";

        /**
         * Holds the value for number type Tokens.
         */
        double tokenValue = 0;

        Token(TOKEN tokenType);

        Token(TOKEN tokenType, double tokenValue);

        Token(TOKEN tokenType, const std::string &tokenName);

        Token(TOKEN tokenType, const std::string &tokenName, double tokenValue);

        /**
         * Data from Token into a string.
         * @return String with the data of the Token.
         */
        std::string toString();
    };

    /**
     * Determine the token type given a string and a STATE.
     * @param lexeme: The lexeme that stopped at a final STATE.
     * @param acceptState: The final STATE where the lexeme stopped.
     * @return Token.
     */
    Token determineToken(std::string &lexeme, STATE &acceptState);

    /**
     * Determine the punctuation. The size of the string should be 1. If it is not 1, there is an
     * error in the transition function.
     * @param lexeme: The lexeme that stopped at a final STATE.
     * @return Token.
     */
    Token determinePunctuationToken(std::string &lexeme);

    /**
     * Determines if a number is real or integer.
     * @param lexeme: The lexeme that stopped at a final STATE.
     * @return Integer Token if integer type, otherwise Real Token.
     */
    Token determineDigit(std::string &lexeme);

    /**
     * Determines if the given string is a keyword or a variable/function declaration.
     * @param lexeme: The lexeme that stopped at a final STATE.
     * @return If the lexeme is a keyword, the function returns its corresponding keyword Token. Otherwise
     * returns an Identifier Token.
     */
    Token determineWords(std::string &lexeme);

    /**
     * Removes the Double quotation marks from the given lexeme.
     * @param lexeme: The lexeme that stopped at a final STATE.
     * @return Printable Token.
     */
    Token determinePrintable(std::string &lexeme);

}
#endif //COMPILERTHEORY_TOKEN_H
