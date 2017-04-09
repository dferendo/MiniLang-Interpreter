//
// Created by dylan on 29/03/2017.
//

#include "ASTIdentifier.h"
#include "../Visitors/Visitor.h"

parser::ast::ASTIdentifier::ASTIdentifier(const std::string &identifier) : identifier(identifier) {}

void parser::ast::ASTIdentifier::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTIdentifier::~ASTIdentifier() {}
