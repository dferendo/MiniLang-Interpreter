//
// Created by dylan on 20/03/2017.
//
#include "../../include/AST/ASTStatements/ASTStatementNode.h"
#include "../../include/AST/ASTNode.h"

ast::ASTNode::ASTNode(const std::vector<ASTStatementNode *> &statements) : statements(statements) {}

void ast::ASTNode::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTNode::~ASTNode() {
    for (auto const &statement : statements) {
        delete statement;
    }
}
