//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTExpression/ASTIdentifier.h"

ast::ASTIdentifier::ASTIdentifier(const std::string &identifier) : identifier(identifier) {}

void ast::ASTIdentifier::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTIdentifier::~ASTIdentifier() {}
