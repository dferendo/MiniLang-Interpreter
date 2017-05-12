//
// Created by dylan on 12/05/2017.
//

#ifndef COMPILERTHEORY_ASTEXPRSTATEMENT_H
#define COMPILERTHEORY_ASTEXPRSTATEMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"

namespace ast {

    class ASTExprStatement : public ASTStatementNode {
    public:
        ASTExprNode * exprNode;

        ASTExprStatement(ASTExprNode *exprNode);

        void accept(visitor::Visitor *v);

        ~ASTExprStatement();

    };

}
#endif //COMPILERTHEORY_ASTEXPRSTATEMENT_H
