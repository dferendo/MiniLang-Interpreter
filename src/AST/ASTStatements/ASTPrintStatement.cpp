//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTStatements/ASTPrintStatement.h"

ast::ASTPrintStatement::ASTPrintStatement(ast::ASTExprNode *exprNode) : exprNode(exprNode) {}

void ast::ASTPrintStatement::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTPrintStatement::~ASTPrintStatement() {
    delete exprNode;
}
