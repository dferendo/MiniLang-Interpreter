//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTWHILESTATEMENT_H
#define COMPILERTHEORY_ASTWHILESTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"
#include "ASTBlock.h"

namespace ast {

    class ASTWhileStatement : public ASTStatementNode {
    public:
        ASTExprNode * exprNode;

        ASTBlock * astBlock;

        ASTWhileStatement(ASTExprNode *exprNode, ASTBlock *astBlock);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTWhileStatement();
    };

}

#endif //COMPILERTHEORY_ASTWHILESTATEMENT_H
