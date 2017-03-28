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

        /**
         * This vector holds all the Tokens for a given program. These Tokens need to be passed to the
         * Parser.
         */
        std::vector<Token> allTokens;

        /**
         * Used as a counter to the next Token for the parser.
         */
        std::vector<Token>::size_type currentIndex = 0;

        /**
         * Returns the next Token.
         * @return Returns the next Token. If called after all the Tokens have been passed, will return
         * Token containing TOK_Error.
         */
        Token getNextToken();

        /**
         * Previews the next Token without incrementing to the next Token.
         * @return Returns the next Token without incrementing to the next Token. If called after all the
         * Tokens have been passed, will return Token containing TOK_Error.
         */
        Token previewNextToken();
    private:
        /**
         * Transition function. Excel formed found in documentation/Transition.ods.
         */
        STATE miniLangTransitions[S_TOTAL][CLASSIFIER_TOTAL] = {
                {S_01,	S_02,	S_03,	S_05,	S_05,	S_06,	S_ERR,	S_14,	S_08,	S_15,	S_00,	S_15,	S_17,	S_19,  S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_03,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_04,    S_ERR},
                {S_ERR,	S_ERR,	S_03,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_05,	S_05,	S_05,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_06,	S_ERR,	S_06,	S_06,	S_06,	S_07,	S_06,	S_06,	S_06,	S_06,	S_ERR,	S_06,	S_06,	S_06,  S_06,    S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_11,	S_09,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_09,	S_ERR,	S_09,	S_09,	S_09,	S_09,	S_09,	S_09,	S_09,	S_09,	S_10,	S_09,	S_09,	S_09,  S_09,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_11,	S_ERR,	S_11,	S_11,	S_11,	S_11,	S_11,	S_12,	S_11,	S_11,	S_11,	S_11,	S_11,	S_11,  S_11,   S_ERR},
                {S_11,	S_ERR,	S_11,	S_11,	S_11,	S_11,	S_11,	S_12,	S_13,	S_11,	S_11,	S_11,	S_11,	S_11,  S_11,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_18,  S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_18,  S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_18,  S_ERR,   S_ERR},
                {S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR,	S_ERR, S_ERR,   S_ERR}
        };

        /**
         * Begins the Lexical Analysis. Turn the given program into a vector of Tokens.
         * @param program: The program that needs to be scanned.
         */
        void tokenization(std::string &program);

        /**
         * Determine the next Tokens.
         * @param program: The program that needs to be scanned.
         * @param charIndex: The current location of the character being processed.
         * @return Returns a Token if the syntax of the program is current, stops the program otherwise.
         */
        Token nextWord(std::string &program, int &charIndex);

        /**
         * Determines the next character to be processed. Spaces and new lines will be ignored at the
         * beginning of a new Token.
         * @param program: The program that needs to be scanned.
         * @param charIndex: The current location of the character being processed.
         * @param lexeme: The current string that will be turned into a Token. If the length of
         * the lexeme is 0, it indicated that a new Token is being processed.
         * @return EOF if end of file, otherwise the next character indicated by charIndex.
         */
        char nextChar(std::string &program, int &charIndex, std::string &lexeme);

        /**
         * Prints Tokens.
         */
        void printTokens();

        /**
         * Determine the location where the Lexer failed.
         * @param program: The program that needs to be scanned.
         * @param currentCharCount: The char index where the Lexer failed.
         * @return The line where the Lexer failed starting from line 1.
         */
        int determineErrorLine(std::string &program, int &currentCharCount);

        /**
         * Empty a Stack.
         * @param filledStack: The stack that needs to be emptied.
         */
        void clear(std::stack<STATE> &filledStack);
    };
}

#endif //LAB2_LEXER_H
