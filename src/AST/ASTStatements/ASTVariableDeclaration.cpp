//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTStatements/ASTVariableDeclaration.h"

ast::ASTVariableDeclaration::ASTVariableDeclaration(const std::string &identifier, lexer::TOKEN tokenType,
                                                            ast::ASTExprNode *expression) : identifier(
        identifier), tokenType(tokenType), expression(expression) {}

void ast::ASTVariableDeclaration::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTVariableDeclaration::~ASTVariableDeclaration() {
    delete expression;
}
