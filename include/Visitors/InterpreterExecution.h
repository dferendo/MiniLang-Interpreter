//
// Created by dylan on 28/04/2017.
//

#ifndef COMPILERTHEORY_INTERPRETEREXECUTION_H
#define COMPILERTHEORY_INTERPRETEREXECUTION_H

#include "Visitor.h"

namespace visitor {

    class InterpreterExecution : public Visitor {
    private:
        void visit(ast::ASTNode *node) override;

        void visit(ast::ASTVariableDeclaration *node) override;

        void visit(ast::ASTAssignment *node) override;

        void visit(ast::ASTPrintStatement *node) override;

        void visit(ast::ASTBlock *node) override;

        void visit(ast::ASTIfStatement *node) override;

        void visit(ast::ASTWhileStatement *node) override;

        void visit(ast::ASTReturnStatement *node) override;

        void visit(ast::ASTFormalParam *node) override;

        void visit(ast::ASTFunctionDeclaration *node) override;

        void visit(ast::ASTBooleanLiteral *node) override;

        void visit(ast::ASTIntegerLiteral *node) override;

        void visit(ast::ASTRealLiteral *node) override;

        void visit(ast::ASTStringLiteral *node) override;

        void visit(ast::ASTIdentifier *node) override;

        void visit(ast::ASTSubExpression *node) override;

        void visit(ast::ASTFunctionCall *node) override;

        void visit(ast::ASTUnary *node) override;

        void visit(ast::ASTBinaryExprNode *node) override;
    };

};
#endif //COMPILERTHEORY_INTERPRETEREXECUTION_H
