//
// Created by dylan on 29/03/2017.
//

#include "../../../../include/Parser/AST/ASTStatements/ASTFunctionDeclaration.h"
#include "../../../../include/Parser/AST/ASTStatements/ASTBlock.h"

parser::ast::ASTFunctionDeclaration::ASTFunctionDeclaration(const std::string &identifier,
                                                            const std::vector<parser::ast::ASTFormalParam *> &formalParams,
                                                            lexer::TOKEN tokenType, parser::ast::ASTBlock *astBlock)
        : identifier(identifier), formalParams(formalParams), tokenType(tokenType), astBlock(astBlock) {}

void parser::ast::ASTFunctionDeclaration::accept(parser::ast::Visitor *v) {
    v->visit(this);
}

parser::ast::ASTFunctionDeclaration::~ASTFunctionDeclaration() {
    delete astBlock;
    for (auto const &param : formalParams) {
        delete param;
    }
}
