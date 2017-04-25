//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTBINARYEXPRNODE_H
#define COMPILERTHEORY_ASTBINARYEXPRNODE_H

#include "ASTExprNode.h"

namespace ast {

    /**
     * ASTBinaryExprNode holds 2 expressions which are connected with an operator.
     */
    class ASTBinaryExprNode : public ASTExprNode {
    public:
        std::string operation;

        ASTExprNode * LHS = nullptr;

        ASTExprNode * RHS = nullptr;

        void setRHS(ASTExprNode *RHS);

        ASTBinaryExprNode(const std::string &operation, ASTExprNode *LHS, ASTExprNode *RHS);

        virtual void accept(visitor::Visitor *v) override;

        virtual ~ASTBinaryExprNode();
    };
}

#endif //COMPILERTHEORY_ASTBINARYEXPRNODE_H
