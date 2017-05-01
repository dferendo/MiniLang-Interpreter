//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTExpression/ASTUnary.h"

ast::ASTUnary::ASTUnary(const std::string &unary, ast::ASTExprNode *unaryExpression) : unary(unary),
                                                                                                       unaryExpression(
                                                                                                               unaryExpression) {}

void ast::ASTUnary::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTUnary::~ASTUnary() {
    delete unaryExpression;
}
