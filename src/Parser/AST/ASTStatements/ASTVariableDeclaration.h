//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_VARIABLEDECLARATION_H
#define COMPILERTHEORY_VARIABLEDECLARATION_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"
#include "../../../Lexer/Token.h"

namespace parser {
    namespace ast {

        class ASTVariableDeclaration : public ast::ASTStatementNode {
        private:
            std::string identifier;
            lexer::TOKEN tokenType;
            ASTExprNode expression;
        public:
            ASTVariableDeclaration(const std::string &identifier, lexer::TOKEN tokenType,
                                   const ASTExprNode &expression);
            void accept(Visitor *v) override;
        };
    }
}

#endif //COMPILERTHEORY_VARIABLEDECLARATION_H
