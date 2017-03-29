//
// Created by dylan on 29/03/2017.
//

#include "ASTStringLiteral.h"
#include "../Visitors/Visitor.h"

void parser::ast::ASTStringLiteral::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTStringLiteral::ASTStringLiteral(const std::string &literalString) : literalString(literalString) {}
