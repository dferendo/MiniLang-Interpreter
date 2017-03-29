//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTSTATEMENTNODE_H
#define COMPILERTHEORY_ASTSTATEMENTNODE_H

#include "../ASTNode.h"

namespace parser {
    namespace ast {
        /**
         *
         */
        class ASTStatementNode : public ASTNode {
        public:
            virtual void accept(Visitor *v) = 0;
        };
    }
}


#endif //COMPILERTHEORY_ASTSTATEMENTNODE_H
