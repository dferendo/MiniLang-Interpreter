//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTStatements/ASTAssignment.h"

ast::ASTAssignment::ASTAssignment(const std::string &identifier, ast::ASTExprNode *exprNode)
        : identifier(identifier), exprNode(exprNode) {}

void ast::ASTAssignment::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTAssignment::~ASTAssignment() {
    delete exprNode;
}
