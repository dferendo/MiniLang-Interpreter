//
// Created by dylan on 28/04/2017.
//
#include <functional>
#include "../../include/Visitors/InterpreterExecution.h"
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
#include "../../include/Exceptions/InterpreterError.h"
#include "../../include/AST/ASTStatements/ASTExprStatement.h"

using namespace ast;
using namespace std;
using namespace lexer;

namespace visitor {

    InterpreterExecution::InterpreterExecution() {
        // This global scope is made so that MiniLangI can use it.
        pushScope(globalScope);
        // Special variable "ans"
        globalScope->addIdentifier(SPECIAL_VARIABLE, nullptr);
    }

    InterpreterExecution::~InterpreterExecution() {
        ScopeForInterpreter * globalScope = popScope();
        free(globalScope);
    }

    void InterpreterExecution::visit(ast::ASTNode *node) {
        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
    }

    void InterpreterExecution::visit(ast::ASTVariableDeclaration *node) {
        ScopeForInterpreter * currentScope = getTopScope();

        node->expression->accept(this);

        // A real variable can be declared with int variables, if so transfer the
        // int variable to a real variable. (Semantic analysis accepts this)
        if (node->tokenType == TOK_RealType && lastEvaluation->lastTypeUsed == INT) {
            lastEvaluation->setRealEvaluation(lastEvaluation->getIntEvaluation());
        }

        currentScope->addIdentifier(node->identifier, lastEvaluation);
        // Set the special variable.
        globalScope->updateSpecialVariableEvaluation(lastEvaluation);
        // So that lastEvaluation is not cleared.
        lastEvaluation = nullptr;
    }

    void InterpreterExecution::visit(ast::ASTAssignment *node) {
        // Assignment cannot change type so use the identifier previous Evaluation
        Evaluation * assignmentEvaluation =
                returnEvaluationOfIdentifierInAllScopes(allScopes, node->identifier);

        node->exprNode->accept(this);

        switch (lastEvaluation->lastTypeUsed) {
            case STRING:
                assignmentEvaluation->setStringEvaluation(lastEvaluation->getStringEvaluation());
                break;
            case REAL:
                assignmentEvaluation->setRealEvaluation(lastEvaluation->getRealEvaluation());
                break;
            case INT:
                // If the previous evaluation was real, the new assignment will also be
                // real, This is accepted by semantic analysis.
                if (assignmentEvaluation->lastTypeUsed == REAL) {
                    assignmentEvaluation->setRealEvaluation(lastEvaluation->getIntEvaluation());
                } else {
                    assignmentEvaluation->setIntEvaluation(lastEvaluation->getIntEvaluation());
                }
                break;
            case BOOL:
                assignmentEvaluation->setBoolEvaluation(lastEvaluation->getBoolEvaluation());
                break;
        }
        globalScope->updateSpecialVariableEvaluation(lastEvaluation);
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
        ScopeForInterpreter *blockScope = new ScopeForInterpreter();
        ast::ASTFunctionDeclaration * functionDeclaration;
        // Push new Scope
        pushScope(blockScope);

        // Check if it was a function
        if (isNextBlockFunction) {
            isNextBlockFunction = false;
            functionDeclaration = returnBlockOfFunction(allScopes, functionCalled.identifier);
            // Put the function arguments passed with the identifiers of the function
            // and add them to the scope.
            for (unsigned long i = 0; i < functionCalled.paramsOfAFunction.size(); i++) {
                functionCalled.paramsOfAFunction.at(i)->accept(this);
                functionDeclaration->formalParams.at(i)->accept(this);
            }
        }

        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
        popScope();
        free(blockScope);
    }

    void InterpreterExecution::visit(ast::ASTIfStatement *node) {
        node->exprNode->accept(this);

        if (lastEvaluation->getBoolEvaluation()) {
            node->astBlockForIF->accept(this);
            return;
        }
        // Optional else block.
        if (node->astBlockForElse != nullptr) {
            node->astBlockForElse->accept(this);
        }
    }

