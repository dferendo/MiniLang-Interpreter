//
// Created by dylan on 29/03/2017.
//


#include "../../../include/Visitors/Visitor.h"
#include "../../../include/AST/ASTExpression/ASTIntegerLiteral.h"

void ast::ASTIntegerLiteral::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTIntegerLiteral::ASTIntegerLiteral(int literalValue) : literalValue(literalValue) {}

ast::ASTIntegerLiteral::~ASTIntegerLiteral() {}
