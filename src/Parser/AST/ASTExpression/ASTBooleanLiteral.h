//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_BOOLEANLITERAL_H
#define COMPILERTHEORY_BOOLEANLITERAL_H

#include "ASTLiteralNode.h"
#include "../Visitors/Visitor.h"

namespace parser {
    namespace ast {
        class ASTBooleanLiteral : public ASTLiteralNode {
        public:
            bool literalValue;

            ASTBooleanLiteral(bool literalValue);

            void accept(Visitor *v) override;

            virtual ~ASTBooleanLiteral();
        };
    }
}

#endif //COMPILERTHEORY_BOOLEANLITERAL_H
