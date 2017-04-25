//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTBLOCK_H
#define COMPILERTHEORY_ASTBLOCK_H

#include "ASTStatementNode.h"

namespace parser {
    namespace ast {

        class ASTBlock : public ASTStatementNode {
        public:
            std::vector<ASTStatementNode *> statements;

            void addStatement(ASTStatementNode * statements);

            void accept(Visitor *v) override;

            virtual ~ASTBlock();
        };

    }
}

#endif //COMPILERTHEORY_ASTBLOCK_H
