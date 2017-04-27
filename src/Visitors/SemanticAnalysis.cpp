//
// Created by dylan on 25/04/2017.
//
#include "../../include/Visitors/SemanticAnalysis.h"
#include "../../include/AST/ASTNode.h"
#include "../../include/AST/ASTStatements/ASTStatementNode.h"
#include "../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include "../../include/AST/ASTStatements/ASTBlock.h"
#include "../../include/AST/ASTStatements/ASTAssignment.h"
#include "../../include/AST/ASTExpression/ASTBinaryExprNode.h"
#include "../../include/AST/ASTStatements/ASTFunctionDeclaration.h"
#include "../../include/AST/ASTExpression/ASTFunctionCall.h"

using namespace ast;
using namespace std;
using namespace lexer;

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
            cout << "Duplicate declaration of local variable '" << node->identifier << "'" << endl;
            exit(1);
        }
        // Get the expression type
        node->expression->accept(this);
        // Check if token is real, if so int is accepted.
        if ((node->tokenType == TOK_RealType) && lastToken == TOK_IntType) {
            // Accept identifier
            currentScope->addIdentifier(node);
            return;
        } else if (lastToken != node->tokenType) {
            cout << "Incompatible types, expected '" << TOKEN_STRING[node->tokenType]
                 << "'" << endl;
            exit(1);
        }
        // Add the identifier
        currentScope->addIdentifier(node);

    }

    void SemanticAnalysis::visit(ASTAssignment *node) {
        // Check if the identifier exists, if not exits.
        if (!checkIfIdentifierExistsInAllScopes(allScopes, node->identifier)) {
            cout << "Can't resolve variable '" << node->identifier << "'" << endl;
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
        // Get the scope the node is currently in
        Scope * currentScope = getTopScope();
        // Check if function exists
        if (currentScope->checkIfAnIdentifierExists(node->identifier)) {
            cout << "Duplicate declaration of variable for function '" << node->identifier << "'"
                 << endl;
            exit(1);
        }
        // Add function
        currentScope->addIdentifier(node);
    }

    void SemanticAnalysis::visit(ASTBooleanLiteral *node) {
        // Set the last tok to boolean literal.
        lastToken = TOK_BoolType;
    }

    void SemanticAnalysis::visit(ASTIntegerLiteral * node) {
        // Set the last tok to integer literal.
        lastToken = TOK_IntType;
    }

    void SemanticAnalysis::visit(ASTRealLiteral * node) {
        // Set the last tok to real literal.
        lastToken = TOK_RealType;
    }

    void SemanticAnalysis::visit(ASTStringLiteral * node) {
        // Set the last tok to string literal.
        lastToken = TOK_StringType;
    }

    void SemanticAnalysis::visit(ASTIdentifier *node) {
        // Check the token of the identifier If it exists
        TOKEN identifierToken = returnTokenOfIdentifierInAllScopes(allScopes, node->identifier);

        if (identifierToken == TOK_Error) {
            cout << "Can't resolve variable '" << node->identifier << "'" << endl;
            exit(1);
        }
        lastToken = identifierToken;
    }

    void SemanticAnalysis::visit(ASTSubExpression *node) {

    }

    void SemanticAnalysis::visit(ASTFunctionCall *node) {
        vector<ast::ASTFormalParam *> * params =
                returnFunctionParamsInAllScopes(allScopes, node->identifier);

        if (params == nullptr) {
            cout << "Can't resolve function '" << node->identifier << "'" << endl;
            exit(1);
        }
        // Check if params match
        if (params->size() != node->actualParams.size()) {
            cout << "Incorrect arguments passed, expected " << params->size() << endl;
            exit(1);
        }

        for (size_t i = 0; i < node->actualParams.size(); i++) {
            node->actualParams[i]->accept(this);
            if (lastToken != (*params)[i]->tokenType) {
                cout << "Parameter type mismatch, expecting '" << TOKEN_STRING[(*params)[i]->tokenType]
                     << "'" << endl;
                exit(1);
            }
        }
        // Set the return type
        lastToken = returnTokenOfIdentifierInAllScopes(allScopes, node->identifier);
    }

    void SemanticAnalysis::visit(ASTUnary *node) {

    }

    void SemanticAnalysis::visit(ASTBinaryExprNode *node) {
        int operatorReturn;
        TOKEN tokenLHS, tokenRHS;

        node->LHS->accept(this);
        tokenLHS = lastToken;
        node->RHS->accept(this);
        tokenRHS = lastToken;

        operatorReturn = handleOperatorType(tokenLHS, tokenRHS, node->operation);
        // Handle operator compatible type
        if (operatorReturn == -1) {
            cout << "Operator not supported for one of the types "
                 << TOKEN_STRING[tokenLHS] << " or "
                 << TOKEN_STRING[tokenRHS] << endl;
            exit(1);
        } else if (operatorReturn == -2) {
            cout << "Incompatible types of " << TOKEN_STRING[tokenLHS]
                 << " and " << TOKEN_STRING[tokenRHS] << endl;
            exit(1);
        } else if (operatorReturn == -3) {
            cout << "Operator not found, problem with lexer." << endl;
            exit(1);
        }
    }

    Scope * SemanticAnalysis::popScope() {
        Scope * tempScope = allScopes.top();
        allScopes.pop();
        return tempScope;
    }

    Scope *SemanticAnalysis::getTopScope() {
        return allScopes.top();
    }

    bool SemanticAnalysis::checkIfIdentifierExistsInAllScopes(stack<Scope *> scopes, string &identifier) {
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

    TOKEN SemanticAnalysis::returnTokenOfIdentifierInAllScopes(stack<Scope *> scopes,
                                                               string &identifier) {
        Scope * currentScope;
        TOKEN tempToken;

        while (!scopes.empty()) {
            currentScope = scopes.top();
            tempToken = currentScope->returnTheTokenOfAnIdentifier(identifier);
            if (tempToken != TOK_Error) {
                return tempToken;
            }
            scopes.pop();
        }
        return TOK_Error;
    }

    int SemanticAnalysis::handleOperatorType(TOKEN lhs, TOKEN rhs, string binaryOperator) {

        // Operators *, / and - all accept int or real only.
        if (!binaryOperator.compare("*") || !binaryOperator.compare("/") || !binaryOperator.compare("-")) {
            // Types not supported
            if ((lhs == TOK_StringType || lhs == TOK_BoolType) ||
                (rhs == TOK_StringType || rhs == TOK_BoolType)) {
                return -1;
            } else {
                // real can support int, while vice versa not true.
                lastToken = (lhs == TOK_IntType && rhs == TOK_IntType)
                            ? TOK_IntType : TOK_RealType;
                return 0;
            }
        } else if (!binaryOperator.compare("and") || !binaryOperator.compare("or")) {
            // 'and' and 'or' is only accepted by boolean
            if (lhs == TOK_BoolType && rhs == TOK_BoolType) {
                lastToken = TOK_BoolType;
                return 0;
            } else {
                return -1;
            }
        } else if (!binaryOperator.compare("+")) {
            // Boolean does not support +
            if (lhs == TOK_BoolType && rhs == TOK_BoolType) {
                return -1;
            } else if (lhs == TOK_StringType && rhs == TOK_StringType) {
                lastToken = TOK_StringType;
                // + can be on int, real and string. String concatenate the strings.
                return 0;
            } else if (lhs == TOK_StringType || rhs == TOK_StringType) {
                // Only 1 expression is a string, incompatible type
                return -2;
            } else {
                lastToken = (lhs == TOK_IntType && rhs == TOK_IntType)
                            ? TOK_IntType : TOK_RealType;
                // Means int and real remains
                return 0;
            }
        }
        // All relational returns bool
        lastToken = TOK_BoolType;
        // Handle relational types
        if (!binaryOperator.compare("<") || !binaryOperator.compare(">") ||
            !binaryOperator.compare("<=") || !binaryOperator.compare(">=")) {
            // Types not supported
            if ((lhs == TOK_StringType || lhs == TOK_BoolType) ||
                (rhs == TOK_StringType || rhs == TOK_BoolType)) {
                return -1;
            } else {
                // real can support int, while vice versa not true.
                return 0;
            }
        } else if (!binaryOperator.compare("==") || !binaryOperator.compare("!=")) {
            // Compare needs to have both types the same
            if (lhs == TOK_StringType && rhs == TOK_StringType) {
                return 0;
            } else if (lhs == TOK_BoolType && rhs == TOK_BoolType) {
                return 0;
            } else if (lhs == TOK_StringType || rhs == TOK_StringType) {
                return -2;
            } else if (lhs == TOK_BoolType || rhs == TOK_BoolType) {
                return -2;
            } else {
                // Int and real can be compared
                return 0;
            }
        }
        // No operator found
        return -3;
    }

    vector<ast::ASTFormalParam *> *
    SemanticAnalysis::returnFunctionParamsInAllScopes(stack<Scope *> scopes, string &identifier) {
        Scope * currentScope;
        vector<ast::ASTFormalParam *> * params;

        while (!scopes.empty()) {
            currentScope = scopes.top();
            params = currentScope->returnFormalsOfFunction(identifier);
            if (params != nullptr) {
                return params;
            }
            scopes.pop();
        }
        return nullptr;
    }

}