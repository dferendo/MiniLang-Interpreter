//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTNODE_H
#define COMPILERTHEORY_ASTNODE_H

#include <iostream>
#include <vector>
#include "../Visitors/Visitor.h"

namespace ast {

    class ASTStatementNode;

    /**
     * A program can contain 0 or many {@link ASTStatementsNode} as children.
     */
    class ASTNode {
    public:
        /**
         * The vector holds all the statements found in <Program>
         */
        std::vector<ASTStatementNode *> statements;

        ASTNode();

        /**
         * Deallocate the statements found in the vector.
         */
        virtual ~ASTNode();

        /**
         * Visitor Class.
         *
         * @param v Visitor.
         */
        virtual void accept(visitor::Visitor * v);

        void addStatements(std::vector<ASTStatementNode *> statements);

        void clearStatements();
    };
}

#endif //COMPILERTHEORY_ASTNODE_H