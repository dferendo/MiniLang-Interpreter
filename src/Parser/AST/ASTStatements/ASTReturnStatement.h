//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTRETURNSTATEMENT_H
#define COMPILERTHEORY_ASTRETURNSTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"

namespace parser{
    namespace ast {

        class ASTReturnStatement : public ASTStatementNode {

        public:
            ast::ASTExprNode * exprNode;

            ASTReturnStatement(ASTExprNode *exprNode);

            void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTRETURNSTATEMENT_H
