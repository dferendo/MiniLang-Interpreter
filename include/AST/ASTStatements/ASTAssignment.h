//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTASSIGNMENT_H
#define COMPILERTHEORY_ASTASSIGNMENT_H

#include "ASTStatementNode.h"
#include "../ASTExpression/ASTExprNode.h"

namespace ast {

    class ASTAssignment : public ASTStatementNode {
    public:
        std::string identifier;

        ASTExprNode * exprNode;

        ASTAssignment(const std::string &identifier, ASTExprNode *exprNode);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTAssignment();
    };
}

#endif //COMPILERTHEORY_ASTASSIGNMENT_H
