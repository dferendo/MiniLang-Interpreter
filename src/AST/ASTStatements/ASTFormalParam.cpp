//
// Created by dylan on 31/03/2017.
//


#include "../../../include/AST/ASTStatements/ASTFormalParam.h"

ast::ASTFormalParam::ASTFormalParam(const std::string &identifier, lexer::TOKEN tokenType) : identifier(
        identifier), tokenType(tokenType) {}

void ast::ASTFormalParam::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTFormalParam::~ASTFormalParam() {}
