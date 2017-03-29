//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTASSIGNMENT_H
#define COMPILERTHEORY_ASTASSIGNMENT_H

#include "ASTStatementNode.h"

namespace parser {
    namespace ast {
        class ASTAssignment : public ast::ASTStatementNode{
        public:
            void accept(Visitor *v) override;
        };
    }
}

#endif //COMPILERTHEORY_ASTASSIGNMENT_H
