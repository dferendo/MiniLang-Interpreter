//
// Created by dylan on 15/03/2017.
//

#include "../../include/Lexer/Classifier.h"
#include <iostream>
using namespace std;

int lexer::getClassifier(char &currentCharacter) {
    switch (currentCharacter) {
        case '{':
        case '}':
        case '(':
        case ')':
        case ',':
        case ':':
        case ';':
            return PUNCTUATION;
        case EOF:
        case '\0':
            return END_OF_FILE;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return NUMBER_LITERAL;
        case '_':
            return UNDERSCORE;
        case '"':
            return DOUBLE_QUOTATION_MARKS;
        case '*':
            return MULTIPLIER;
        case '/':
            return DIVISION;
        case '+':
        case '-':
            return OPERATORS;
        case '\n':
            return NEW_LINE;
        case '<':
        case '>':
            return RELATIONAL_OPERATORS;
        case '!':
            return EXCLAMATION_MARK;
        case '=':
            return EQUALS;
        case '.':
            return FULL_STOP;
        default:
            if (isalpha(currentCharacter)) {
                return LETTER;
            } else if (currentCharacter >= 32 && currentCharacter <= 126) {
                return PRINTABLE;
            } else {
                return OTHER;
            }
    }
}
