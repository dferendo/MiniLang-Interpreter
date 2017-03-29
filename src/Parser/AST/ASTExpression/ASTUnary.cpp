//
// Created by dylan on 29/03/2017.
//

#include "ASTUnary.h"
#include "../Visitors/Visitor.h"

parser::ast::ASTUnary::ASTUnary(const std::string &unary, const parser::ast::ASTExprNode &unaryExpression) : unary(
        unary), unaryExpression(unaryExpression) {}

void parser::ast::ASTUnary::accept(Visitor *v) {
    v->visit(this);
}
