//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTSUBEXPRESSION_H
#define COMPILERTHEORY_ASTSUBEXPRESSION_H

#include "ASTExprNode.h"
#include "../../Visitors/Visitor.h"

namespace ast {

    class ASTSubExpression : public ASTExprNode {
    public:
        ASTExprNode * subExpression;

        ASTSubExpression(ASTExprNode *subExpression);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTSubExpression();
    };

}

#endif //COMPILERTHEORY_ASTSUBEXPRESSION_H
