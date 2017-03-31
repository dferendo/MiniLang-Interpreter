//
// Created by dylan on 28/03/2017.
//

#include "XMLConverterVisitor.h"
#include "../ASTNode.h"
#include "../ASTStatements/ASTStatementNode.h"
#include "../ASTStatements/ASTVariableDeclaration.h"
#include "../../../Lexer/Token.h"

using namespace std;

namespace parser {
    namespace ast{

        XMLConverterVisitor::XMLConverterVisitor() : currentIndent(0) {
            outputXML.open("program.xml");
        }

        void XMLConverterVisitor::visit(ASTNode *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Program>" << endl;

            currentIndent++;
            for (auto const &childNode : node->statements) {
                childNode->accept(this);
            }
            currentIndent--;
            outputXML << word << "</Program>" << endl;
        }

        void XMLConverterVisitor::visit(ASTVariableDeclaration *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<VariableDeclaration type=\"" << lexer::TOKEN_STRING[node->tokenType] << "\">" << endl;
            currentIndent++;
            word = getStartingPositionAfterIndent();
            outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
            // TODO:
//            node->expression->accept(this);
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</VariableDeclaration>" << endl;
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
