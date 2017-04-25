//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTStatements/ASTWhileStatement.h"
#include "../../../../include/Parser/AST/Visitors/Visitor.h"
#include "../../../../include/Parser/AST/ASTExpression/ASTExprNode.h"

void parser::ast::ASTWhileStatement::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTWhileStatement::ASTWhileStatement(parser::ast::ASTExprNode *exprNode, parser::ast::ASTBlock *astBlock)
        : exprNode(exprNode), astBlock(astBlock) {}

parser::ast::ASTWhileStatement::~ASTWhileStatement() {
    delete exprNode;
    delete astBlock;
}
