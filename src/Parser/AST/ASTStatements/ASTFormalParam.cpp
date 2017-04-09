//
// Created by dylan on 31/03/2017.
//

#include "../../../../include/Parser/AST/ASTStatements/ASTFormalParam.h"

parser::ast::ASTFormalParam::ASTFormalParam(const std::string &identifier, lexer::TOKEN tokenType) : identifier(
        identifier), tokenType(tokenType) {}

void parser::ast::ASTFormalParam::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

parser::ast::ASTFormalParam::~ASTFormalParam() {}
