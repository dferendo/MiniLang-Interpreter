//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTRETURNSTATEMENT_H
#define COMPILERTHEORY_ASTRETURNSTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"

namespace ast {

    class ASTReturnStatement : public ASTStatementNode {

    public:
        ast::ASTExprNode * exprNode;

        ASTReturnStatement(ASTExprNode *exprNode);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTReturnStatement();
    };

}

#endif //COMPILERTHEORY_ASTRETURNSTATEMENT_H
