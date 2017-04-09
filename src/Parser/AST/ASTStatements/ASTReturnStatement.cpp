//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTStatements/ASTReturnStatement.h"

parser::ast::ASTReturnStatement::ASTReturnStatement(parser::ast::ASTExprNode *exprNode) : exprNode(exprNode) {}

void parser::ast::ASTReturnStatement::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

parser::ast::ASTReturnStatement::~ASTReturnStatement() {
    delete exprNode;
}
