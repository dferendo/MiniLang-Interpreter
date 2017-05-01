//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTExpression/ASTSubExpression.h"

ast::ASTSubExpression::ASTSubExpression(ast::ASTExprNode *subExpression) : subExpression(
        subExpression) {}

void ast::ASTSubExpression::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTSubExpression::~ASTSubExpression() {
    delete subExpression;
}
