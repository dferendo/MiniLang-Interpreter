//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTExpression/ASTSubExpression.h"
#include "../../../../include/Parser/AST/Visitors/Visitor.h"

parser::ast::ASTSubExpression::ASTSubExpression(parser::ast::ASTExprNode *subExpression) : subExpression(
        subExpression) {}

void parser::ast::ASTSubExpression::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTSubExpression::~ASTSubExpression() {
    delete subExpression;
}
