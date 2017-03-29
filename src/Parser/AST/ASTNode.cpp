//
// Created by dylan on 20/03/2017.
//

#include "ASTNode.h"

namespace parser {
    namespace ast {

        void ASTNode::addStatement(ASTStatementNode * statement) {
            statements.push_back(statement);
        }

        void ASTNode::accept(Visitor *v) {
            v->visit(this);
        }
    }
}
