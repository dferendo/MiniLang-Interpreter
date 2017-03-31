//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTWHILESTATEMENT_H
#define COMPILERTHEORY_ASTWHILESTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"
#include "ASTBlock.h"

namespace parser {
    namespace ast {

        class ASTWhileStatement : public ASTStatementNode {
        public:
            ASTExprNode * exprNode;

            ASTBlock * astBlock;

            ASTWhileStatement(ASTExprNode *exprNode, ASTBlock *astBlock);

            void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTWHILESTATEMENT_H
