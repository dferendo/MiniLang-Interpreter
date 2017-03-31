//
// Created by dylan on 29/03/2017.
//

#include "ASTFunctionDeclaration.h"

void
parser::ast::ASTFunctionDeclaration::setFormalParams(ASTFormalParam * &formalParam) {
    this->formalParams.push_back(formalParam);
}

parser::ast::ASTFunctionDeclaration::ASTFunctionDeclaration(const std::string &identifier,
                                                            const std::vector<parser::ast::ASTFormalParam *> &formalParams,
                                                            lexer::TOKEN tokenType, parser::ast::ASTBlock *astBlock)
        : identifier(identifier), formalParams(formalParams), tokenType(tokenType), astBlock(astBlock) {}

void parser::ast::ASTFunctionDeclaration::accept(parser::ast::Visitor *v) {
    v->visit(this);
}
