//
// Created by dylan on 25/04/2017.
//
#include "../../include/Visitors/Scope.h"
#include "../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include <algorithm>

bool visitor::Scope::checkIfAnIdentifierExists(std::string &identifier) {
    return scopeIdentifiers.find(identifier) != scopeIdentifiers.end();
}

void visitor::Scope::addIdentifier(ast::ASTVariableDeclaration *identifier) {
    scopeIdentifiers.insert(std::pair<std::string, lexer::TOKEN>(identifier->identifier, identifier->tokenType));
}

lexer::TOKEN visitor::Scope::returnTheTokenOfAnIdentifier(std::string &identifier) {
    std::map<std::string, lexer::TOKEN>::iterator it = scopeIdentifiers.find(identifier);

    if (it == scopeIdentifiers.end()) {
        return lexer::TOK_Error;
    }
    // Return TOKEN
    return it->second;
}


