//
// Created by dylan on 29/03/2017.
//


#include "../../../include/AST/ASTExpression/ASTFunctionCall.h"

ast::ASTFunctionCall::ASTFunctionCall(const std::string &identifier,
                                      const std::vector<ast::ASTExprNode *> &actualParams) : identifier(
        identifier), actualParams(actualParams) {}

void ast::ASTFunctionCall::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTFunctionCall::~ASTFunctionCall() {
    for (auto const & param : actualParams) {
        delete param;
    }
}
