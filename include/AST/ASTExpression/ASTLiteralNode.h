//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTLITERALNODE_H
#define COMPILERTHEORY_ASTLITERALNODE_H

#include "ASTExprNode.h"
#include "../../Visitors/Visitor.h"

namespace ast {

    /**
     * Used for cleaner class divided. It is the parent of Integer, Boolean, Real and String literals.
     */
    class ASTLiteralNode : public ASTExprNode {
    public:
        virtual void accept(visitor::Visitor *v) = 0;

        virtual ~ASTLiteralNode() {};
    };
}

#endif //COMPILERTHEORY_ASTLITERALNODE_H
