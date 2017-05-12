//
// Created by dylan on 11/05/2017.
//

#ifndef COMPILERTHEORY_SEMANTICANALYSISERROR_H
#define COMPILERTHEORY_SEMANTICANALYSISERROR_H

#include <string>

namespace exceptions {

    class SemanticAnalysisError {
    public:
        std::string reason;

        SemanticAnalysisError(const std::string &reason) : reason(reason) {}
    };

}

#endif //COMPILERTHEORY_SEMANTICANALYSISERROR_H
