//
// Created by dylan on 29/03/2017.
//

#include "../../../include/Visitors/Visitor.h"
#include "../../../include/AST/ASTExpression/ASTExprNode.h"
#include "../../../include/AST/ASTExpression/ASTBinaryExprNode.h"

ast::ASTBinaryExprNode::ASTBinaryExprNode(const std::string &operation, ast::ASTExprNode *LHS,
                                                  ast::ASTExprNode *RHS) : operation(operation), LHS(LHS),
                                                                                   RHS(RHS) {}

void ast::ASTBinaryExprNode::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTBinaryExprNode::~ASTBinaryExprNode() {
    delete LHS;
    delete RHS;
}