    void InterpreterExecution::visit(ast::ASTWhileStatement *node) {

        while (true) {
            // Evaluate the condition
            node->exprNode->accept(this);
            if (lastEvaluation->getBoolEvaluation()) {
                node->astBlock->accept(this);
            } else {
                break;
            }
        }
    }

    void InterpreterExecution::visit(ast::ASTReturnStatement *node) {
        node->exprNode->accept(this);
    }

    void InterpreterExecution::visit(ast::ASTFormalParam *node) {
        ScopeForInterpreter * currentScope = getTopScope();
        // The actual param is located at the last Evaluation
        currentScope->addIdentifier(node->identifier, lastEvaluation);
        // So that lastEvaluation is not cleared.
        lastEvaluation = nullptr;
    }

    void InterpreterExecution::visit(ast::ASTFunctionDeclaration *node) {
        ScopeForInterpreter * currentScope = getTopScope();
        // Hold the block of the function so that the block can be executed when
        // called and hold the parameters so the arguments of function call
        // can be substituted with the parameters of the function.
        currentScope->addFunctionBlock(node->identifier, node);
    }

    void InterpreterExecution::visit(ast::ASTExprStatement *node) {
        node->exprNode->accept(this);

        globalScope->updateSpecialVariableEvaluation(lastEvaluation);
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
        Evaluation * evaluation;
        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = new Evaluation();
        evaluation = returnEvaluationOfIdentifierInAllScopes(allScopes, node->identifier);
        // Create a copy of the identifier so that the previous identifier remains untouched
        switch (evaluation->lastTypeUsed) {
            case STRING:
                lastEvaluation->setStringEvaluation(evaluation->getStringEvaluation());
                break;
            case REAL:
                lastEvaluation->setRealEvaluation(evaluation->getRealEvaluation());
                break;
            case INT:
                lastEvaluation->setIntEvaluation(evaluation->getIntEvaluation());
                break;
            case BOOL:
                lastEvaluation->setBoolEvaluation(evaluation->getBoolEvaluation());
                break;
        }
    }

    void InterpreterExecution::visit(ast::ASTSubExpression *node) {
        node->subExpression->accept(this);
    }

    void InterpreterExecution::visit(ast::ASTFunctionCall *node) {
        ast::ASTFunctionDeclaration * functionDeclaration;
        // Set variables so that block knows the new function
        isNextBlockFunction = true;
        functionCalled.identifier = node->identifier;
        functionCalled.paramsOfAFunction = node->actualParams;

        functionDeclaration = returnBlockOfFunction(allScopes, node->identifier);
        // Call block to be executed
        functionDeclaration->astBlock->accept(this);
        // The return will be updated by the return function.
    }

    void InterpreterExecution::visit(ast::ASTUnary *node) {
        Evaluation * evaluation = new Evaluation();
        node->unaryExpression->accept(this);

        if (!node->unary.compare("not")) {
            evaluation->setBoolEvaluation(!lastEvaluation->getBoolEvaluation());
        } else if (!node->unary.compare("-")) {
            if (lastEvaluation->lastTypeUsed == INT) {
                evaluation->setIntEvaluation(lastEvaluation->getIntEvaluation() * -1);
            } else if (lastEvaluation->lastTypeUsed == REAL) {
                evaluation->setRealEvaluation(lastEvaluation->getRealEvaluation() * -1);
            } else {
                cout << "Semantic analysis incorrect for Unary." << endl;
                exit(1);
            }
        } else {
            cout << "Semantic analysis incorrect for Unary." << endl;
            exit(1);
        }

        if (lastEvaluation != nullptr) {
            free(lastEvaluation);
        }
        lastEvaluation = evaluation;
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
        cout << "Semantic analysis failed. Identifier is suppose to exists." << endl;
        exit(2);
    }

