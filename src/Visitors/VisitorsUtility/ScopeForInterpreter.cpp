//
// Created by dylan on 11/05/2017.
//
#include "../../../include/Visitors/VisitorsUtility/ScopeForInterpreter.h"
#include "../../../include/Visitors/InterpreterExecution.h"

void visitor::ScopeForInterpreter::addIdentifier(std::string identifier, visitor::Evaluation *evaluation) {
    scopeIdentifiers.insert(std::pair<std::string, Evaluation *>(identifier, evaluation));
}

void visitor::ScopeForInterpreter::addFunctionBlock(std::string identifier, ast::ASTFunctionDeclaration *block) {
    functionsBlock.insert(std::pair<std::string, ast::ASTFunctionDeclaration *>(identifier, block));
}

visitor::Evaluation *visitor::ScopeForInterpreter::returnIdentifierValue(std::string identifier) {
    std::map<std::string, Evaluation *>::iterator it = scopeIdentifiers.find(identifier);

    if (it == scopeIdentifiers.end()) {
        return nullptr;
    }
    return it->second;
}

ast::ASTFunctionDeclaration * visitor::ScopeForInterpreter::returnIdentifierFunctionBlock(std::string identifier) {
    std::map<std::string, ast::ASTFunctionDeclaration *>::iterator it = functionsBlock.find(identifier);

    if (it == functionsBlock.end()) {
        return nullptr;
    }
    return it->second;
}

visitor::ScopeForInterpreter::~ScopeForInterpreter() {
    // Free Evaluation
    for (auto &identifier : scopeIdentifiers) {
        free(identifier.second);
    }
}

void visitor::ScopeForInterpreter::updateSpecialVariableEvaluation(visitor::Evaluation *evaluation) {
    std::map<std::string, Evaluation *>::iterator it = scopeIdentifiers.find(SPECIAL_VARIABLE);

    if (it == scopeIdentifiers.end()) {
        std::cout << "Special Variable not declared." << std::endl;
        exit(2);
    }
    it->second = evaluation;
}
