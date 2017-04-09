//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTExpression/ASTUnary.h"
#include "../../../../include/Parser/AST/Visitors/Visitor.h"

parser::ast::ASTUnary::ASTUnary(const std::string &unary, parser::ast::ASTExprNode *unaryExpression) : unary(unary),
                                                                                                       unaryExpression(
                                                                                                               unaryExpression) {}

void parser::ast::ASTUnary::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTUnary::~ASTUnary() {
    delete unaryExpression;
}
