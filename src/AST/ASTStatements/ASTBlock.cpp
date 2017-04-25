//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTStatements/ASTStatementNode.h"
#include "../../../include/AST/ASTStatements/ASTBlock.h"

void ast::ASTBlock::accept(visitor::Visitor *v) {
    v->visit(this);
}

void ast::ASTBlock::addStatement(ast::ASTStatementNode *statements) {
    this->statements.push_back(statements);
}

ast::ASTBlock::~ASTBlock() {
    for (auto const &statement : statements) {
        delete statement;
    }
}
