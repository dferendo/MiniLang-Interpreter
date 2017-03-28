//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_XMLCONVERTORVISITOR_H
#define COMPILERTHEORY_XMLCONVERTORVISITOR_H

#include "Visitor.h"
#include <iostream>
#include <fstream>

namespace parser {
    namespace ast {
        
        class XMLConverterVisitor : public Visitor {
        private:
            const std::string TAB_INDENT = "\t";

            int currentIndent = 0;

            std::ofstream outputXML;

            std::string getStartingPositionAfterIndent();
        public:
            XMLConverterVisitor();

            virtual void visit(ASTNode *node) override;

            virtual void visit(ASTStatementNode *node) override;
        };
    }
}


#endif //COMPILERTHEORY_XMLCONVERTORVISITOR_H
