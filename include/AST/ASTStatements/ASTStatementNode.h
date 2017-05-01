//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTSTATEMENTNODE_H
#define COMPILERTHEORY_ASTSTATEMENTNODE_H

#include "../../Visitors/Visitor.h"
#include <iostream>
#include "vector"

namespace ast {
    /**
     *
     */
    class ASTStatementNode {
    public:
        virtual void accept(visitor::Visitor *v) = 0;

        virtual ~ASTStatementNode() {};
    };
}


#endif //COMPILERTHEORY_ASTSTATEMENTNODE_H
