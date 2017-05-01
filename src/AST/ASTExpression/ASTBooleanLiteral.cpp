//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTExpression/ASTBooleanLiteral.h"

ast::ASTBooleanLiteral::ASTBooleanLiteral(bool literalValue) : literalValue(literalValue) {}

void ast::ASTBooleanLiteral::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTBooleanLiteral::~ASTBooleanLiteral() {}
