//
// Created by dylan on 20/03/2017.
//

#include "Parser.h"
#include "../Exceptions/UnexpectedTokenWhileParsing.h"

using namespace lexer;
using namespace std;
using namespace exceptions;

parser::Parser::Parser(Lexer lexer) : lexer(lexer) {
    parse();
}

void parser::Parser::parse() {
    // TODO: Create initial ASTNode
    // Program can contain 0 or more Statements. If the first token is
    // TOK_EOF, it indicates that the program is empty.
    while (currentToken.tokenType != TOK_EOF) {
        parseStatement();
    }
}

void parser::Parser::parseStatement() {

    currentToken = lexer.getNextToken();

    switch (currentToken.tokenType) {
        case TOK_Var:
            parseVariableDeclarationStatement();
            break;
        case TOK_Set:
            parseAssignmentStatement();
            break;
        case TOK_Print:
            parsePrintStatement();
            break;
        case TOK_If:
            parseIfStatement();
            break;
        case TOK_While:
            parseWhileStatement();
            break;
        case TOK_Return:
            parseReturnStatement();
            break;
        case TOK_Def:
            parseFunctionDeclarationStatement();
            break;
        case TOK_LeftCurlyBracket:
            parseBlock();
            break;
        default:
            throw UnexpectedTokenWhileParsing("Unexpected token found while parsing. Expecting Statement Token.");
    }
    return;
}

void parser::Parser::parseVariableDeclarationStatement() {
    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Identifier) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                  "Expected Identifier after var keyword.");
    }

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Colon) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                  "Expected ':' after Identifier when variable declaration");
    }

    parseType();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Equals) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseExpression();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_SemiColon) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    return;
}

void parser::Parser::parseAssignmentStatement() {
    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Identifier) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Equals) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseExpression();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_SemiColon) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    return;
}

void parser::Parser::parsePrintStatement() {
    parseExpression();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_SemiColon) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    return;
}

void parser::Parser::parseIfStatement() {
    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_LeftParenthesis) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseExpression();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_RightParenthesis) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseBlock();

    if (lexer.previewNextToken().tokenType != TOK_Else) {
        return;
    }

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Else) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseBlock();

    return;
}

void parser::Parser::parseWhileStatement() {
    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_LeftParenthesis) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseExpression();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_RightParenthesis) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseBlock();

    return;
}

void parser::Parser::parseReturnStatement() {
    parseExpression();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_SemiColon) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    return;
}

void parser::Parser::parseFunctionDeclarationStatement() {
    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Identifier) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_LeftParenthesis) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseFormalParam();

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_RightParenthesis) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_Colon) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }

    parseType();

    parseBlock();

    return;
}

void parser::Parser::parseBlock() {

    // Statement inside a block is 0 or more statements. If there are no
    // Statements, do not call parseStatements since it will cause trouble.
    if (lexer.previewNextToken().tokenType != TOK_RightCurlyBracket) {
        parseStatement();
    }

    currentToken = lexer.getNextToken();

    if (currentToken.tokenType != TOK_RightCurlyBracket) {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }
    return;
}

void parser::Parser::parseExpression() {
    parseSimpleExpression();

    Token nextToken = lexer.previewNextToken();

    if (nextToken.tokenType == TOK_RelationalOperator) {
        currentToken = lexer.getNextToken();
        parseExpression();
        return;
    } else if (nextToken.tokenType == TOK_Equals) {
        currentToken = lexer.getNextToken();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Equals) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
        }
        parseExpression();
        return;
    }
}

void parser::Parser::parseFormalParam() {

    if (lexer.previewNextToken().tokenType == TOK_Identifier) {
        // TODO check current token??
        currentToken = lexer.getNextToken();
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Colon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
        }

        parseType();

        if (lexer.previewNextToken().tokenType == TOK_Comma) {
            currentToken = lexer.getNextToken();
            parseFormalParam();
        }
    }

    return;
}

void parser::Parser::parseType() {
    currentToken = lexer.getNextToken();

    switch (currentToken.tokenType) {
        case TOK_RealType:
        case TOK_IntType:
        case TOK_BoolType:
        case TOK_StringType:
            break;
        default:
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }
    return;
}

void parser::Parser::parseFactor() {

    currentToken = lexer.getNextToken();

    if (parseLiteral()) {
        return;
    } else if (currentToken.tokenType == TOK_Identifier) {
        // This factor can either be Identifier or Function call if the next token is TOK_LeftParenthesis.
        parseFunctionCall();
        return;
    } else if (currentToken.tokenType == TOK_LeftParenthesis) {
        currentToken = lexer.getNextToken();
        parseExpression();
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
        }

        return;
    }  else if ((currentToken.tokenType == TOK_AdditiveOperator && currentToken.tokenName == "+") ||
                (currentToken.tokenType == TOK_Logic && currentToken.tokenName == "not")) {
        parseExpression();
        return;
    } else {
        throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
    }
}

bool parser::Parser::parseLiteral() {

    switch (currentToken.tokenType) {
        case TOK_BooleanLiteral:
        case TOK_IntegerLiteral:
        case TOK_RealLiteral:
        case TOK_Printable:
            return true;
        default:
            return false;
    }
}

void parser::Parser::parseFunctionCall() {

    if (lexer.previewNextToken().tokenType == TOK_LeftParenthesis) {
        currentToken = lexer.getNextToken();

        parseActualParams();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
        }

        return;
    }
}

void parser::Parser::parseActualParams() {
    // Function call can have no actualParams
    if (lexer.previewNextToken().tokenType == TOK_RightParenthesis) {
        return;
    }

    parseExpression();

    if (lexer.previewNextToken().tokenType == TOK_Comma) {
        currentToken = lexer.getNextToken();

        if (lexer.previewNextToken().tokenType == TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing");
        }
        parseActualParams();
    }
    return;
}

void parser::Parser::parseTerm() {

    parseFactor();

    Token nextToken = lexer.previewNextToken();

    if (nextToken.tokenType == TOK_MultiplicativeOperator ||
            (nextToken.tokenType == TOK_Logic && nextToken.tokenName == "and")) {
        currentToken = lexer.getNextToken();
        parseTerm();
        return;
    }
    return;
}

void parser::Parser::parseSimpleExpression() {

    parseTerm();

    Token nextToken = lexer.previewNextToken();

    if (nextToken.tokenType == TOK_AdditiveOperator ||
            (nextToken.tokenType == TOK_Logic && nextToken.tokenName == "or")) {
        currentToken = lexer.getNextToken();
        parseSimpleExpression();
        return;
    }
    return;

}
