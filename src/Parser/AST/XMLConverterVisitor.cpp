//
// Created by dylan on 28/03/2017.
//

#include "XMLConverterVisitor.h"
#include "ASTNode.h"
#include "ASTStatementNode.h"

using namespace std;

namespace parser {
    namespace ast{

        XMLConverterVisitor::XMLConverterVisitor() : currentIndent(0) {
            outputXML.open("program.xml");
        }

        void XMLConverterVisitor::visit(ASTNode *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << "<Program>" << endl;

            currentIndent++;
            for (auto const &childNode : node->statements) {
                childNode->accept(this);
            }
            currentIndent--;
            outputXML << "</Program>" << endl;
        }

        void XMLConverterVisitor::visit(ASTStatementNode *node) {

        }

        string XMLConverterVisitor::getStartingPositionAfterIndent() {
            string tempTab = "";

            for (int currentIndex = 0; currentIndex < currentIndent; currentIndex++) {
                tempTab.append(TAB_INDENT);
            }
            return tempTab;
        }

    }
}
