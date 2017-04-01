//
// Created by dylan on 29/03/2017.
//

#include "ASTBinaryExprNode.h"

parser::ast::ASTBinaryExprNode::ASTBinaryExprNode(const std::string &operation, parser::ast::ASTExprNode *LHS,
                                                  parser::ast::ASTExprNode *RHS) : operation(operation), LHS(LHS),
                                                                                   RHS(RHS) {}

void parser::ast::ASTBinaryExprNode::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

void parser::ast::ASTBinaryExprNode::setRHS(parser::ast::ASTExprNode *RHS) {
    ASTBinaryExprNode::RHS = RHS;
}
