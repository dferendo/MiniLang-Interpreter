//
// Created by dylan on 25/04/2017.
//

#ifndef COMPILERTHEORY_SCOPE_H
#define COMPILERTHEORY_SCOPE_H

#include <map>
#include "../AST/ASTExpression/ASTIdentifier.h"
#include "../Lexer/Token.h"

namespace visitor {

    class Scope {
    private:
        std::map<std::string, lexer::TOKEN > scopeIdentifiers;
    public:
        bool checkIfAnIdentifierExists(std::string &identifier);

        bool addIdentifierWithCheck(ast::ASTVariableDeclaration * identifier);
    };

}
#endif //COMPILERTHEORY_SCOPE_H
