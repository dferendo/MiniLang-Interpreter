//
// Created by dylan on 29/03/2017.
//

#include "ASTSubExpression.h"
#include "../Visitors/Visitor.h"

parser::ast::ASTSubExpression::ASTSubExpression(const parser::ast::ASTExprNode &subExpression) : subExpression(
        subExpression) {}

void parser::ast::ASTSubExpression::accept(Visitor *v) {
    v->visit(this);
}
