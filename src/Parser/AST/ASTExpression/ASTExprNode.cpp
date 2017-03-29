//
// Created by dylan on 20/03/2017.
//

#include "ASTExprNode.h"

void parser::ast::ASTExprNode::accept(parser::ast::Visitor *v) {
    ASTNode::accept(v);
}
