//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_VISITOR_H
#define COMPILERTHEORY_VISITOR_H

namespace parser {
    namespace ast {
        class ASTNode;
        class ASTStatementNode;

        class Visitor {
        public:
            virtual void visit(ASTNode * node) = 0;
            virtual void visit(ASTStatementNode * node) = 0;
        };
    }
}
#endif //COMPILERTHEORY_VISITOR_H
