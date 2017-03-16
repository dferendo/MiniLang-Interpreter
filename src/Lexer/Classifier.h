//
// Created by dylan on 15/03/2017.
//

#ifndef COMPILERTHEORY_CLASSIFIER_H
#define COMPILERTHEORY_CLASSIFIER_H

namespace lexer {

    /**
     * These will be the classifications. Columns in the 2-d array.
     * Punctuation: '{' | '}' | '(' |')'
     * END_OF_FILE: EOF
     * INTEGER_LITERAL: Integers from 0-9
     *
     */
    enum CLASSIFIER {
        PUNCTUATION = 0,
        END_OF_FILE = 1,
        NUMBER_LITERAL = 2,
        LETTER = 3,
        UNDERSCORE = 4,
        DOUBLE_QUOTATION_MARKS = 5,
        PRINTABLE = 6,
        MULTIPLIER = 7,
        DIVISION = 8,
        OPERATORS = 9,
        NEW_LINE = 10,
        RELATIONAL_OPERATORS = 11,
        EXCLAMATION_MARK = 12,
        EQUALS = 13,
        OTHER = 14,
        CLASSIFIER_TOTAL = OTHER + 1
    };

    int getClassifier(char &currentCharacter);
}

#endif //COMPILERTHEORY_CLASSIFIER_H
