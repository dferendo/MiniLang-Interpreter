//
// Created by dylan on 29/03/2017.
//

#include "ASTVariableDeclaration.h"

parser::ast::ASTVariableDeclaration::ASTVariableDeclaration(const std::string &identifier, lexer::TOKEN tokenType,
                                                            const parser::ast::ASTExprNode &expression) : identifier(
        identifier), tokenType(tokenType), expression(expression) {}

void parser::ast::ASTVariableDeclaration::accept(parser::ast::Visitor *v) {
    v->visit(this);
}
