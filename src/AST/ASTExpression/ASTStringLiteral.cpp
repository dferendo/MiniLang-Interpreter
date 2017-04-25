//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTExpression/ASTStringLiteral.h"

ast::ASTStringLiteral::ASTStringLiteral(const std::string &literalString) : literalString(literalString) {}

void ast::ASTStringLiteral::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTStringLiteral::~ASTStringLiteral() {}