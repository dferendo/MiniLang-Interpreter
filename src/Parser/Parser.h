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

namespace parser {
    class Parser {
    private:
        lexer::Lexer lexer;
        lexer::Token currentToken = lexer::Token(lexer::TOK_Error);

        void parse();

        ast::ASTStatementNode * parseStatement();

        ast::ASTVariableDeclaration * parseVariableDeclarationStatement();

        void parseAssignmentStatement();

        void parsePrintStatement();

        void parseIfStatement();

        void parseWhileStatement();

        void parseReturnStatement();

        void parseFunctionDeclarationStatement();

        void parseBlock();

        ast::ASTExprNode * parseExpression();

        void parseFormalParam();

        ast::ASTLiteralNode * parseLiteral();

        ast::ASTExprNode * parseFactor();

        ast::ASTFunctionCall * parseFunctionCall();

        void parseActualParams(std::vector<ast::ASTExprNode *> &arguments);

        lexer::TOKEN parseType();

        ast::ASTBinaryExprNode * combineExpressions(ast::ASTBinaryExprNode *parent, ast::ASTBinaryExprNode * newNode);
    public:

        Parser(lexer::Lexer lexer);
    };
}


#endif //COMPILERTHEORY_PARSER_H
