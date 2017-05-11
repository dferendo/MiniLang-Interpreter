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

        std::map<std::string, ast::ASTFunctionDeclaration *> functionsBlock;
    public:
        void addIdentifier(std::string identifier, Evaluation * evaluation);

        void addFunctionBlock(std::string identifier,
                              ast::ASTFunctionDeclaration * functionDeclaration);

        Evaluation * returnIdentifierValue(std::string identifier);

        ast::ASTFunctionDeclaration * returnIdentifierFunctionBlock(std::string identifier);
    };

}
#endif //COMPILERTHEORY_SCOPEFORINTERPRETER_H
