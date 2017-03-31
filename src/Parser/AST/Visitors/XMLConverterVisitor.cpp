//
// Created by dylan on 28/03/2017.
//

#include "XMLConverterVisitor.h"
#include "../ASTNode.h"
#include "../ASTStatements/ASTStatementNode.h"
#include "../ASTStatements/ASTVariableDeclaration.h"
#include "../ASTStatements/ASTAssignment.h"
#include "../ASTStatements/ASTBlock.h"
#include "../ASTStatements/ASTIfStatement.h"
#include "../ASTStatements/ASTWhileStatement.h"

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

        void XMLConverterVisitor::visit(ASTAssignment *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Assignment>" << endl;
            currentIndent++;
            word = getStartingPositionAfterIndent();
            outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
            // TODO:
//            node->expression->accept(this);
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</Assignment>" << endl;
        }

        void XMLConverterVisitor::visit(ASTPrintStatement *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<PrintStatement>" << endl;
            currentIndent++;
            // TODO:
//            node->expression->accept(this);
            currentIndent--;
            outputXML << word << "</PrintStatement>" << endl;
        }

        void XMLConverterVisitor::visit(ASTBlock *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Block>" << endl;

            currentIndent++;
            for (auto const &childNode : node->statements) {
                childNode->accept(this);
            }
            currentIndent--;
            outputXML << word << "</Block>" << endl;
        }

        void XMLConverterVisitor::visit(ASTIfStatement *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<IfStatement>" << endl;
            // TODO:
//            node->expression->accept(this);
            currentIndent++;
            node->astBlockForIF->accept(this);

            // Else is optional.
            if (node->astBlockForElse != nullptr) {
                node->astBlockForElse->accept(this);
            }
            currentIndent--;
            outputXML << word << "</IfStatement>" << endl;
        }

        void XMLConverterVisitor::visit(ASTWhileStatement *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<WhileStatement>" << endl;
            // TODO:
//            node->expression->accept(this);
            currentIndent++;
            node->astBlock->accept(this);
            currentIndent--;
            outputXML << word << "</WhileStatement>" << endl;
        }

        void XMLConverterVisitor::visit(ASTReturnStatement *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<ReturnStatement>" << endl;
            currentIndent++;
            // TODO:
//            node->expression->accept(this);
            currentIndent--;
            outputXML << word << "</ReturnStatement>" << endl;
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
