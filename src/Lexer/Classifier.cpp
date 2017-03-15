//
// Created by dylan on 15/03/2017.
//

#include "Classifier.h"
#include <iostream>
using namespace std;

// TODO regex
int lexer::getClassifier(char &currentCharacter) {
    switch (currentCharacter) {
        case '{':
        case '}':
            return PUNCTUATION;
        case EOF:
            return END_OF_FILE;
        default:
            OTHER;
    }
    return 0;
}
