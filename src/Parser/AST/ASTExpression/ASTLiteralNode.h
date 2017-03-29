//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTLITERALNODE_H
#define COMPILERTHEORY_ASTLITERALNODE_H

#include "ASTExprNode.h"
#include "../Visitors/Visitor.h"

namespace parser {
    namespace ast {
        class ASTLiteralNode : public ASTExprNode {
        public:
            virtual void accept(Visitor *v) = 0;
        };
    }
}

#endif //COMPILERTHEORY_ASTLITERALNODE_H
