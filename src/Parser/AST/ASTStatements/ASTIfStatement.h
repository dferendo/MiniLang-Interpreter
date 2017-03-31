//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTIFSTATEMENT_H
#define COMPILERTHEORY_ASTIFSTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"
#include "ASTBlock.h"
namespace parser {
    namespace ast {

        class ASTIfStatement : public ASTStatementNode {
        public:
            ASTExprNode * exprNode;

            ASTBlock * astBlockForIF = nullptr;

            ASTBlock * astBlockForElse = nullptr;

            ASTIfStatement(ASTExprNode *exprNode, ASTBlock *astBlockForIF);

            ASTIfStatement(ASTExprNode *exprNode, ASTBlock *astBlockForIF, ASTBlock *astBlockForElse);

            void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTIFSTATEMENT_H
