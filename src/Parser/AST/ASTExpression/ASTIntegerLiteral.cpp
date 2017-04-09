//
// Created by dylan on 29/03/2017.
//

#include "ASTIntegerLiteral.h"

void parser::ast::ASTIntegerLiteral::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

parser::ast::ASTIntegerLiteral::ASTIntegerLiteral(int literalValue) : literalValue(literalValue) {}

parser::ast::ASTIntegerLiteral::~ASTIntegerLiteral() {}
