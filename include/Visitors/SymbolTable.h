//
// Created by dylan on 27/04/2017.
//

#ifndef COMPILERTHEORY_SYMBOLTABLE_H
#define COMPILERTHEORY_SYMBOLTABLE_H

#include "../Lexer/Token.h"
#include "../AST/ASTStatements/ASTFormalParam.h"

namespace visitor {

    class SymbolTable {
    public:
        lexer::TOKEN returnType;

        std::vector<ast::ASTFormalParam *> * functionsParams= nullptr;

        SymbolTable(lexer::TOKEN returnType);

        SymbolTable(lexer::TOKEN returnType, std::vector<ast::ASTFormalParam *> functionsParams);
    };

}

#endif //COMPILERTHEORY_SYMBOLTABLE_H
