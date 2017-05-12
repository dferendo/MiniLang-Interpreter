//
// Created by dylan on 01/04/2017.
//

#ifndef COMPILERTHEORY_OPERATORNOTFOUND_H
#define COMPILERTHEORY_OPERATORNOTFOUND_H

#include <iostream>

namespace exceptions {

    class OperatorNotFound {
    public:
        std::string reason;

        OperatorNotFound(const std::string &reason);
    };

}


#endif //COMPILERTHEORY_OPERATORNOTFOUND_H
