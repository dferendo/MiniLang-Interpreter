//
// Created by dylan on 25/04/2017.
//

#ifndef COMPILERTHEORY_SCOPE_H
#define COMPILERTHEORY_SCOPE_H

#include <map>
#include <vector>
#include "../../AST/ASTExpression/ASTIdentifier.h"
#include "../../Lexer/Token.h"
#include "SymbolTable.h"

namespace visitor {

    /**
     * Hold the identifiers that are found in a Scope.
     */
    class Scope {
    private:
        /**
         * Holds all identifiers which are unique. Includes functions.
         */
        std::map<std::string, SymbolTable *> scopeIdentifiers;
    public:
        /**
         * Checks if the identifier is unique.
         *
         * @param identifier The name given for a variable or function.
         * @return True if the identifier already exists, false otherwise.
         */
        bool identifierExists(std::string &identifier);

        /**
         * Add identifier with the {@link SymbolTable.h} consisting of a
         * return type only.
         *
         * @param identifier: The new variable to be added.
         */
        void addIdentifier(ast::ASTVariableDeclaration *identifier);

        /**
         * Add identifier with the {@link SymbolTable.h} consisting of
         * a return type and parameters of the function.
         *
         * @param function: The new function to be added.
         */
        void addIdentifier(ast::ASTFunctionDeclaration *function);

        /**
         * Add the params of a function with the given scope as an identifier.
         *
         * @param param: The param of the function.
         *
         * @warning: The param of the function should be added in the function scope.
         */
        void addIdentifier(ast::ASTFormalParam * param);

        /**
         * Return the type of the identifier.
         *
         * @param identifier: The identifier to be searched.
         * @return: The type of the of variable, TOK_Error if not found.
         */
        lexer::TOKEN returnTheTokenOfAnIdentifier(std::string &identifier);

        /**
         * Return the parameters of a function.
         *
         * @param identifier
         * @return: Vector containing the params, nullptr if not found.
         */
        std::vector<ast::ASTFormalParam *> * returnFormalsOfFunction(std::string &identifier);
    };

}
#endif //COMPILERTHEORY_SCOPE_H
