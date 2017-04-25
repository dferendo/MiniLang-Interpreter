//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTExpression/ASTRealLiteral.h"

ast::ASTRealLiteral::ASTRealLiteral(double realValue) : realValue(realValue) {}

void ast::ASTRealLiteral::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTRealLiteral::~ASTRealLiteral() {}
