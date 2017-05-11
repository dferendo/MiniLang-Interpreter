//
// Created by dylan on 11/05/2017.
//
#include "../../include/Visitors/ScopeForInterpreter.h"

void visitor::ScopeForInterpreter::addIdentifier(std::string identifier, visitor::Evaluation *evaluation) {
    scopeIdentifiers.insert(std::pair<std::string, Evaluation *>(identifier, evaluation));
}

visitor::Evaluation *visitor::ScopeForInterpreter::returnIdentifierValue(std::string identifier) {
    std::map<std::string, Evaluation *>::iterator it = scopeIdentifiers.find(identifier);

    if (it == scopeIdentifiers.end()) {
        return nullptr;
    }
    return it->second;
}
