//
// Created by dylan on 20/03/2017.
//

#include "ASTStatementNode.h"

void parser::ast::ASTStatementNode::accept(parser::ast::Visitor *v) {
    ASTNode::accept(v);
}
