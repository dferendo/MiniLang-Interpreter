//
// Created by dylan on 25/04/2017.
//

#ifndef COMPILERTHEORY_SEMANTICANALYSIS_H
#define COMPILERTHEORY_SEMANTICANALYSIS_H

#include <stack>
#include "Visitor.h"
#include "Scope.h"

namespace visitor {

    /**
     * Semantic pass for the program.
     */
    class SemanticAnalysis : public Visitor {
    private:
        /**
         * Checks if the given function is returned and add the params
         * of the function to its corresponding scope.
         */
        typedef struct ReturnCheckForFunctionDeclaration {
            bool isReturnFound;
            bool isFunctionDeclarationBlock;
            ast::ASTFunctionDeclaration * functionDeclaration;
        } ReturnCheckForFunctionDeclaration;

        /**
         * All the scopes of the program.
         */
        std::stack<Scope *> allScopes;

        /**
         * The last token type of an expression. Every time an expression
         * is checked, the token is updated.
         */
        lexer::TOKEN lastToken;

        /**
         * Functions can be declared inside other function, and thus the functions
         * are held in this vector.
         */
        std::vector<ReturnCheckForFunctionDeclaration *> functionsReturn;

        /**
         * Push the new scope in the allScopes stack. Called whenever there is a block.
         *
         * @param scope: The new scope.
         */
        void pushScope(Scope *scope);

        /**
         * Pop a scope from the allScopes stack.
         *
         * @return: Returns the last added scope from allScopes.
         */
        Scope * popScope();

        /**
         * Get the top scope from allScopes stack.
         *
         * @return: Returns the top scope from allScopes.
         */
        Scope * getTopScope();

        /**
         * Returns the type of an identifier from allScopes. The last edited is
         * returned first.
         *
         * @param scopes: All the scopes of the program.
         * @param identifier: The identifier to search.
         * @return: TOK_Error if identifier not found, the return type otherwise.
         */
        lexer::TOKEN returnTokenOfIdentifierInAllScopes(std::stack<Scope *> scopes,
                                                        std::string &identifier);

        /**
         * Returns the parameters of a function found in all scopes.
         *
         * @param scopes: All the scopes of the program.
         * @param identifier: The identifier to search.
         * @return: nullptr is identifier not found or it is not a function identifier,
         *          vector of params otherwise.
         */
        std::vector<ast::ASTFormalParam *> * returnFunctionParamsInAllScopes(std::stack<Scope *> scopes,
                                                                             std::string &identifier);

        /**
         * Checks if the tokens are correct for the given operator.
         *
         * @param lhs: The left token.
         * @param rhs: The right token
         * @param binaryOperator: The operator.
         * @return: -1 if operator is not supported for the given type.
         *          -2 if incompatible type.
         *           0 if the operators are correct, set lastToken to the correct type.
         */
        int handleOperatorType(lexer::TOKEN lhs, lexer::TOKEN rhs, std::string binaryOperator);

        virtual void visit(ast::ASTNode *node) override;

        virtual void visit(ast::ASTVariableDeclaration *node) override;

        virtual void visit(ast::ASTAssignment *node) override;

        virtual void visit(ast::ASTPrintStatement *node) override;

        virtual void visit(ast::ASTBlock *node) override;

        virtual void visit(ast::ASTIfStatement *node) override;

        virtual void visit(ast::ASTWhileStatement *node) override;

        virtual void visit(ast::ASTReturnStatement *node) override;

        virtual void visit(ast::ASTFormalParam *node) override;

        virtual void visit(ast::ASTFunctionDeclaration *node) override;

        virtual void visit(ast::ASTBooleanLiteral *node) override;

        virtual void visit(ast::ASTIntegerLiteral *node) override;

        virtual void visit(ast::ASTRealLiteral *node) override;

        virtual void visit(ast::ASTStringLiteral *node) override;

        virtual void visit(ast::ASTIdentifier *node) override;

        virtual void visit(ast::ASTSubExpression *node) override;

        virtual void visit(ast::ASTFunctionCall *node) override;

        virtual void visit(ast::ASTUnary *node) override;

        virtual void visit(ast::ASTBinaryExprNode *node) override;
    public:
        SemanticAnalysis();
    };

}
#endif //COMPILERTHEORY_SEMANTICANALYSIS_H
