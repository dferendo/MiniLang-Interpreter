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
        // Check if identifier exists. Do not add it yet to avoid
        // var test4 : int = test4;
        if (currentScope->checkIfAnIdentifierExists(node->identifier)) {
            std::cout << "Duplicate declaration of local variable '" << node->identifier << "'" << std::endl;
            exit(1);
        }
        // Get the expression type
        node->expression->accept(this);
        if (lastToken != node->tokenType) {
            std::cout << "Incompatible types, expected '" << lexer::TOKEN_STRING[node->tokenType]
                      << "'" << std::endl;
        }
        // Add the identifier
        currentScope->addIdentifier(node);

    }

    void SemanticAnalysis::visit(ASTAssignment *node) {
        // Check if the identifier exists, if not exits.
        if (!checkIfIdentifierExistsInAllScopes(allScopes, node->identifier)) {
            std::cout << "Can't resolve variable '" << node->identifier << "'" << std::endl;
            exit(1);
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
        // Set the last tok to boolean literal.
        lastToken = lexer::TOK_BoolType;
    }

    void SemanticAnalysis::visit(ASTIntegerLiteral * node) {
        // Set the last tok to integer literal.
        lastToken = lexer::TOK_IntType;
    }

    void SemanticAnalysis::visit(ASTRealLiteral * node) {
        // Set the last tok to real literal.
        lastToken = lexer::TOK_RealType;
    }

    void SemanticAnalysis::visit(ASTStringLiteral * node) {
        // Set the last tok to string literal.
        lastToken = lexer::TOK_StringType;
    }

    void SemanticAnalysis::visit(ASTIdentifier *node) {
        // Check the token of the identifier IF it exists
        lexer::TOKEN identifierToken = returnTokenOfIdentifier(allScopes, node->identifier);

        if (identifierToken == lexer::TOK_Error) {
            std::cout << "Can't resolve variable '" << node->identifier << "'" << std::endl;
            exit(1);
        }
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

    bool SemanticAnalysis::checkIfIdentifierExistsInAllScopes(std::stack<Scope *> scopes, std::string &identifier) {
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

    lexer::TOKEN SemanticAnalysis::returnTokenOfIdentifier(std::stack<Scope *> scopes, std::string &identifier) {
        Scope * currentScope;
        lexer::TOKEN tempToken;

        while (!scopes.empty()) {
            currentScope = scopes.top();
            tempToken = currentScope->returnTheTokenOfAnIdentifier(identifier);
            if (tempToken != lexer::TOK_Error) {
                return tempToken;
            }
            scopes.pop();
        }
        return lexer::TOK_Error;
    }

}