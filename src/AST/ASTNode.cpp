//
// Created by dylan on 20/03/2017.
//
#include "../../include/AST/ASTStatements/ASTStatementNode.h"
#include "../../include/AST/ASTNode.h"

void ast::ASTNode::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTNode::~ASTNode() {
    for (auto const &statement : statements) {
        delete statement;
    }
}

ast::ASTNode::ASTNode() {}

void ast::ASTNode::addStatements(std::vector<ASTStatementNode *> statements) {
    this->statements.insert(this->statements.end(), statements.begin(), statements.end());
}

void ast::ASTNode::clearStatements() {
    statements.clear();
}

