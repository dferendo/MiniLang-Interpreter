//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTFUNCTIONDECLARATION_H
#define COMPILERTHEORY_ASTFUNCTIONDECLARATION_H

#include "ASTStatementNode.h"
#include "ASTFormalParam.h"

namespace parser {
    namespace ast {

        class ASTFunctionDeclaration : public ASTStatementNode {

        public:
            std::string identifier;

            std::vector<ASTFormalParam *> formalParams;

            lexer::TOKEN tokenType;

            ASTBlock * astBlock;

            ASTFunctionDeclaration(const std::string &identifier, const std::vector<ASTFormalParam *> &formalParams,
                                   lexer::TOKEN tokenType, ASTBlock *astBlock);

            void accept(Visitor *v) override;

            virtual ~ASTFunctionDeclaration();
        };

    }
}

#endif //COMPILERTHEORY_ASTFUNCTIONDECLARATION_H