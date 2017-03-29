//
// Created by dylan on 29/03/2017.
//

#ifndef COMPILERTHEORY_ASTFUNCTIONCALL_H
#define COMPILERTHEORY_ASTFUNCTIONCALL_H

#include "ASTExprNode.h"
#include "../Visitors/Visitor.h"
#include <iostream>
#include <vector>

namespace parser {
    namespace ast {

        class ASTFunctionCall : public ASTExprNode {
        public:
            std::string identifier;

            std::vector<ASTExprNode * > actualParams;

            ASTFunctionCall(const std::string &identifier, const std::vector<ASTExprNode *> &actualParams);

            void accept(Visitor *v) override;
        };

    }
}

#endif //COMPILERTHEORY_ASTFUNCTIONCALL_H
