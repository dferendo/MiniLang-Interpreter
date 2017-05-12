//
// Created by dylan on 11/05/2017.
//

#ifndef COMPILERTHEORY_LEXERFAILED_H
#define COMPILERTHEORY_LEXERFAILED_H

#include <string>

namespace exceptions {

    class LexerFailed {
    public:
        std::string reason;

        LexerFailed(const std::string &reason) : reason(reason) {}
    };

}

#endif //COMPILERTHEORY_LEXERFAILED_H
