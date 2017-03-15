//
// Created by dylan on 15/03/2017.
//

#ifndef COMPILERTHEORY_CLASSIFIER_H
#define COMPILERTHEORY_CLASSIFIER_H

namespace lexer {

    enum CLASSIFIER {
        PUNCTUATION = 0,
        END_OF_FILE = 1,
        OTHER = 2,
        CLASSIFIER_TOTAL = OTHER
    };

    int getClassifier(char &currentCharacter);
}

#endif //COMPILERTHEORY_CLASSIFIER_H