    ast::ASTFunctionDeclaration *
    InterpreterExecution::returnBlockOfFunction(std::stack<ScopeForInterpreter *> scopes, std::string &identifier) {
        ScopeForInterpreter * currentScope;
        ASTFunctionDeclaration * temp;

        while (!scopes.empty()) {
            currentScope = scopes.top();
            temp = currentScope->returnIdentifierFunctionBlock(identifier);
            if (temp != nullptr) {
                return temp;
            }
            scopes.pop();
        }
        // If this occurs, semantic analysis failed.
        cout << "Semantic analysis failed. Function declaration should exists." << endl;
        exit(2);
    }

    void InterpreterExecution::handleOperator(Evaluation *LHS, Evaluation *RHS,
                                              std::string currentOperator) {
        // In this case one is of type int and the other is real.
        // Semantic analysis allows this.
        if (LHS->lastTypeUsed != RHS->lastTypeUsed) {
            if (LHS->lastTypeUsed == INT) {
                LHS->setRealEvaluation(LHS->getIntEvaluation());
            } else if (RHS->lastTypeUsed == INT) {
                RHS->setRealEvaluation(RHS->getIntEvaluation());
            } else {
                cout << "Semantic analysis error, two different types are given"
                        "which are not int or real!" << endl;
                exit(1);
            }
        }

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
            exit(1);
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
            if (RHS == 0) {
                throw exceptions::InterpreterError("Division by 0 is not allowed.");
            }
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
            exit(1);
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
            if (RHS == 0) {
                throw exceptions::InterpreterError("Division by 0 is not allowed.");
            }
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
            exit(1);
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
            exit(1);
        }
        lastEvaluation = evaluation;
    }

    void InterpreterExecution::printCurrentStatements() {
        unsigned currentParamCounter;
        // -1 to remove ans
        if (globalScope->scopeIdentifiers.size() - 1 != 0) {
            cout << "Variables: " << endl;

            for (auto &identifier : globalScope->scopeIdentifiers) {
                if (!identifier.first.compare(SPECIAL_VARIABLE)) {
                    continue;
                }
                cout << identifier.first << " : " << TYPE_USED_STRING[identifier.second->lastTypeUsed]
                     << endl;
            }
        }

        if (globalScope->functionsBlock.size() != 0) {
            cout << "Functions: " << endl;

            for (auto &identifier : globalScope->functionsBlock) {
                currentParamCounter = 0;
                cout << identifier.first << " : " << TYPE_USED_STRING[identifier.second->tokenType];
                cout << " params: (";
                for (auto &param : identifier.second->formalParams) {
                    if (currentParamCounter++ == identifier.second->formalParams.size() - 1) {
                        cout << param->identifier << " : " << TOKEN_STRING[param->tokenType];
                    } else {
                        cout << param->identifier << " : " << TOKEN_STRING[param->tokenType] << ", ";
                    }
                }
                cout << ")" << endl;
            }
        }

        if (globalScope->scopeIdentifiers.size() == 0 && globalScope->functionsBlock.size() == 0) {
            cout << "Currently no statements!" << endl;
        }
    }

    void InterpreterExecution::printSpecialVariableIfChanged() {
        Evaluation * tempEvaluation;
        std::map<std::string, Evaluation *>::iterator it = globalScope->scopeIdentifiers.find(SPECIAL_VARIABLE);

        if (it == globalScope->scopeIdentifiers.end()) {
            std::cout << "Special Variable not declared." << std::endl;
            exit(2);
        }
        if (it->second != nullptr) {
            tempEvaluation = it->second;
            cout << "var " << SPECIAL_VARIABLE << " : " <<  TYPE_USED_STRING[tempEvaluation->lastTypeUsed] << " = ";
            switch (tempEvaluation->lastTypeUsed) {
                case STRING:
                    cout << tempEvaluation->getStringEvaluation() << endl;
                    break;
                case REAL:
                    cout << tempEvaluation->getRealEvaluation() << endl;
                    break;
                case INT:
                    cout << tempEvaluation->getIntEvaluation() << endl;
                    break;
                case BOOL:
                    cout << tempEvaluation->getBoolEvaluation() << endl;
                    break;
            }
            // Resets the evaluation so that if for example a print statements comes after, it does not re-print.
            it->second = nullptr;
        }
    }

}