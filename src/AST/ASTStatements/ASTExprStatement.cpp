//
// Created by dylan on 12/05/2017.
//
#include "../../../include/AST/ASTStatements/ASTExprStatement.h"


ast::ASTExprStatement::ASTExprStatement(ast::ASTExprNode *exprNode) : exprNode(exprNode) {}

ast::ASTExprStatement::~ASTExprStatement() {
    delete exprNode;
}

void ast::ASTExprStatement::accept(visitor::Visitor *v) {
    v->visit(this);
}


