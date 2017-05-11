//
// Created by dylan on 20/03/2017.
//

#include "../../include/Parser/Parser.h"
#include "../../include/Exceptions/UnexpectedTokenWhileParsing.h"
#include "../../include/AST/ASTExpression/ASTUnary.h"
#include "../../include/Visitors/SemanticAnalysis.h"
#include "../../include/Visitors/InterpreterExecution.h"

using namespace lexer;
using namespace std;
using namespace exceptions;
using namespace visitor;

namespace parser {


    vector<ast::ASTStatementNode *> Parser::parse() {
        vector<ast::ASTStatementNode *> statements;
        // Program can contain 0 or more Statements. If the first token is
        // TOK_EOF, it indicates that the program is empty.
        while (lexer->previewNextToken().tokenType != TOK_EOF) {
            statements.push_back(parseStatement());
        }
        return statements;
    }

    ast::ASTStatementNode * Parser::parseStatement() {
        currentToken = lexer->getNextToken();

        switch (currentToken.tokenType) {
            case TOK_Var:
                return parseVariableDeclarationStatement();
            case TOK_Set:
                return parseAssignmentStatement();
            case TOK_Print:
                return parsePrintStatement();
            case TOK_If:
                return parseIfStatement();
            case TOK_While:
                return parseWhileStatement();
            case TOK_Return:
                return parseReturnStatement();
            case TOK_Def:
                return parseFunctionDeclarationStatement();
            case TOK_LeftCurlyBracket:
                return parseBlock();
            default:
                throw UnexpectedTokenWhileParsing("Unexpected token found while parsing. Expecting Statement Token.");
        }
    }

    ast::ASTVariableDeclaration * Parser::parseVariableDeclarationStatement() {
        std::string identifier;
        TOKEN tokenType;
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                      "Expected name after var keyword.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Colon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                      "Expected ':' after Identifier when variable declaration");
        }

