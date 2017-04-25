//
// Created by dylan on 25/04/2017.
//
#include "../../include/Visitors/Scope.h"
#include "../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include <algorithm>

bool visitor::Scope::checkIfAnIdentifierExists(std::string &identifier) {
    return scopeIdentifiers.find(identifier) != scopeIdentifiers.end();
}

bool visitor::Scope::addIdentifierWithCheck(ast::ASTVariableDeclaration *identifier) {
    if (scopeIdentifiers.find(identifier->identifier) == scopeIdentifiers.end()) {
        scopeIdentifiers.insert(std::pair<std::string, lexer::TOKEN>(identifier->identifier, identifier->tokenType));
        return true;
    } else {
        return false;
    }
}


