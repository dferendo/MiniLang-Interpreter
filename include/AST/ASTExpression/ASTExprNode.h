//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTEXPRNODE_H
#define COMPILERTHEORY_ASTEXPRNODE_H


#include "../../Visitors/Visitor.h"
#include "../ASTStatements/ASTStatementNode.h"
#include <iostream>

namespace ast {

    class ASTExprNode {
    public:
        virtual void accept(visitor::Visitor *v) = 0;

        virtual ~ASTExprNode() {};
    };

}


#endif //COMPILERTHEORY_ASTEXPRNODE_H
