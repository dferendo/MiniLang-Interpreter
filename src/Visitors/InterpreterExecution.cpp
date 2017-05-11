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

        currentScope->addIdentifier(node->identifier, lastEvaluation);
        // So that lastEvaluation is not cleared.
        lastEvaluation = nullptr;
    }

    void InterpreterExecution::visit(ast::ASTAssignment *node) {
    }

    void InterpreterExecution::visit(ast::ASTPrintStatement *node) {
        string temp;
        node->exprNode->accept(this);

        switch (lastEvaluation->lastTypeUsed) {
            case STRING:
                cout << lastEvaluation->getStringEvaluation() << endl;
                break;
            case REAL:
                cout << lastEvaluation->getRealEvaluation() << endl;
                break;
            case INT:
                cout << lastEvaluation->getIntEvaluation() << endl;
                break;
            case BOOL:
                temp = lastEvaluation->getBoolEvaluation() ? "true" : "false";
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
        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = new Evaluation();
        // Boolean literal are still an expression
        lastEvaluation->setBoolEvaluation(node->literalValue);
    }

    void InterpreterExecution::visit(ast::ASTIntegerLiteral *node) {
        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = new Evaluation();
        lastEvaluation->setIntEvaluation(node->literalValue);
    }

    void InterpreterExecution::visit(ast::ASTRealLiteral *node) {
        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = new Evaluation();
        lastEvaluation->setRealEvaluation(node->realValue);
    }

    void InterpreterExecution::visit(ast::ASTStringLiteral *node) {
        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = new Evaluation();
        lastEvaluation->setStringEvaluation(node->literalString);
    }

    void InterpreterExecution::visit(ast::ASTIdentifier *node) {
        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = new Evaluation();
        lastEvaluation = returnEvaluationOfIdentifierInAllScopes(allScopes, node->identifier);
    }

    void InterpreterExecution::visit(ast::ASTSubExpression *node) {

    }

    void InterpreterExecution::visit(ast::ASTFunctionCall *node) {

    }

    void InterpreterExecution::visit(ast::ASTUnary *node) {

    }

    void InterpreterExecution::visit(ast::ASTBinaryExprNode *node) {
        Evaluation *LHS, *RHS;

        node->LHS->accept(this);
        LHS = lastEvaluation;
        // So that the last evaluation does not get freed
        lastEvaluation = nullptr;
        node->RHS->accept(this);
        RHS = lastEvaluation;
        lastEvaluation = nullptr;

        handleOperator(LHS, RHS, node->operation);

        free(LHS);
        free(RHS);
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

    Evaluation * InterpreterExecution::returnEvaluationOfIdentifierInAllScopes(stack<ScopeForInterpreter *> scopes,
                                                                              string &identifier) {
        ScopeForInterpreter * currentScope;
        Evaluation * temp;

        while (!scopes.empty()) {
            currentScope = scopes.top();
            temp = currentScope->returnIdentifierValue(identifier);
            if (temp != nullptr) {
                return temp;
            }
            scopes.pop();
        }
        // If this occurs, semantic analysis failed.
        cout << "Semantic analysis failed." << endl;
        exit(2);
    }

    void InterpreterExecution::handleOperator(Evaluation *LHS, Evaluation *RHS,
                                              std::string currentOperator) {
        switch (LHS->lastTypeUsed) {
            case STRING:
                handleType(LHS->getStringEvaluation(), RHS->getStringEvaluation(), currentOperator);
                break;
            case REAL:
                handleType(LHS->getRealEvaluation(), RHS->getRealEvaluation(), currentOperator);
                break;
            case INT:
                handleType(LHS->getIntEvaluation(), RHS->getIntEvaluation(), currentOperator);
                break;
            case BOOL:
                handleType(LHS->getBoolEvaluation(), RHS->getBoolEvaluation(), currentOperator);
                break;
        }
    }

    void InterpreterExecution::handleType(std::string LHS, std::string RHS, std::string currentOperator) {
        Evaluation * evaluation = new Evaluation();

        if (!currentOperator.compare("+")) {
            evaluation->setStringEvaluation(LHS + RHS);
        } else {
            cout << "Problem with Semantic analysis, operator not supported for string" << endl;
        }
        lastEvaluation = evaluation;
    }

    void InterpreterExecution::handleType(int LHS, int RHS, std::string currentOperator) {
        Evaluation * evaluation = new Evaluation();

        if (!currentOperator.compare("+")) {
            evaluation->setIntEvaluation(LHS + RHS);
        } else if (!currentOperator.compare("-")) {
            evaluation->setIntEvaluation(LHS - RHS);
        } else if (!currentOperator.compare("*")) {
            evaluation->setIntEvaluation(LHS * RHS);
        } else if (!currentOperator.compare("/")) {
            evaluation->setIntEvaluation(LHS / RHS);
        } else if (!currentOperator.compare("<")) {
            evaluation->setBoolEvaluation(LHS < RHS);
        } else if (!currentOperator.compare(">")) {
            evaluation->setBoolEvaluation(LHS > RHS);
        } else if (!currentOperator.compare("==")) {
            evaluation->setBoolEvaluation(LHS == RHS);
        } else if (!currentOperator.compare("!=")) {
            evaluation->setBoolEvaluation(LHS != RHS);
        } else if (!currentOperator.compare("<=")) {
            evaluation->setBoolEvaluation(LHS <= RHS);
        } else if (!currentOperator.compare(">=")) {
            evaluation->setBoolEvaluation(LHS >= RHS);
        } else {
            cout << "Problem with Semantic analysis, operator not supported for int" << endl;
        }
        lastEvaluation = evaluation;
    }

    void InterpreterExecution::handleType(double LHS, double RHS, std::string currentOperator) {
        Evaluation * evaluation = new Evaluation();

        if (!currentOperator.compare("+")) {
            evaluation->setRealEvaluation(LHS + RHS);
        } else if (!currentOperator.compare("-")) {
            evaluation->setRealEvaluation(LHS - RHS);
        } else if (!currentOperator.compare("*")) {
            evaluation->setRealEvaluation(LHS * RHS);
        } else if (!currentOperator.compare("/")) {
            evaluation->setRealEvaluation(LHS / RHS);
        } else if (!currentOperator.compare("<")) {
            evaluation->setBoolEvaluation(LHS < RHS);
        } else if (!currentOperator.compare(">")) {
            evaluation->setBoolEvaluation(LHS > RHS);
        } else if (!currentOperator.compare("==")) {
            evaluation->setBoolEvaluation(LHS == RHS);
        } else if (!currentOperator.compare("!=")) {
            evaluation->setBoolEvaluation(LHS != RHS);
        } else if (!currentOperator.compare("<=")) {
            evaluation->setBoolEvaluation(LHS <= RHS);
        } else if (!currentOperator.compare(">=")) {
            evaluation->setBoolEvaluation(LHS >= RHS);
        } else {
            cout << "Problem with Semantic analysis, operator not supported for real" << endl;
        }
        lastEvaluation = evaluation;
    }

    void InterpreterExecution::handleType(bool LHS, bool RHS, std::string currentOperator) {
        Evaluation * evaluation = new Evaluation();

        if (!currentOperator.compare("and")) {
            evaluation->setBoolEvaluation(LHS && RHS);
        } else if (!currentOperator.compare("or")) {
            evaluation->setBoolEvaluation(LHS || RHS);
        } else {
            cout << "Problem with Semantic analysis, operator not supported for bool" << endl;
        }
        lastEvaluation = evaluation;
    }
}