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

        ast::ASTExprNode parseExpression();

        void parseFormalParam();

        bool parseLiteral();

        void parseFactor();

        void parseTerm();

        void parseSimpleExpression();

        void parseFunctionCall();

        void parseActualParams();

        lexer::TOKEN parseType();
    public:

        Parser(lexer::Lexer lexer);
    };
}


#endif //COMPILERTHEORY_PARSER_H
