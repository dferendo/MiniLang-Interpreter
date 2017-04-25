//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTINTEGERLITERAL_H
#define COMPILERTHEORY_ASTINTEGERLITERAL_H

#include "ASTLiteralNode.h"
#include "../../Visitors/Visitor.h"

namespace ast {

    /**
     * Holds integers literals.
     */
    class ASTIntegerLiteral : public ASTLiteralNode {
    public:
        int literalValue;

        ASTIntegerLiteral(int literalValue);

        void accept(visitor::Visitor *v) override;

        virtual ~ASTIntegerLiteral();
    };
}

#endif //COMPILERTHEORY_ASTINTEGERLITERAL_H
