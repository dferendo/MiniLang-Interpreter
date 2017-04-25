//
// Created by dylan on 15/03/2017.
//

#ifndef COMPILERTHEORY_CLASSIFIER_H
#define COMPILERTHEORY_CLASSIFIER_H

namespace lexer {

    /**
     * Classification for MiniLang.
     * Punctuation: '{' | '}' | '(' |')' | ',' | ':' | ';'.
     * END_OF_FILE: EOF.
     * NUMBER_LITERAL: Integers from 0-9.
     * LETTER: A-Za-z.
     * UNDERSCORE: '_'.
     * DOUBLE_QUOTATION_MARKS: '"'.
     * PRINTABLE: [\x20 - \x7E]. Since this is a range that contains other classifications,
     * the specific type of the classification will be returned, not printable.
     * MULTIPLIER: '*'.
     * DIVISION: '/'.
     * OPERATORS: '+' | '-'.
     * NEW_LINE: '\n'. Classification for new line is needed because of comments.
     * RELATIONAL_OPERATORS: '<' | '>'.
     * EXCLAMATION_MARK: '!'.
     * EQUALS: '='.
     * FULL_STOP: '.'.
     * OTHER: Any remaining character.
     * CLASSIFIER_TOTAL: Holds the amount of classifications used to determine the size of the transition
     * table found in {@link lexer::Lexer}.
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
        FULL_STOP = 14,
        OTHER = 15,
        CLASSIFIER_TOTAL = OTHER + 1
    };

    /**
     * Returns the classifier according to the given character.
     * @param currentCharacter: The character that needs to be classified.
     * @return Number indication the column location of the given character in the transition table.
     */
    int getClassifier(char &currentCharacter);
}

#endif //COMPILERTHEORY_CLASSIFIER_H
