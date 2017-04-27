//
// Created by dylan on 25/04/2017.
//

#ifndef COMPILERTHEORY_SCOPE_H
#define COMPILERTHEORY_SCOPE_H

#include <map>
#include <vector>
#include "../AST/ASTExpression/ASTIdentifier.h"
#include "../Lexer/Token.h"
#include "SymbolTable.h"

namespace visitor {

    class Scope {
    private:
        std::map<std::string, SymbolTable *> scopeIdentifiers;
    public:
        bool checkIfAnIdentifierExists(std::string &identifier);

        void addIdentifier(ast::ASTVariableDeclaration *identifier);

        void addIdentifier(ast::ASTFunctionDeclaration *function);

        lexer::TOKEN returnTheTokenOfAnIdentifier(std::string &identifier);

        std::vector<ast::ASTFormalParam *> * returnFormalsOfFunction(std::string &identifier);
    };

}
#endif //COMPILERTHEORY_SCOPE_H
