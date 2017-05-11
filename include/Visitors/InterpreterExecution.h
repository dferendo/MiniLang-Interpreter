//
// Created by dylan on 28/04/2017.
//

#ifndef COMPILERTHEORY_INTERPRETEREXECUTION_H
#define COMPILERTHEORY_INTERPRETEREXECUTION_H

#include <stack>
#include "Visitor.h"
#include "VisitorsUtility/Scope.h"
#include "VisitorsUtility/Evaluation.h"
#include "VisitorsUtility/ScopeForInterpreter.h"

namespace visitor {

    class InterpreterExecution : public Visitor {
    private:
        Evaluation * lastEvaluation = new Evaluation();

        /**
         * All the scopes of the program.
         */
        std::stack<ScopeForInterpreter *> allScopes;

        /**
         * Push the new scope in the allScopes stack. Called whenever there is a block.
         *
         * @param scope: The new scope.
         */
        void pushScope(ScopeForInterpreter *scope);

        /**
         * Pop a scope from the allScopes stack.
         *
         * @return: Returns the last added scope from allScopes.
         */
        ScopeForInterpreter * popScope();

        /**
         * Get the top scope from allScopes stack.
         *
         * @return: Returns the top scope from allScopes.
         */
        ScopeForInterpreter * getTopScope();

        Evaluation * returnEvaluationOfIdentifierInAllScopes(std::stack<ScopeForInterpreter *> scopes,
                                                             std::string &identifier);

        void handleOperator(Evaluation * LHS, Evaluation * RHS, std::string currentOperator);

        void handleType(std::string LHS, std::string RHS, std::string currentOperator);

        void handleType(int LHS, int RHS, std::string currentOperator);

        void handleType(double LHS, double RHS, std::string currentOperator);

        void handleType(bool LHS, bool RHS, std::string currentOperator);

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
    };

};
#endif //COMPILERTHEORY_INTERPRETEREXECUTION_H
