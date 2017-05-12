//
// Created by dylan on 28/03/2017.
//

#include "../../include/Visitors/XMLConverterVisitor.h"
#include "../../include/AST/ASTStatements/ASTVariableDeclaration.h"
#include "../../include/AST/ASTStatements/ASTAssignment.h"
#include "../../include/AST/ASTStatements/ASTBlock.h"
#include "../../include/AST/ASTStatements/ASTIfStatement.h"
#include "../../include/AST/ASTStatements/ASTWhileStatement.h"
#include "../../include/AST/ASTStatements/ASTFormalParam.h"
#include "../../include/AST/ASTStatements/ASTFunctionDeclaration.h"
#include "../../include/AST/ASTExpression/ASTBooleanLiteral.h"
#include "../../include/AST/ASTExpression/ASTIntegerLiteral.h"
#include "../../include/AST/ASTExpression/ASTRealLiteral.h"
#include "../../include/AST/ASTExpression/ASTStringLiteral.h"
#include "../../include/AST/ASTStatements/ASTPrintStatement.h"
#include "../../include/AST/ASTStatements/ASTReturnStatement.h"
#include "../../include/AST/ASTExpression/ASTIdentifier.h"
#include "../../include/AST/ASTExpression/ASTFunctionCall.h"
#include "../../include/AST/ASTExpression/ASTUnary.h"
#include "../../include/AST/ASTExpression/ASTSubExpression.h"
#include "../../include/AST/ASTExpression/ASTBinaryExprNode.h"
#include "../../include/AST/ASTStatements/ASTExprStatement.h"

using namespace std;
using namespace ast;

namespace visitor {

    XMLConverterVisitor::XMLConverterVisitor() {}

    void XMLConverterVisitor::visit(ASTNode *node) {
        // Set default to the main node.
        currentIndent = 0;
        outputXML.open("program.xml");
        // Start parsing main node.
        string word = getStartingPositionAfterIndent();
        outputXML << word << "<Program>" << endl;

        currentIndent++;
        for (auto const &childNode : node->statements) {
            childNode->accept(this);
        }
        currentIndent--;
        outputXML << word << "</Program>" << endl;
        outputXML.close();
    }

    void XMLConverterVisitor::visit(ASTVariableDeclaration *node) {
        string word = getStartingPositionAfterIndent();
        outputXML << word << "<VariableDeclaration type=\"" << lexer::TOKEN_STRING[node->tokenType] << "\">" << endl;
        currentIndent++;
        word = getStartingPositionAfterIndent();
        outputXML << word << "<Identifier>" << node->identifier << "</Identifier>" << endl;
        printExpression(node->expression);
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
        printExpression(node->exprNode);
        currentIndent--;
        word = getStartingPositionAfterIndent();
        outputXML << word << "</Assignment>" << endl;
    }

    void XMLConverterVisitor::visit(ASTPrintStatement *node) {
        string word = getStartingPositionAfterIndent();
        outputXML << word << "<PrintStatement>" << endl;
        currentIndent++;
        printExpression(node->exprNode);
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
        printExpression(node->exprNode);
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
        printExpression(node->exprNode);
        currentIndent++;
        node->astBlock->accept(this);
        currentIndent--;
        outputXML << word << "</WhileStatement>" << endl;
    }

    void XMLConverterVisitor::visit(ASTReturnStatement *node) {
        string word = getStartingPositionAfterIndent();
        outputXML << word << "<ReturnStatement>" << endl;
        currentIndent++;
        printExpression(node->exprNode);
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

    void XMLConverterVisitor::visit(ast::ASTExprStatement *node) {
        string word = getStartingPositionAfterIndent();

        outputXML << word << "<Identifier>" << endl;
        currentIndent++;
        node->exprNode->accept(this);
        currentIndent--;
        outputXML << word << "</Identifier>" << endl;
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
        outputXML << word << "<BinaryExprNode op=\"" << printOperator(node->operation) <<"\">" << endl;
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

    void XMLConverterVisitor::printExpression(ASTExprNode *node) {
        string word = getStartingPositionAfterIndent();
        ASTBinaryExprNode * temp = dynamic_cast<ASTBinaryExprNode *> (node);

        if (temp) {
            node->accept(this);
        } else {
            outputXML << word << "<Expression>" << endl;
            currentIndent++;
            node->accept(this);
            currentIndent--;
            outputXML << word << "</Expression>" << endl;
        }
    }

    std::string XMLConverterVisitor::printOperator(std::string currentOperator) {
        if (currentOperator.compare(">") == 0) {
            return "&gt;";
        } else if (currentOperator.compare("<") == 0) {
            return "&lt;";
        } else if (currentOperator.compare(">=") == 0) {
            return "&gt;=";
        } else if (currentOperator.compare("<=") == 0) {
            return "&lt;=";
        } else {
            return currentOperator;
        }
    }

}
