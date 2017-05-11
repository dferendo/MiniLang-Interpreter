//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_PARSER_H
#define COMPILERTHEORY_PARSER_H

#include "../Lexer/Lexer.h"
#include "../AST/ASTNode.h"
#include "../AST/ASTStatements/ASTStatementNode.h"
#include "../AST/ASTStatements/ASTVariableDeclaration.h"
#include "../AST/ASTExpression/ASTBooleanLiteral.h"
#include "../AST/ASTExpression/ASTIntegerLiteral.h"
#include "../AST/ASTExpression/ASTRealLiteral.h"
#include "../AST/ASTExpression/ASTStringLiteral.h"
#include "../AST/ASTExpression/ASTFunctionCall.h"
#include "../AST/ASTExpression/ASTIdentifier.h"
#include "../AST/ASTExpression/ASTBinaryExprNode.h"
#include "../AST/ASTStatements/ASTAssignment.h"
#include "../AST/ASTStatements/ASTPrintStatement.h"
#include "../AST/ASTStatements/ASTBlock.h"
#include "../AST/ASTStatements/ASTIfStatement.h"
#include "../AST/ASTStatements/ASTWhileStatement.h"
#include "../AST/ASTStatements/ASTReturnStatement.h"
#include "../AST/ASTStatements/ASTFunctionDeclaration.h"

namespace parser {

    class Parser {
    private:
        /**
         * Holds the lexer that will be used to pass the tokens.
         */
        lexer::Lexer * lexer;

        /**
         * Holds the current Token.
         */
        lexer::Token currentToken = lexer::Token(lexer::TOK_Error);

        /**
         * Parse a statement. A statement can be initialised by the following.
         * 'var' keyword will start a Variable Declaration,
         * 'set' keyword will start a Variable Assignment,
         * 'print' keyword will start a print statement,
         * 'if' keyword will start an if statement,
         * 'while' keyword will start a while statement,
         * 'return' keyword will start a return statement,
         * 'def' keyword will start a function declaration,
         * '{' will start a block statement.
         * @return Will return the AST of the statement passed.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTStatementNode * parseStatement();

        /**
         * Parses a Variable Declaration. After the keyword 'var' which is taken by the statement,
         * it expects an identifier, ':', Type, '=', an Expression and ';'.
         * @return Returns the AST of the variable declaration.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTVariableDeclaration * parseVariableDeclarationStatement();

        /**
         * Parses an Assignment. After the keyword 'set' which is taken by the statement, it
         * expects an identifier, '=' an Expression and ';'.
         * @return Returns the AST of the assignment.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTAssignment * parseAssignmentStatement();

        /**
         * Parses a print statement. After the keyword 'print' which is taken by the statement,
         * it expects an Expression and a ';'.
         * @return Returns the AST of the print statement.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTPrintStatement * parsePrintStatement();

        /**
         * Parses an If Statement. After the keyword 'if' which is taken by the statement,
         * it expects '(', an Expression, ')', a Block, and an optional 'else' keyword. If there
         * is an else, another block is expected.
         * @return Returns the AST of the If statement.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTIfStatement * parseIfStatement();

        /**
         * Parses a while statement. After the keyword 'while' which is taken by the statement,
         * it expects '(', an Expression, ')' and a block.
         * @return Returns the AST of the While Statement.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTWhileStatement * parseWhileStatement();

        /**
         * Parses a return Statement. After the keyword 'return' which is taken by the statement,
         * it expected an Expression and a ';'.
         * @return Returns the AST of a return statement.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTReturnStatement * parseReturnStatement();

        /**
         * Parses a function declaration. After the keyword 'def' which is taken by the statement,
         * it expects an identifier, '(', optional formal parameters, ')', ':', Type and a Block.
         * @return Returns the AST of a function declaration.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTFunctionDeclaration * parseFunctionDeclarationStatement();

        /**
         * Parses a block statement. Block statements accepts 0 or many statements. Expected
         * '}' to end a block statement.
         * @return Returns the AST of the block.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTBlock * parseBlock();

        /**
         * Handles the relation operators (<, >, ==, <=, >=) of an expression.
         *
         * @return Returns simpleExpression if no relation operator is next, otherwise
         * returns ast::BinaryExprNode with the operator, simpleExpression and another
         * computed simpleExpression.
         */
        ast::ASTExprNode * parseExpression();

        /**
         * Handles the additive operators (+, -) of an expression.
         *
         * @return: Returns the term if no additive operator is next, otherwise returns
         * ast::BinaryExprNode with the operator, the term and another computed term.
         */
        ast::ASTExprNode * parseSimpleExpression();

        /**
         * Handles the multiplier operators (*, /) of an expression.
         *
         * @return: Returns the factor if no multiplicative operator is next, otherwise returns
         * ast::BinaryExprNode with the operator, the factor and another computed factor.
         */
        ast::ASTExprNode * parseTerm();

        /**
         * Parses formal parameters. To add more parameters ',' is added between parameters.
         *
         * @param formalParams: Holds all the parameters of the function.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        void parseFormalParams(std::vector<ast::ASTFormalParam *> &formalParams);

        /**
         * A formal parameter expects an identifier, ':' and a type.
         *
         * @return: the formal parameter.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTFormalParam * parseFormalParam();

        /**
         * Parses a literal Node. It can be Boolean, Integer, Real or String literal.
         * @return A literal Node, nullptr if token is not literal.
         */
        ast::ASTLiteralNode * parseLiteral();

        /**
         * A factor can be a Literal, Identifier, FunctionCall, subExpression or Unary.
         * @return The ASTNode of the factor which are children of ASTExprNode.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTExprNode * parseFactor();

        /**
         * Parses a function call. It expects an identifier, '(', optional Actual Params and ')'.
         * @return Returns ASTFunctionCall Node.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        ast::ASTFunctionCall * parseFunctionCall();

        /**
         * Parses the actual Params used by the function call. It expects an expression. Multiple actual parameters
         * can be added by inserting a ',' between 2 actual params.
         * @param arguments The vectors that holds the actual params.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        void parseActualParams(std::vector<ast::ASTExprNode *> &arguments);

        /**
         * Checks if the next token is a token type. Throws exception if it is not.
         * @return The type of the token.
         * @throw UnexpectedTokenWhileParsing will be thrown if unexpected token.
         */
        lexer::TOKEN parseType();
    public:
        Parser(lexer::Lexer * lexer);

        /**
         * Starts the parser. The program can contains 0 or more statements. Parser will
         * stop when TOK_EOF is encountered.
         */
        std::vector<ast::ASTStatementNode *> parse();
    };
}


#endif //COMPILERTHEORY_PARSER_H
