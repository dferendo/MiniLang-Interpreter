//
// Created by dylan on 29/03/2017.
//

#include "ASTBlock.h"

void parser::ast::ASTBlock::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

void parser::ast::ASTBlock::addStatement(parser::ast::ASTStatementNode *statements) {
    this->statements.push_back(statements);
}
