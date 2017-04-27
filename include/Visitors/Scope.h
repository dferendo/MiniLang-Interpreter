//
// Created by dylan on 25/04/2017.
//

#ifndef COMPILERTHEORY_SCOPE_H
#define COMPILERTHEORY_SCOPE_H

#include <map>
#include <vector>
#include "../AST/ASTExpression/ASTIdentifier.h"
#include "../Lexer/Token.h"

namespace visitor {

    class Scope {
    private:
        std::map<std::string, lexer::TOKEN> scopeIdentifiers;

        std::map<std::string, std::vector<ast::ASTFormalParam *>> functionsParams;
    public:
        bool checkIfAnIdentifierExists(std::string &identifier);

        void addIdentifier(ast::ASTVariableDeclaration *identifier);

        lexer::TOKEN returnTheTokenOfAnIdentifier(std::string &identifier);
    };

}
#endif //COMPILERTHEORY_SCOPE_H
