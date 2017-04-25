//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTExpression/ASTStringLiteral.h"
#include "../../../../include/Parser/AST/Visitors/Visitor.h"

parser::ast::ASTStringLiteral::ASTStringLiteral(const std::string &literalString) : literalString(literalString) {}

void parser::ast::ASTStringLiteral::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTStringLiteral::~ASTStringLiteral() {}