//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTExpression/ASTRealLiteral.h"
#include "../../../../include/Parser/AST/Visitors/Visitor.h"

parser::ast::ASTRealLiteral::ASTRealLiteral(double realValue) : realValue(realValue) {}

void parser::ast::ASTRealLiteral::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTRealLiteral::~ASTRealLiteral() {}
