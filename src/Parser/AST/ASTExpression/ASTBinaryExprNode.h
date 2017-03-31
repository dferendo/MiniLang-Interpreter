//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTBINARYEXPRNODE_H
#define COMPILERTHEORY_ASTBINARYEXPRNODE_H

#include "ASTExprNode.h"

namespace parser {
    namespace ast {

        class ASTBinaryExprNode : public ASTExprNode {
        public:
            std::string operation;

            ASTExprNode * LHS = nullptr;

            ASTExprNode * RHS = nullptr;

            ASTBinaryExprNode(const std::string &operation, ASTExprNode *LHS, ASTExprNode *RHS);

            virtual void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTBINARYEXPRNODE_H
