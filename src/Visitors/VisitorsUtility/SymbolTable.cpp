//
// Created by dylan on 27/04/2017.
//
#include "../../../include/Visitors/VisitorsUtility/SymbolTable.h"

visitor::SymbolTable::SymbolTable(lexer::TOKEN returnType) : returnType(returnType) {}

visitor::SymbolTable::SymbolTable(lexer::TOKEN returnType, std::vector<ast::ASTFormalParam *> functionsParams)
        : returnType(returnType) {
    this->functionsParams = new std::vector<ast::ASTFormalParam *>(functionsParams);
}

visitor::SymbolTable::~SymbolTable() {
    delete functionsParams;
}
