//
// Created by dylan on 29/03/2017.
//

#include "ASTAssignment.h"

void parser::ast::ASTAssignment::accept(parser::ast::Visitor *v) {
    v->visit(this);
}
