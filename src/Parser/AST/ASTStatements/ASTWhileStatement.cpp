//
// Created by dylan on 29/03/2017.
//

#include "ASTWhileStatement.h"
#include "../Visitors/Visitor.h"
#include "../ASTExpression/ASTExprNode.h"

void parser::ast::ASTWhileStatement::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTWhileStatement::ASTWhileStatement(parser::ast::ASTExprNode *exprNode, parser::ast::ASTBlock *astBlock)
        : exprNode(exprNode), astBlock(astBlock) {}
