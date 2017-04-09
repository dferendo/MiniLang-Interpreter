//
// Created by dylan on 31/03/2017.
//

#ifndef COMPILERTHEORY_ASTFORMALPARAMS_H
#define COMPILERTHEORY_ASTFORMALPARAMS_H

#include "../ASTNode.h"
#include "../../../Lexer/Token.h"

namespace parser {
    namespace ast {

        class ASTFormalParam {
        public:
            std::string identifier;

            lexer::TOKEN tokenType;

            ASTFormalParam(const std::string &identifier, lexer::TOKEN tokenType);

            void accept(Visitor *v);

            virtual ~ASTFormalParam();
        };

    }
}

#endif //COMPILERTHEORY_ASTFORMALPARAMS_H
