//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_VISITOR_H
#define COMPILERTHEORY_VISITOR_H

namespace parser {
    namespace ast {
        class ASTNode;
        class ASTVariableDeclaration;

        class Visitor {
        public:
            virtual void visit(ASTNode * node) = 0;
            virtual void visit(ASTVariableDeclaration * node) = 0;
        };
    }
}
#endif //COMPILERTHEORY_VISITOR_H
