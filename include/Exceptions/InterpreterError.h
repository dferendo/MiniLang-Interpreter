//
// Created by dylan on 12/05/2017.
//

#ifndef COMPILERTHEORY_INTERPRETERERROR_H
#define COMPILERTHEORY_INTERPRETERERROR_H

#include <string>

namespace exceptions {

    class InterpreterError {
    public:
        std::string reason;

        InterpreterError(const std::string &reason) : reason(reason) {}
    };

}

#endif //COMPILERTHEORY_INTERPRETERERROR_H
