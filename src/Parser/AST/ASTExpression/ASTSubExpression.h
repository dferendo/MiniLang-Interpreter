//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTSUBEXPRESSION_H
#define COMPILERTHEORY_ASTSUBEXPRESSION_H

#include "ASTExprNode.h"
#include "../Visitors/Visitor.h"

namespace parser {
    namespace ast {

        class ASTSubExpression : public ASTExprNode {
        public:
            ASTExprNode * subExpression;

            ASTSubExpression(ASTExprNode *subExpression);

            void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTSUBEXPRESSION_H
