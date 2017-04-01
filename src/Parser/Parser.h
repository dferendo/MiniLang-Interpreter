//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_PARSER_H
#define COMPILERTHEORY_PARSER_H

#include "../Lexer/Lexer.h"
#include "AST/ASTNode.h"
#include "AST/ASTStatements/ASTStatementNode.h"
#include "AST/Visitors/XMLConverterVisitor.h"
#include "AST/ASTStatements/ASTVariableDeclaration.h"
#include "AST/ASTExpression/ASTBooleanLiteral.h"
#include "AST/ASTExpression/ASTIntegerLiteral.h"
#include "AST/ASTExpression/ASTRealLiteral.h"
#include "AST/ASTExpression/ASTStringLiteral.h"
#include "AST/ASTExpression/ASTFunctionCall.h"
#include "AST/ASTExpression/ASTIdentifier.h"
#include "AST/ASTExpression/ASTBinaryExprNode.h"
#include "AST/ASTStatements/ASTAssignment.h"
#include "AST/ASTStatements/ASTPrintStatement.h"
#include "AST/ASTStatements/ASTBlock.h"
#include "AST/ASTStatements/ASTIfStatement.h"
#include "AST/ASTStatements/ASTWhileStatement.h"
#include "AST/ASTStatements/ASTReturnStatement.h"
#include "AST/ASTStatements/ASTFunctionDeclaration.h"

namespace parser {

    class Parser {
    private:
        lexer::Lexer lexer;

        lexer::Token currentToken = lexer::Token(lexer::TOK_Error);

        void parse();

        ast::ASTStatementNode * parseStatement();

        ast::ASTVariableDeclaration * parseVariableDeclarationStatement();

        ast::ASTAssignment * parseAssignmentStatement();

        ast::ASTPrintStatement * parsePrintStatement();

        ast::ASTIfStatement * parseIfStatement();

        ast::ASTWhileStatement * parseWhileStatement();

        ast::ASTReturnStatement * parseReturnStatement();

        ast::ASTFunctionDeclaration * parseFunctionDeclarationStatement();

        ast::ASTBlock * parseBlock();

        ast::ASTExprNode * parseExpression();

        std::vector<ast::ASTFormalParam *> parseFormalParam();

        ast::ASTLiteralNode * parseLiteral();

        ast::ASTExprNode * parseFactor();

        ast::ASTFunctionCall * parseFunctionCall();

        void parseActualParams(std::vector<ast::ASTExprNode *> &arguments);

        lexer::TOKEN parseType();

        std::string checkOperator();

        ast::ASTBinaryExprNode * combineExpressions(ast::ASTBinaryExprNode * parent, std::string currentOperator,
                                                    ast::ASTExprNode * newFactor);

        int getOperatorPrecedence(std::string currentOperator);
    public:
        Parser(lexer::Lexer lexer);
    };
}


#endif //COMPILERTHEORY_PARSER_H
