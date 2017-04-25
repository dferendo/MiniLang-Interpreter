//
// Created by dylan on 27/03/2017.
//

#ifndef COMPILERTHEORY_UNEXPECTEDTOKENWHILEPARSING_H
#define COMPILERTHEORY_UNEXPECTEDTOKENWHILEPARSING_H

#include <iostream>

namespace exceptions {
    class UnexpectedTokenWhileParsing {
    public:
        std::string reasonForError;
        UnexpectedTokenWhileParsing(const std::string &reasonForError);
    };
}


#endif //COMPILERTHEORY_UNEXPECTEDTOKENWHILEPARSING_H
