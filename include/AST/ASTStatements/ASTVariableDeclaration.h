//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_VARIABLEDECLARATION_H
#define COMPILERTHEORY_VARIABLEDECLARATION_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"
#include "../../Lexer/Token.h"

namespace ast {

    class ASTVariableDeclaration : public ASTStatementNode {
    public:
        std::string identifier;
        lexer::TOKEN tokenType;
        ASTExprNode * expression;

        ASTVariableDeclaration(const std::string &identifier, lexer::TOKEN tokenType, ASTExprNode *expression);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTVariableDeclaration();
    };
}

#endif //COMPILERTHEORY_VARIABLEDECLARATION_H
