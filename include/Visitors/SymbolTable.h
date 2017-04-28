//
// Created by dylan on 27/04/2017.
//

#ifndef COMPILERTHEORY_SYMBOLTABLE_H
#define COMPILERTHEORY_SYMBOLTABLE_H

#include "../Lexer/Token.h"
#include "../AST/ASTStatements/ASTFormalParam.h"

namespace visitor {

    /**
     * Holds the return type of identifiers. If the identifier is a function,
     * the parameters are also held.
     */
    class SymbolTable {
    public:
        lexer::TOKEN returnType;

        /**
         * If identifier is not a function, nullptr is held as a params.
         */
        std::vector<ast::ASTFormalParam *> * functionsParams= nullptr;

        /**
         * Constructor used for identifiers that are not a function.
         *
         * @param returnType: The token type of the identifier.
         */
        SymbolTable(lexer::TOKEN returnType);

        /**
         * Constructor used for identifiers that are a function.
         *
         * @param returnType: The return type of the function.
         * @param functionsParams: The parameters of the function.
         */
        SymbolTable(lexer::TOKEN returnType, std::vector<ast::ASTFormalParam *> functionsParams);
    };

}

#endif //COMPILERTHEORY_SYMBOLTABLE_H
