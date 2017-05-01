//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTIFSTATEMENT_H
#define COMPILERTHEORY_ASTIFSTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"
#include "ASTBlock.h"

namespace ast {

    class ASTIfStatement : public ASTStatementNode {
    public:
        ASTExprNode * exprNode;

        ASTBlock * astBlockForIF;

        /**
         * Optional else block.
         */
        ASTBlock * astBlockForElse = nullptr;

        ASTIfStatement(ASTExprNode *exprNode, ASTBlock *astBlockForIF);

        ASTIfStatement(ASTExprNode *exprNode, ASTBlock *astBlockForIF, ASTBlock *astBlockForElse);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTIfStatement();
    };

}

#endif //COMPILERTHEORY_ASTIFSTATEMENT_H
