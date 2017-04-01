//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTEXPRNODE_H
#define COMPILERTHEORY_ASTEXPRNODE_H


#include "../Visitors/Visitor.h"
#include <iostream>

namespace parser {
    namespace ast {

        class ASTExprNode {
        public:
            virtual void accept(Visitor *v) = 0;
        };

    }
}


#endif //COMPILERTHEORY_ASTEXPRNODE_H
