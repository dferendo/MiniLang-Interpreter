//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTUNARY_H
#define COMPILERTHEORY_ASTUNARY_H

#include "ASTExprNode.h"
#include "../Visitors/Visitor.h"
#include <iostream>

namespace parser {
    namespace ast {

        class ASTUnary : public ASTExprNode {
        public:
            std::string unary;

            ASTExprNode * unaryExpression;

            ASTUnary(const std::string &unary, ASTExprNode *unaryExpression);

            void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTUNARY_H
