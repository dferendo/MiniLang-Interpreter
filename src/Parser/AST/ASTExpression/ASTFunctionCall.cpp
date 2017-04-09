//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTExpression/ASTFunctionCall.h"
#include "../../../../include/Parser/AST/Visitors/Visitor.h"

parser::ast::ASTFunctionCall::ASTFunctionCall(const std::string &identifier,
                                              const std::vector<parser::ast::ASTExprNode *> &actualParams) : identifier(
        identifier), actualParams(actualParams) {}

void parser::ast::ASTFunctionCall::accept(Visitor *v) {
    v->visit(this);
}

parser::ast::ASTFunctionCall::~ASTFunctionCall() {
    for (auto const & param : actualParams) {
        delete param;
    }
}
