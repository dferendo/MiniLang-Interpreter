//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_VISITOR_H
#define COMPILERTHEORY_VISITOR_H

namespace ast {
    class ASTNode;
    // Statements
    class ASTVariableDeclaration;
    class ASTAssignment;
    class ASTPrintStatement;
    class ASTBlock;
    class ASTIfStatement;
    class ASTWhileStatement;
    class ASTReturnStatement;
    class ASTFormalParam;
    class ASTFunctionDeclaration;
    class ASTExprStatement;
    // Expressions
    class ASTExprNode;
    class ASTBooleanLiteral;
    class ASTIntegerLiteral;
    class ASTRealLiteral;
    class ASTStringLiteral;
    class ASTIdentifier;
    class ASTSubExpression;
    class ASTFunctionCall;
    class ASTUnary;
    class ASTBinaryExprNode;
}

namespace visitor {

    class Visitor {
    public:
        virtual void visit(ast::ASTNode * node) = 0;
        virtual void visit(ast::ASTVariableDeclaration * node) = 0;
        virtual void visit(ast::ASTAssignment * node) = 0;
        virtual void visit(ast::ASTPrintStatement * node) = 0;
        virtual void visit(ast::ASTBlock * node) = 0;
        virtual void visit(ast::ASTIfStatement * node) = 0;
        virtual void visit(ast::ASTWhileStatement * node) = 0;
        virtual void visit(ast::ASTReturnStatement * node) = 0;
        virtual void visit(ast::ASTExprStatement * node) = 0;
        virtual void visit(ast::ASTFormalParam * node) = 0;
        virtual void visit(ast::ASTFunctionDeclaration * node) = 0;
        virtual void visit(ast::ASTBooleanLiteral * node) = 0;
        virtual void visit(ast::ASTIntegerLiteral * node) = 0;
        virtual void visit(ast::ASTRealLiteral * node) = 0;
        virtual void visit(ast::ASTStringLiteral * node) = 0;
        virtual void visit(ast::ASTIdentifier * node) = 0;
        virtual void visit(ast::ASTSubExpression * node) = 0;
        virtual void visit(ast::ASTFunctionCall * node) = 0;
        virtual void visit(ast::ASTUnary * node) = 0;
        virtual void visit(ast::ASTBinaryExprNode * node) = 0;
    };

}
#endif //COMPILERTHEORY_VISITOR_H
