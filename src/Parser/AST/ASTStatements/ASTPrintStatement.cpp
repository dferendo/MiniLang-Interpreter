//
// Created by dylan on 29/03/2017.
//

#include "ASTPrintStatement.h"

parser::ast::ASTPrintStatement::ASTPrintStatement(parser::ast::ASTExprNode *exprNode) : exprNode(exprNode) {}

void parser::ast::ASTPrintStatement::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

parser::ast::ASTPrintStatement::~ASTPrintStatement() {
    delete exprNode;
}
