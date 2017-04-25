//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_BOOLEANLITERAL_H
#define COMPILERTHEORY_BOOLEANLITERAL_H

#include "ASTLiteralNode.h"
#include "../../Visitors/Visitor.h"

namespace ast {

    /**
     * Holds true or false literal.
     */
    class ASTBooleanLiteral : public ASTLiteralNode {
    public:
        bool literalValue;

        ASTBooleanLiteral(bool literalValue);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTBooleanLiteral();
    };
}

#endif //COMPILERTHEORY_BOOLEANLITERAL_H
