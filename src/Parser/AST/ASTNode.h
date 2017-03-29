//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_ASTNODE_H
#define COMPILERTHEORY_ASTNODE_H

#include <iostream>
#include <vector>
#include "Visitor.h"

namespace parser {
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

            void addStatement(ASTStatementNode * statements);

            virtual void accept(Visitor * v);
        };
    }
}

#endif //COMPILERTHEORY_ASTNODE_H