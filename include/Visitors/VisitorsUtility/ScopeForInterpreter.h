//
// Created by dylan on 11/05/2017.
//

#ifndef COMPILERTHEORY_SCOPEFORINTERPRETER_H
#define COMPILERTHEORY_SCOPEFORINTERPRETER_H

#include <string>
#include <map>
#include "Evaluation.h"
#include "../../AST/ASTStatements/ASTVariableDeclaration.h"

namespace visitor {

    class ScopeForInterpreter {
    private:
        std::map<std::string, Evaluation *> scopeIdentifiers;
    public:
        void addIdentifier(std::string identifier, Evaluation * evaluation);

        Evaluation * returnIdentifierValue(std::string identifier);
    };

}
#endif //COMPILERTHEORY_SCOPEFORINTERPRETER_H
