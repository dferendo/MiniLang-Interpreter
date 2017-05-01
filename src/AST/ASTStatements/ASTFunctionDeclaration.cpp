//
// Created by dylan on 29/03/2017.
//

#include "../../../include/AST/ASTStatements/ASTFunctionDeclaration.h"
#include "../../../include/AST/ASTStatements/ASTBlock.h"

ast::ASTFunctionDeclaration::ASTFunctionDeclaration(const std::string &identifier,
                                                            const std::vector<ast::ASTFormalParam *> &formalParams,
                                                            lexer::TOKEN tokenType, ast::ASTBlock *astBlock)
        : identifier(identifier), formalParams(formalParams), tokenType(tokenType), astBlock(astBlock) {}

void ast::ASTFunctionDeclaration::accept(visitor::Visitor *v) {
    v->visit(this);
}

ast::ASTFunctionDeclaration::~ASTFunctionDeclaration() {
    delete astBlock;
    for (auto const &param : formalParams) {
        delete param;
    }
}
