//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_VISITOR_H
#define COMPILERTHEORY_VISITOR_H

namespace parser {
    namespace ast {
        class ASTNode;
        class ASTVariableDeclaration;
        class ASTAssignment;
        class ASTPrintStatement;
        class ASTBlock;
        class ASTIfStatement;
        class ASTWhileStatement;
        class ASTReturnStatement;

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
        };
    }
}
#endif //COMPILERTHEORY_VISITOR_H
