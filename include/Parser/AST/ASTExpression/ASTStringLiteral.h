//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTSTRINGLITERAL_H
#define COMPILERTHEORY_ASTSTRINGLITERAL_H

#include <iostream>
#include "ASTLiteralNode.h"
#include "../Visitors/Visitor.h"

namespace parser {
    namespace ast {

        class ASTStringLiteral : public ASTLiteralNode {
        public:
            std::string literalString;

            ASTStringLiteral(const std::string &literalString);

            void accept(Visitor *v) override;

            virtual ~ASTStringLiteral();
        };
    }
}

#endif //COMPILERTHEORY_ASTSTRINGLITERAL_H
