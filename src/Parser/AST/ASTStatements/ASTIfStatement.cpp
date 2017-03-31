//
// Created by dylan on 29/03/2017.
//

#include "ASTIfStatement.h"

parser::ast::ASTIfStatement::ASTIfStatement(parser::ast::ASTExprNode *exprNode, parser::ast::ASTBlock *astBlockForIF)
        : exprNode(exprNode), astBlockForIF(astBlockForIF) {}

parser::ast::ASTIfStatement::ASTIfStatement(parser::ast::ASTExprNode *exprNode, parser::ast::ASTBlock *astBlockForIF,
                                            parser::ast::ASTBlock *astBlockForElse) : exprNode(exprNode),
                                                                                      astBlockForIF(astBlockForIF),
                                                                                      astBlockForElse(
                                                                                              astBlockForElse) {}

void parser::ast::ASTIfStatement::accept(parser::ast::Visitor *v) {
    v->visit(this);
}
