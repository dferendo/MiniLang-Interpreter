//
// Created by dylan on 25/04/2017.
//
#include "../../include/Visitors/SemanticAnalysis.h"
#include "../../include/AST/ASTStatements/ASTStatementNode.h"
#include "../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include "../../include/AST/ASTStatements/ASTBlock.h"
#include "../../include/AST/ASTStatements/ASTAssignment.h"
#include "../../include/AST/ASTExpression/ASTBinaryExprNode.h"
#include "../../include/AST/ASTStatements/ASTFunctionDeclaration.h"
#include "../../include/AST/ASTExpression/ASTFunctionCall.h"
#include "../../include/AST/ASTExpression/ASTSubExpression.h"
#include "../../include/AST/ASTExpression/ASTUnary.h"
#include "../../include/AST/ASTStatements/ASTPrintStatement.h"
#include "../../include/AST/ASTStatements/ASTIfStatement.h"
#include "../../include/AST/ASTStatements/ASTWhileStatement.h"
#include "../../include/AST/ASTStatements/ASTReturnStatement.h"
#include "../../include/Exceptions/SemanticAnalysisError.h"
#include "../../include/AST/ASTStatements/ASTExprStatement.h"
#include "../../include/Visitors/InterpreterExecution.h"

using namespace ast;
using namespace std;
using namespace lexer;
using namespace exceptions;

namespace visitor {

    SemanticAnalysis::SemanticAnalysis() {
        // This global scope is made so that MiniLangI can use it.
        pushScope(globalScope);
        // Special variable "ans"
        globalScope->addIdentifier(SPECIAL_VARIABLE);
    }

    void SemanticAnalysis::pushScope(Scope *scope) {
        allScopes.push(scope);
    }

    void SemanticAnalysis::visit(ASTNode *node) {
        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
    }

    SemanticAnalysis::~SemanticAnalysis() {
        Scope * globalScope = popScope();
        free(globalScope);
    }

    void SemanticAnalysis::visit(ASTVariableDeclaration *node) {
        // Get the scope the node is currently in
        Scope * currentScope = getTopScope();
        // Check if identifier exists. Do not add it yet to avoid
        // var test4 : int = test4;
        if (currentScope->identifierExists(node->identifier)) {
            throw SemanticAnalysisError("Duplicate declaration of local variable '" + node->identifier + "'");
        }
        // Get the expression type
        node->expression->accept(this);
        // Check if token is real, if so int is accepted.
        if ((node->tokenType == TOK_RealType) && lastToken == TOK_IntType) {
            // Accept identifier
            currentScope->addIdentifier(node);
            return;
        } else if (lastToken != node->tokenType) {
            throw SemanticAnalysisError("Incompatible types, expected '" + TOKEN_STRING[node->tokenType] + "'");
        }
        // Add the identifier
        currentScope->addIdentifier(node);
    }

    void SemanticAnalysis::visit(ASTAssignment *node) {
        TOKEN identifierToken = returnTokenOfIdentifierInAllScopes(allScopes, node->identifier);
        // Check if the identifier exists, if not exits.
        if (identifierToken == TOK_Error) {
            throw SemanticAnalysisError("Can't resolve variable '" + node->identifier + "'");
        }
        // Get the expression type
        node->exprNode->accept(this);
        // Check if token is real, if so int is accepted.
        if ((identifierToken == TOK_RealType) && lastToken == TOK_IntType) {
            return;
        } else if (lastToken != identifierToken) {
            throw SemanticAnalysisError("Incompatible types, expected '" + TOKEN_STRING[identifierToken] + "'");
        }
    }

    void SemanticAnalysis::visit(ASTPrintStatement *node) {
        // Check if expression is correct.
        node->exprNode->accept(this);
    }

    void SemanticAnalysis::visit(ASTBlock *node) {
        Scope *blockScope = new Scope();
        // Push new Scope
        pushScope(blockScope);

        for (auto &function : functionsReturn) {
            if (!function->isFunctionDeclarationBlock) {
                function->isFunctionDeclarationBlock = true;
                // Add params to the new block
                for (auto const &param : function->functionDeclaration->formalParams) {
                    param->accept(this);
                }
                // Can only happen one at a time
                break;
            }
        }

        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
        // Pop scope
        popScope();
        free(blockScope);
    }

    void SemanticAnalysis::visit(ASTIfStatement *node) {
        node->exprNode->accept(this);

        if (lastToken != TOK_BoolType) {
            throw SemanticAnalysisError("If only supports boolean. ");
        }
        node->astBlockForIF->accept(this);
        // Go to else block as well
        if (node->astBlockForElse != nullptr) {
            node->astBlockForElse->accept(this);
        }
    }

    void SemanticAnalysis::visit(ASTWhileStatement *node) {
        node->exprNode->accept(this);

        if (lastToken != TOK_BoolType) {
            throw SemanticAnalysisError("While only supports boolean. ");
        }
        node->astBlock->accept(this);
    }

