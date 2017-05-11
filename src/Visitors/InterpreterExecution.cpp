//
// Created by dylan on 28/04/2017.
//
#include "../../include/Visitors/InterpreterExecution.h"
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
#include "../../include/AST/ASTExpression/ASTStringLiteral.h"
#include "../../include/AST/ASTExpression/ASTBooleanLiteral.h"
#include "../../include/AST/ASTExpression/ASTIntegerLiteral.h"
#include "../../include/AST/ASTExpression/ASTRealLiteral.h"

using namespace ast;
using namespace std;
using namespace lexer;

namespace visitor {
    
    void InterpreterExecution::visit(ast::ASTNode *node) {
        // Add Global scope
        ScopeForInterpreter * globalScope = new ScopeForInterpreter();
        pushScope(globalScope);

        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
        popScope();
    }

    void InterpreterExecution::visit(ast::ASTVariableDeclaration *node) {
        ScopeForInterpreter * currentScope = getTopScope();

        node->expression->accept(this);

        currentScope->addIdentifier(node->identifier, &lastEvaluation);
    }

    void InterpreterExecution::visit(ast::ASTAssignment *node) {
    }

    void InterpreterExecution::visit(ast::ASTPrintStatement *node) {
        string temp;
        node->exprNode->accept(this);

        switch (lastEvaluation.lastTypeUsed) {
            case STRING:
                cout << lastEvaluation.getStringEvaluation() << endl;
                break;
            case REAL:
                cout << lastEvaluation.getRealEvaluation() << endl;
                break;
            case INT:
                cout << lastEvaluation.getIntEvaluation() << endl;
                break;
            case BOOL:
                temp = lastEvaluation.getBoolEvaluation() ? "true" : "false";
                cout << temp << endl;
                break;
        }
    }

    void InterpreterExecution::visit(ast::ASTBlock *node) {

    }

    void InterpreterExecution::visit(ast::ASTIfStatement *node) {

    }

    void InterpreterExecution::visit(ast::ASTWhileStatement *node) {

    }

    void InterpreterExecution::visit(ast::ASTReturnStatement *node) {

    }

    void InterpreterExecution::visit(ast::ASTFormalParam *node) {

    }

    void InterpreterExecution::visit(ast::ASTFunctionDeclaration *node) {

    }

    void InterpreterExecution::visit(ast::ASTBooleanLiteral *node) {
        // Boolean literal are still an expression
        lastEvaluation.setBoolEvaluation(node->literalValue);
    }

    void InterpreterExecution::visit(ast::ASTIntegerLiteral *node) {
        lastEvaluation.setIntEvaluation(node->literalValue);
    }

    void InterpreterExecution::visit(ast::ASTRealLiteral *node) {
        lastEvaluation.setRealEvaluation(node->realValue);
    }

    void InterpreterExecution::visit(ast::ASTStringLiteral *node) {
        lastEvaluation.setStringEvaluation(node->literalString);
    }

    void InterpreterExecution::visit(ast::ASTIdentifier *node) {

    }

    void InterpreterExecution::visit(ast::ASTSubExpression *node) {

    }

    void InterpreterExecution::visit(ast::ASTFunctionCall *node) {

    }

    void InterpreterExecution::visit(ast::ASTUnary *node) {

    }

    void InterpreterExecution::visit(ast::ASTBinaryExprNode *node) {

    }

    void InterpreterExecution::pushScope(ScopeForInterpreter *scope) {
        allScopes.push(scope);
    }

    ScopeForInterpreter *InterpreterExecution::popScope() {
        ScopeForInterpreter * tempScope = allScopes.top();
        allScopes.pop();
        return tempScope;
    }

    ScopeForInterpreter *InterpreterExecution::getTopScope() {
        return allScopes.top();
    }
}