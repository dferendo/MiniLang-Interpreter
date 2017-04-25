//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTStatements/ASTReturnStatement.h"

ast::ASTReturnStatement::ASTReturnStatement(ast::ASTExprNode *exprNode) : exprNode(exprNode) {}

void ast::ASTReturnStatement::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTReturnStatement::~ASTReturnStatement() {
    delete exprNode;
}
