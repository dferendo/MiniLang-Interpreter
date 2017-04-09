//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTIDENTIFIER_H
#define COMPILERTHEORY_ASTIDENTIFIER_H

#include "ASTExprNode.h"
#include "../Visitors/Visitor.h"
#include <iostream>

namespace parser {
    namespace ast {

        class ASTIdentifier : public ASTExprNode {
        public:
            std::string identifier;

            ASTIdentifier(const std::string &identifier);

            void accept(Visitor *v) override;

            virtual ~ASTIdentifier();
        };
    }
}

#endif //COMPILERTHEORY_ASTIDENTIFIER_H
