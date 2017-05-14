//
// Created by dylan on 25/04/2017.
//
#include "../../../include/Visitors/VisitorsUtility/Scope.h"
#include "../../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include "../../../include/AST/ASTStatements/ASTFunctionDeclaration.h"
#include <algorithm>

bool visitor::Scope::identifierExists(std::string &identifier) {
    return scopeIdentifiers.find(identifier) != scopeIdentifiers.end();
}

void visitor::Scope::addIdentifier(ast::ASTVariableDeclaration *identifier) {
    SymbolTable * temp = new SymbolTable(identifier->tokenType);

    scopeIdentifiers.insert(std::pair<std::string, SymbolTable *>(identifier->identifier, temp));
}

void visitor::Scope::addIdentifier(ast::ASTFunctionDeclaration *function) {
    SymbolTable * temp = new SymbolTable(function->tokenType, function->formalParams);

    scopeIdentifiers.insert(std::pair<std::string, SymbolTable *>(function->identifier, temp));
}

void visitor::Scope::addIdentifier(ast::ASTFormalParam *param) {
    SymbolTable * temp = new SymbolTable(param->tokenType);

    scopeIdentifiers.insert(std::pair<std::string, SymbolTable *>(param->identifier, temp));
}

void visitor::Scope::addIdentifier(std::string identifier) {
    scopeIdentifiers.insert(std::pair<std::string, SymbolTable *>(identifier, nullptr));
}

lexer::TOKEN visitor::Scope::returnTheTokenOfAnIdentifier(std::string &identifier) {
    std::map<std::string, SymbolTable* >::iterator it = scopeIdentifiers.find(identifier);

    if (it == scopeIdentifiers.end()) {
        return lexer::TOK_Error;
    }
    // Return TOKEN
    return it->second->returnType;
}

std::vector<ast::ASTFormalParam *> *visitor::Scope::returnFormalsOfFunction(std::string &identifier) {
    std::map<std::string, SymbolTable* >::iterator it = scopeIdentifiers.find(identifier);

    if (it == scopeIdentifiers.end()) {
        // Not found
        return nullptr;
    }
    // Return vector, nullptr if it does not exists
    return it->second->functionsParams;
}

visitor::Scope::~Scope() {
    // Free Symbol table
    for (auto &identifier : scopeIdentifiers) {
        delete identifier.second;
    }
}