    void SemanticAnalysis::visit(ASTReturnStatement *node) {
        ReturnCheckForFunctionDeclaration * returnCheckForFunctionDeclaration;

        node->exprNode->accept(this);

        returnCheckForFunctionDeclaration = functionsReturn.back();

        if (lastToken != returnCheckForFunctionDeclaration->functionDeclaration->tokenType) {
            throw SemanticAnalysisError("Returning '" + TOKEN_STRING[lastToken] + "' when expecting '"
                                                      + TOKEN_STRING[returnCheckForFunctionDeclaration->functionDeclaration->tokenType]);
        }
        returnCheckForFunctionDeclaration->isReturnFound = true;
    }

    void SemanticAnalysis::visit(ASTFormalParam *node) {
        Scope * currentScope = getTopScope();
        // Check if identifier exists
        if (currentScope->identifierExists(node->identifier)) {
            throw SemanticAnalysisError("Duplicate declaration of local variable '" + node->identifier + "'");
        }
        // Add the identifier
        currentScope->addIdentifier(node);
    }

    void SemanticAnalysis::visit(ASTFunctionDeclaration *node) {
        ReturnCheckForFunctionDeclaration * returnCheckForFunctionDeclaration;
        // Get the scope the node is currently in
        Scope * currentScope = getTopScope();
        // Check if function exists
        if (currentScope->identifierExists(node->identifier)) {
            throw SemanticAnalysisError("Duplicate declaration of variable for function '" + node->identifier + "'");
        }
        // Add function
        currentScope->addIdentifier(node);

        returnCheckForFunctionDeclaration = new ReturnCheckForFunctionDeclaration();
        // Variable used to check if there was a return
        returnCheckForFunctionDeclaration->isReturnFound = false;
        returnCheckForFunctionDeclaration->isFunctionDeclarationBlock = false;
        returnCheckForFunctionDeclaration->functionDeclaration = node;
        functionsReturn.push_back(returnCheckForFunctionDeclaration);

        // Go to block
        node->astBlock->accept(this);

        // Check if there was a return.
        returnCheckForFunctionDeclaration = functionsReturn.back();
        functionsReturn.pop_back();
        if (!returnCheckForFunctionDeclaration->isReturnFound) {
            throw SemanticAnalysisError("Control reaches end of non-void function, return required. ");
        }
        free(returnCheckForFunctionDeclaration);
    }

    void SemanticAnalysis::visit(ast::ASTExprStatement *node) {
        node->exprNode->accept(this);
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
            throw SemanticAnalysisError("Can't resolve variable '" + node->identifier + "'");
        }
        lastToken = identifierToken;
    }

    void SemanticAnalysis::visit(ASTSubExpression *node) {
        node->subExpression->accept(this);
    }

    void SemanticAnalysis::visit(ASTFunctionCall *node) {
        vector<ast::ASTFormalParam *> * params =
                returnFunctionParamsInAllScopes(allScopes, node->identifier);

        if (params == nullptr) {
            throw SemanticAnalysisError("Can't resolve function '" + node->identifier + "'");
        }
        // Check if params match
        if (params->size() != node->actualParams.size()) {
            throw SemanticAnalysisError("Incorrect arguments passed, expected " + params->size());
        }

        for (size_t i = 0; i < node->actualParams.size(); i++) {
            node->actualParams[i]->accept(this);

            // Integers can be passed as real.
            if (lastToken == TOK_IntType && (*params)[i]->tokenType == TOK_RealType) {
                continue;
            }

            if (lastToken != (*params)[i]->tokenType) {
                throw SemanticAnalysisError("Parameter type mismatch, expecting '" + TOKEN_STRING[(*params)[i]->tokenType]
                                            + "'");
            }
        }
        // Set the return type
        lastToken = returnTokenOfIdentifierInAllScopes(allScopes, node->identifier);
    }

    void SemanticAnalysis::visit(ASTUnary *node) {
        // Check type of expression
        node->unaryExpression->accept(this);

        if (lastToken == TOK_StringType) {
            throw SemanticAnalysisError("Operator not supported for "
                                        + TOKEN_STRING[TOK_StringType]);
        } else if (lastToken == TOK_BoolType) {
            // Not can only be applied to boolean, compare returns 0
            // if equal
            if (node->unary.compare("not")) {
                throw SemanticAnalysisError("Operator not supported for "
                                            + TOKEN_STRING[TOK_BoolType]);
            }
        } else if (lastToken == TOK_IntType || lastToken == TOK_RealType) {
            // - can only be applied to int and real
            if (node->unary.compare("-")) {
                throw SemanticAnalysisError("Operator not supported for "
                                            + TOKEN_STRING[lastToken]);
            }
        } else {
            throw SemanticAnalysisError("Type not supported.");
        }
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
            throw SemanticAnalysisError("Operator not supported for one of the types "
                                        + TOKEN_STRING[tokenLHS] + " or "
                                        + TOKEN_STRING[tokenRHS] + ".");
        } else if (operatorReturn == -2) {
            throw SemanticAnalysisError("Incompatible types of " + TOKEN_STRING[tokenLHS]
                                        + " and " + TOKEN_STRING[tokenRHS]);
        } else if (operatorReturn == -3) {
            throw SemanticAnalysisError("Operator not found, problem with lexer.");
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