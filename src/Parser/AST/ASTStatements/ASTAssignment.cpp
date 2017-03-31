//
// Created by dylan on 29/03/2017.
//

#include "ASTAssignment.h"

parser::ast::ASTAssignment::ASTAssignment(const std::string &identifier, parser::ast::ASTExprNode *exprNode)
        : identifier(identifier), exprNode(exprNode) {}

void parser::ast::ASTAssignment::accept(parser::ast::Visitor *v) {
    v->visit(this);
}
