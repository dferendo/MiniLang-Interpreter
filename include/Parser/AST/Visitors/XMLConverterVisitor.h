//
// Created by dylan on 28/03/2017.
//

#ifndef COMPILERTHEORY_XMLCONVERTORVISITOR_H
#define COMPILERTHEORY_XMLCONVERTORVISITOR_H

#include "Visitor.h"
#include "../ASTExpression/ASTExprNode.h"
#include <iostream>
#include <fstream>

namespace parser {
    namespace ast {
        
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
            void printExpression(ASTExprNode * node);

            virtual void visit(ASTNode *node) override;

            virtual void visit(ASTVariableDeclaration *node) override;

            virtual void visit(ASTAssignment *node) override;

            virtual void visit(ASTPrintStatement *node) override;

            virtual void visit(ASTBlock *node) override;

            virtual void visit(ASTIfStatement *node) override;

            virtual void visit(ASTWhileStatement *node) override;

            virtual void visit(ASTReturnStatement *node) override;

            virtual void visit(ASTFormalParam *node) override;

            virtual void visit(ASTFunctionDeclaration *node) override;

            virtual void visit(ASTBooleanLiteral *node) override;

            virtual void visit(ASTIntegerLiteral *node) override;

            virtual void visit(ASTRealLiteral *node) override;

            virtual void visit(ASTStringLiteral *node) override;

            virtual void visit(ASTIdentifier *node) override;

            virtual void visit(ASTSubExpression *node) override;

            virtual void visit(ASTFunctionCall *node) override;

            virtual void visit(ASTUnary *node) override;

            virtual void visit(ASTBinaryExprNode *node) override;
        public:
            XMLConverterVisitor();
        };
    }
}


#endif //COMPILERTHEORY_XMLCONVERTORVISITOR_H
