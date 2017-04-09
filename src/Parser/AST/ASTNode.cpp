//
// Created by dylan on 20/03/2017.
//

#include "ASTNode.h"
#include "ASTStatements/ASTStatementNode.h"

namespace parser {
    namespace ast {

        ASTNode::ASTNode(const std::vector<ASTStatementNode *> &statements) : statements(statements) {}

        void ASTNode::accept(Visitor *v) {
            v->visit(this);
        }

        ASTNode::~ASTNode() {
            for (auto const &statement : statements) {
                delete statement;
            }
        }
    }
}