        tokenType = parseType();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Equals) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '=' after Variable Type.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ';' after declaration.");
        }

        return new ast::ASTVariableDeclaration(identifier, tokenType, exprNode);
    }

    ast::ASTAssignment * Parser::parseAssignmentStatement() {
        std::string identifier;
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                      "Expected name after set keyword.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Equals) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '=' after identifier.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ';' after assignment.");
        }

        return new ast::ASTAssignment(identifier, exprNode);
    }

    ast::ASTPrintStatement * Parser::parsePrintStatement() {
        ast::ASTExprNode * exprNode = parseExpression();
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ';' after assignment.");
        }

        return new ast::ASTPrintStatement(exprNode);
    }

    ast::ASTIfStatement * Parser::parseIfStatement() {
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '(' after If.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expect ')' after Expression.");
        }

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after If declaration.");
        }

        ast::ASTBlock * ifBlock = parseBlock();

        if (lexer->previewNextToken().tokenType != TOK_Else) {
            return new ast::ASTIfStatement(exprNode, ifBlock);
        }

        // First one get else, other one {.
        currentToken = lexer->getNextToken();
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after Else.");
        }
        // ParseBlock will parse the else block.
        return new ast::ASTIfStatement(exprNode, ifBlock, parseBlock());
    }

    ast::ASTWhileStatement * Parser::parseWhileStatement() {
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '(' after While statement.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ')' after Expression.");
        }

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after Expression.");
        }

        return new ast::ASTWhileStatement(exprNode, parseBlock());
    }

    ast::ASTReturnStatement * Parser::parseReturnStatement() {
        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expecting ';' after return Statement.");
        }

        return new ast::ASTReturnStatement(exprNode);
    }

    ast::ASTFunctionDeclaration * Parser::parseFunctionDeclarationStatement() {
        string identifier;
        TOKEN tokenType;
        vector<ast::ASTFormalParam *> formalParams;

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected identifier after def keyword.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '(' after identifier.");
        }

        parseFormalParams(formalParams);
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ')' after FormalParams.");
        }

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Colon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ':' after parenthesis.");
        }

        tokenType = parseType();

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after Type.");
        }

        return new ast::ASTFunctionDeclaration(identifier, formalParams, tokenType, parseBlock());
    }

    ast::ASTBlock * Parser::parseBlock() {
        ast::ASTBlock * block = new ast::ASTBlock();

        // Statement inside a block contains 0 or more statements. If there are no
        // Statements, do not call parseStatements since it will cause trouble.
        while (lexer->previewNextToken().tokenType != TOK_RightCurlyBracket) {
            block->addStatement(parseStatement());
        }

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_RightCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '}' after Block.");
        }
        return block;
    }

    ast::ASTExprNode * Parser::parseExpression() {
        ast::ASTExprNode * simpleExpression = parseSimpleExpression();
        string temp;

        if (lexer->previewNextToken().tokenType == TOK_RelationalOperator) {
            currentToken = lexer->getNextToken();
            temp = currentToken.tokenName;
            ast::ASTExprNode * expression = parseExpression();
            return new ast::ASTBinaryExprNode(temp, simpleExpression, expression);
        } else {
            return simpleExpression;
        }
    }

    ast::ASTExprNode *Parser::parseTerm() {
        ast::ASTExprNode * factor = parseFactor();
        string temp;
        TOKEN nextToken = lexer->previewNextToken().tokenType;

        if (nextToken == TOK_MultiplicativeOperator ||
            (nextToken == TOK_Logic && lexer->previewNextToken().tokenName == "and")){
            currentToken = lexer->getNextToken();
            temp = currentToken.tokenName;
            ast::ASTExprNode * term = parseTerm();
            return new ast::ASTBinaryExprNode(temp, factor, term);
        } else {
            return factor;
        }
    }

    ast::ASTExprNode *Parser::parseSimpleExpression() {
        ast::ASTExprNode * term = parseTerm();
        string temp;
        TOKEN nextToken = lexer->previewNextToken().tokenType;

        if (nextToken == TOK_AdditiveOperator ||
            (nextToken == TOK_Logic && lexer->previewNextToken().tokenName == "or")) {
            currentToken = lexer->getNextToken();
            temp = currentToken.tokenName;
            ast::ASTExprNode * simpleExpression = parseSimpleExpression();
            return new ast::ASTBinaryExprNode(temp, term, simpleExpression);
        } else {
            return term;
        }
    }

    void Parser::parseFormalParams(vector<ast::ASTFormalParam *> &formalParams) {

        if (lexer->previewNextToken().tokenType == TOK_RightParenthesis) {
            return;
        }

        if (formalParams.size() == 0) {
            formalParams.push_back(parseFormalParam());
        } else {
            currentToken = lexer->getNextToken();

            if (currentToken.tokenType != TOK_Comma) {
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ',' after param.");
            }
            formalParams.push_back(parseFormalParam());
        }
        parseFormalParams(formalParams);
    }

    ast::ASTFormalParam * Parser::parseFormalParam() {
        string identifier;
        TOKEN tokenType;

        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected Identifier.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer->getNextToken();

        if (currentToken.tokenType != TOK_Colon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ':' after identifier.");
        }

        tokenType = parseType();
        return new ast::ASTFormalParam(identifier, tokenType);
    }

    ast::ASTExprNode * Parser::parseFactor() {
        currentToken = lexer->getNextToken();
        ast::ASTLiteralNode * literalNode = parseLiteral();

        if (literalNode != nullptr) {
            return literalNode;
        } else if (currentToken.tokenType == TOK_Identifier) {
            // This factor can either be Identifier or Function call if the next token is TOK_LeftParenthesis.
            ast::ASTFunctionCall * functionCall = parseFunctionCall();

            if (functionCall != nullptr) {
                return functionCall;
            } else {
                return new ast::ASTIdentifier(currentToken.tokenName);
            }
        } else if (currentToken.tokenType == TOK_LeftParenthesis) {
            ast::ASTExprNode * exprNode = parseExpression();
            currentToken = lexer->getNextToken();

            if (currentToken.tokenType != TOK_RightParenthesis) {
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expecting ')' after expression");
            }

            return exprNode;
        } else if ((currentToken.tokenType == TOK_AdditiveOperator && currentToken.tokenName == "-") ||
                   (currentToken.tokenType == TOK_Logic && currentToken.tokenName == "not")) {
            string temp = currentToken.tokenName;
            return new ast::ASTUnary(temp, parseExpression());
        } else {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected Expression.");
        }
    }

    ast::ASTLiteralNode * Parser::parseLiteral() {

        switch (currentToken.tokenType) {
            case TOK_BooleanLiteral:
                return new ast::ASTBooleanLiteral(currentToken.tokenName.find("true") != string::npos);
            case TOK_IntegerLiteral:
                return new ast::ASTIntegerLiteral((int) currentToken.tokenValue);
            case TOK_RealLiteral:
                return new ast::ASTRealLiteral(currentToken.tokenValue);
            case TOK_Printable:
                return new ast::ASTStringLiteral(currentToken.tokenName);
            default:
                return nullptr;
        }
    }

    ast::ASTFunctionCall * Parser::parseFunctionCall() {
        // The current token is the identifier.
        std::string identifier = currentToken.tokenName;
        ast::ASTFunctionCall * functionCall = nullptr;
        vector<ast::ASTExprNode *> arguments;

        if (lexer->previewNextToken().tokenType == TOK_LeftParenthesis) {
            currentToken = lexer->getNextToken();
            parseActualParams(arguments);
            currentToken = lexer->getNextToken();

            if (currentToken.tokenType != TOK_RightParenthesis) {
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ')' after parameters.");
            }
            functionCall = new ast::ASTFunctionCall(identifier, arguments);
        }
        return functionCall;
    }

    TOKEN Parser::parseType() {
        currentToken = lexer->getNextToken();

        switch (currentToken.tokenType) {
            case TOK_RealType:
            case TOK_IntType:
            case TOK_BoolType:
            case TOK_StringType:
                return currentToken.tokenType;
            default:
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                          "Expected Variable Type after ':'.");
        }
    }

    void Parser::parseActualParams(vector<ast::ASTExprNode *> &arguments) {
        // Function call can have no actualParams
        if (lexer->previewNextToken().tokenType != TOK_RightParenthesis) {

            arguments.push_back(parseExpression());

            if (lexer->previewNextToken().tokenType == TOK_Comma) {
                currentToken = lexer->getNextToken();

                if (lexer->previewNextToken().tokenType == TOK_RightParenthesis) {
                    throw UnexpectedTokenWhileParsing(
                            "Unexpected Token found while parsing. Expected Expression after ','.");
                }
                parseActualParams(arguments);
            }
        }
    }

    Parser::Parser(lexer::Lexer *lexer) {
        this->lexer = lexer;
    }

}