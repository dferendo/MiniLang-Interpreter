//
// Created by dylan on 29/03/2017.
//


#include "../../../include/Visitors/Visitor.h"
#include "../../../include/AST/ASTStatements/ASTWhileStatement.h"

void ast::ASTWhileStatement::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTWhileStatement::ASTWhileStatement(ast::ASTExprNode *exprNode, ast::ASTBlock *astBlock)
        : exprNode(exprNode), astBlock(astBlock) {}

ast::ASTWhileStatement::~ASTWhileStatement() {
    delete exprNode;
    delete astBlock;
}
