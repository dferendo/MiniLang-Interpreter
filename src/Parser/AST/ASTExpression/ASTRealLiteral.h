//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTREALLITERAL_H
#define COMPILERTHEORY_ASTREALLITERAL_H

#include "ASTLiteralNode.h"
#include "../Visitors/Visitor.h"

namespace parser {
    namespace ast{

        class ASTRealLiteral : public ASTLiteralNode {
        public:
            double realValue;

            ASTRealLiteral(double realValue);

            void accept(Visitor *v) override;

            virtual ~ASTRealLiteral();
        };

    }
}

#endif //COMPILERTHEORY_ASTREALLITERAL_H
