//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTEXPRNODE_H
#define COMPILERTHEORY_ASTEXPRNODE_H


#include "../ASTNode.h"

namespace parser {
    namespace ast {

        class ASTExprNode : public ASTNode {
        public:
            virtual void accept(Visitor *v) override;
        };

    }
}


#endif //COMPILERTHEORY_ASTEXPRNODE_H
