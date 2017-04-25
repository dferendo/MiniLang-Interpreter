//
// Created by dylan on 25/04/2017.
//
#include "../../include/Visitors/SemanticAnalysis.h"
#include "../../include/AST/ASTNode.h"
#include "../../include/AST/ASTStatements/ASTStatementNode.h"
#include "../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include "../../include/AST/ASTStatements/ASTBlock.h"
#include "../../include/AST/ASTStatements/ASTAssignment.h"

using namespace ast;

namespace visitor {

    void SemanticAnalysis::pushScope(Scope *scope) {
        allScopes.push(scope);
    }

    void SemanticAnalysis::visit(ASTNode *node) {
        // Add Global scope
        Scope * globalScope = new Scope();
        pushScope(globalScope);

        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
        popScope();
    }

    void SemanticAnalysis::visit(ASTVariableDeclaration *node) {
        // Get the scope the node is currently in
        Scope * currentScope = getTopScope();
        // Add identifier, if it already exists exits.
        if (!currentScope->addIdentifierWithCheck(node)) {
            std::cout << "Duplicate declaration of local variable '" << node->identifier << "'" << std::endl;
            exit(1);
        }
    }

    void SemanticAnalysis::visit(ASTAssignment *node) {
        if (!checkIfIdentifierExists(allScopes, node->identifier)) {
            std::cout << "Can't resolve variable '" << node->identifier << "'" << std::endl;
        }
    }

    void SemanticAnalysis::visit(ASTPrintStatement *node) {

    }

    void SemanticAnalysis::visit(ASTBlock *node) {
        Scope * blockScope = new Scope();
        // Push new Scope
        allScopes.push(blockScope);
        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
        // Pop scope
        allScopes.pop();
    }

    void SemanticAnalysis::visit(ASTIfStatement *node) {

    }

    void SemanticAnalysis::visit(ASTWhileStatement *node) {

    }

    void SemanticAnalysis::visit(ASTReturnStatement *node) {

    }

    void SemanticAnalysis::visit(ASTFormalParam *node) {

    }

    void SemanticAnalysis::visit(ASTFunctionDeclaration *node) {

    }

    void SemanticAnalysis::visit(ASTBooleanLiteral *node) {

    }

    void SemanticAnalysis::visit(ASTIntegerLiteral *node) {

    }

    void SemanticAnalysis::visit(ASTRealLiteral *node) {

    }

    void SemanticAnalysis::visit(ASTStringLiteral *node) {

    }

    void SemanticAnalysis::visit(ASTIdentifier *node) {

    }

    void SemanticAnalysis::visit(ASTSubExpression *node) {

    }

    void SemanticAnalysis::visit(ASTFunctionCall *node) {

    }

    void SemanticAnalysis::visit(ASTUnary *node) {

    }

    void SemanticAnalysis::visit(ASTBinaryExprNode *node) {

    }

    Scope * SemanticAnalysis::popScope() {
        Scope * tempScope = allScopes.top();
        allScopes.pop();
        return tempScope;
    }

    Scope *SemanticAnalysis::getTopScope() {
        return allScopes.top();
    }

    bool SemanticAnalysis::checkIfIdentifierExists(std::stack<Scope *> scopes, std::string &identifier) {
        Scope * currentScope;

        while (!scopes.empty()) {
            currentScope = scopes.top();
            if (currentScope->checkIfAnIdentifierExists(identifier)) {
                return true;
            }
            scopes.pop();
        }
        return false;
    }

}