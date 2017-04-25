//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_VISITOR_H
#define COMPILERTHEORY_VISITOR_H

namespace parser {
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
        // Expressions
        class ASTBooleanLiteral;
        class ASTIntegerLiteral;
        class ASTRealLiteral;
        class ASTStringLiteral;
        class ASTIdentifier;
        class ASTSubExpression;
        class ASTFunctionCall;
        class ASTUnary;
        class ASTBinaryExprNode;

        class Visitor {
        public:
            virtual void visit(ASTNode * node) = 0;
            virtual void visit(ASTVariableDeclaration * node) = 0;
            virtual void visit(ASTAssignment * node) = 0;
            virtual void visit(ASTPrintStatement * node) = 0;
            virtual void visit(ASTBlock * node) = 0;
            virtual void visit(ASTIfStatement * node) = 0;
            virtual void visit(ASTWhileStatement * node) = 0;
            virtual void visit(ASTReturnStatement * node) = 0;
            virtual void visit(ASTFormalParam * node) = 0;
            virtual void visit(ASTFunctionDeclaration * node) = 0;
            virtual void visit(ASTBooleanLiteral * node) = 0;
            virtual void visit(ASTIntegerLiteral * node) = 0;
            virtual void visit(ASTRealLiteral * node) = 0;
            virtual void visit(ASTStringLiteral * node) = 0;
            virtual void visit(ASTIdentifier * node) = 0;
            virtual void visit(ASTSubExpression * node) = 0;
            virtual void visit(ASTFunctionCall * node) = 0;
            virtual void visit(ASTUnary * node) = 0;
            virtual void visit(ASTBinaryExprNode * node) = 0;
        };
    }
}
#endif //COMPILERTHEORY_VISITOR_H
