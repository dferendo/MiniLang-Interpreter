//
// Created by dylan on 29/03/2017.
//

#include "ASTRealLiteral.h"
#include "../Visitors/Visitor.h"

parser::ast::ASTRealLiteral::ASTRealLiteral(double realValue) : realValue(realValue) {}

void parser::ast::ASTRealLiteral::accept(Visitor *v) {
    v->visit(this);
}
