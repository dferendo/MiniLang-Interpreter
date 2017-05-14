//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_XMLCONVERTORVISITOR_H
#define COMPILERTHEORY_XMLCONVERTORVISITOR_H

#include "Visitor.h"
#include "../AST/ASTNode.h"
#include <iostream>
#include <fstream>

namespace visitor {

    class XMLConverterVisitor : public Visitor {
    private:
        const std::string TAB_INDENT = "\t";

        /**
         * Holds the current indentation used to output in the XML file.
         */
        int currentIndent = 0;

        /**
         * Outputs of the program.
         */
        std::ofstream outputXML;

        /**
         * Utility function that returns a string with the respective indentation.
         * @return A string containing the respective indentation.
         */
        std::string getStartingPositionAfterIndent();

        /**
         * Some operators cannot be printed normally in an xml file, this function
         * replace the operators with the according command.
         * @param currentOperator The operator that needs to be printed.
         * @return The command needed to print that operator.
         */
        std::string printOperator(std::string currentOperator);

        /**
         * An expression can be single expression or contains an operator. If no operatos
         * <Expression> tag will be used otherwise <BinaryExprNode> will be used.
         * @param node The node that will be traversed.
         */
        void printExpression(ast::ASTExprNode * node);

        virtual void visit(ast::ASTNode *node) override;

        virtual void visit(ast::ASTVariableDeclaration *node) override;

        virtual void visit(ast::ASTAssignment *node) override;

        virtual void visit(ast::ASTPrintStatement *node) override;

        virtual void visit(ast::ASTBlock *node) override;

        virtual void visit(ast::ASTIfStatement *node) override;

        virtual void visit(ast::ASTWhileStatement *node) override;

        virtual void visit(ast::ASTReturnStatement *node) override;

        virtual void visit(ast::ASTFormalParam *node) override;

        virtual void visit(ast::ASTFunctionDeclaration *node) override;

        virtual void visit(ast::ASTExprStatement * node) override;

        virtual void visit(ast::ASTBooleanLiteral *node) override;

        virtual void visit(ast::ASTIntegerLiteral *node) override;

        virtual void visit(ast::ASTRealLiteral *node) override;

        virtual void visit(ast::ASTStringLiteral *node) override;

        virtual void visit(ast::ASTIdentifier *node) override;

        virtual void visit(ast::ASTSubExpression *node) override;

        virtual void visit(ast::ASTFunctionCall *node) override;

        virtual void visit(ast::ASTUnary *node) override;

        virtual void visit(ast::ASTBinaryExprNode *node) override;
    public:
        XMLConverterVisitor();

        virtual ~XMLConverterVisitor();
    };
}


#endif //COMPILERTHEORY_XMLCONVERTORVISITOR_H
