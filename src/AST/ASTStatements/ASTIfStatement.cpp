//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTStatements/ASTBlock.h"
#include "../../../include/AST/ASTExpression/ASTExprNode.h"
#include "../../../include/AST/ASTStatements/ASTIfStatement.h"

ast::ASTIfStatement::ASTIfStatement(ast::ASTExprNode *exprNode, ast::ASTBlock *astBlockForIF)
        : exprNode(exprNode), astBlockForIF(astBlockForIF) {}

ast::ASTIfStatement::ASTIfStatement(ast::ASTExprNode *exprNode, ast::ASTBlock *astBlockForIF,
                                            ast::ASTBlock *astBlockForElse) : exprNode(exprNode),
                                                                                      astBlockForIF(astBlockForIF),
                                                                                      astBlockForElse(
                                                                                              astBlockForElse) {}

void ast::ASTIfStatement::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTIfStatement::~ASTIfStatement() {
    delete exprNode;
    delete astBlockForIF;
    if (astBlockForElse != nullptr) {
        delete astBlockForElse;
    }
}
