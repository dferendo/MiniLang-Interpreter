//
// Created by dylan on 29/03/2017.
//

#include "ASTBooleanLiteral.h"

parser::ast::ASTBooleanLiteral::ASTBooleanLiteral(bool literalValue) : literalValue(literalValue) {}

void parser::ast::ASTBooleanLiteral::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

parser::ast::ASTBooleanLiteral::~ASTBooleanLiteral() {}
