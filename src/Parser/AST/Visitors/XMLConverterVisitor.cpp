//
// Created by dylan on 28/03/2017.
//

#include "XMLConverterVisitor.h"
#include "../ASTNode.h"
#include "../ASTStatements/ASTVariableDeclaration.h"
#include "../ASTStatements/ASTAssignment.h"
#include "../ASTStatements/ASTBlock.h"
#include "../ASTStatements/ASTIfStatement.h"
#include "../ASTStatements/ASTWhileStatement.h"
#include "../ASTStatements/ASTFormalParam.h"
#include "../ASTStatements/ASTFunctionDeclaration.h"
#include "../ASTExpression/ASTBooleanLiteral.h"
#include "../ASTExpression/ASTIntegerLiteral.h"
#include "../ASTExpression/ASTRealLiteral.h"
#include "../ASTExpression/ASTStringLiteral.h"
#include "../ASTStatements/ASTPrintStatement.h"
#include "../ASTStatements/ASTReturnStatement.h"
#include "../ASTExpression/ASTIdentifier.h"
#include "../ASTExpression/ASTFunctionCall.h"
#include "../ASTExpression/ASTUnary.h"
#include "../ASTExpression/ASTSubExpression.h"
#include "../ASTExpression/ASTBinaryExprNode.h"

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
            node->expression->accept(this);
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
            node->exprNode->accept(this);
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</Assignment>" << endl;
        }

        void XMLConverterVisitor::visit(ASTPrintStatement *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<PrintStatement>" << endl;
            currentIndent++;
            node->exprNode->accept(this);
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
            node->exprNode->accept(this);
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
            node->exprNode->accept(this);
            currentIndent++;
            node->astBlock->accept(this);
            currentIndent--;
            outputXML << word << "</WhileStatement>" << endl;
        }

        void XMLConverterVisitor::visit(ASTReturnStatement *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<ReturnStatement>" << endl;
            currentIndent++;
            node->exprNode->accept(this);
            currentIndent--;
            outputXML << word << "</ReturnStatement>" << endl;
        }

        void XMLConverterVisitor::visit(ASTFormalParam *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<FormalParam type=\"" << lexer::TOKEN_STRING[node->tokenType] << "\">" << endl;
            currentIndent++;
            word = getStartingPositionAfterIndent();
            outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</FormalParam>" << endl;
        }

        void XMLConverterVisitor::visit(ASTFunctionDeclaration *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<FunctionDeclaration type=\"" << lexer::TOKEN_STRING[node->tokenType] << "\">" <<  endl;
            currentIndent++;
            word = getStartingPositionAfterIndent();
            outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
            outputXML << word << "<FormalParams>" << endl;
            currentIndent++;
            for (auto const &formalParam : node->formalParams) {
                formalParam->accept(this);
            }
            currentIndent--;
            outputXML << word << "</FormalParams>" << endl;
            node->astBlock->accept(this);
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</FunctionDeclaration>" << endl;
        }

        void XMLConverterVisitor::visit(ASTBooleanLiteral *node) {
            string word = getStartingPositionAfterIndent();
            if (node->literalValue) {
                outputXML << word << "<Boolean>true</Boolean>" << endl;
            } else {
                outputXML << word << "<Boolean>false</Boolean>" << endl;
            }
        }

        void XMLConverterVisitor::visit(ASTIntegerLiteral *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Integer>" << node->literalValue << "</Integer>" << endl;
        }

        void XMLConverterVisitor::visit(ASTRealLiteral *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Real>" << node->realValue << "</Real>" << endl;
        }

        void XMLConverterVisitor::visit(ASTStringLiteral *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<String>" << node->literalString << "</String>" << endl;
        }

        void XMLConverterVisitor::visit(ASTIdentifier *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
        }

        void XMLConverterVisitor::visit(ASTFunctionCall *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<FunctionCall>" << endl;
            currentIndent++;
            word = getStartingPositionAfterIndent();
            outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
            outputXML << word << "<ActualParams>" << endl;
            currentIndent++;
            for (auto const &param : node->actualParams) {
                param->accept(this);
            }
            currentIndent--;
            outputXML << word << "</ActualParams>" << endl;
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</FunctionCall>" << endl;
        }

        void XMLConverterVisitor::visit(ASTSubExpression *node) {
            node->subExpression->accept(this);
        }

        void XMLConverterVisitor::visit(ASTUnary *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<Unary op=\"" << node->unary <<"\">" << endl;
            currentIndent++;
            node->unaryExpression->accept(this);
            currentIndent--;
            word = getStartingPositionAfterIndent();
            outputXML << word << "</Unary>" << endl;
        }

        void XMLConverterVisitor::visit(ASTBinaryExprNode *node) {
            string word = getStartingPositionAfterIndent();
            outputXML << word << "<BinaryExprNode op=\"" << node->operation <<"\">" << endl;
            currentIndent++;
            node->LHS->accept(this);
            node->RHS->accept(this);
            currentIndent--;
            outputXML << word << "</BinaryExprNode>" << endl;
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
