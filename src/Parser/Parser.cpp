//
// Created by dylan on 20/03/2017.
//

#include "../../include/Parser/Parser.h"
#include "../../include/Exceptions/UnexpectedTokenWhileParsing.h"
#include "../../include/Parser/AST/ASTExpression/ASTUnary.h"
#include "../../include/Exceptions/OperatorNotFound.h"

using namespace lexer;
using namespace std;
using namespace exceptions;

namespace parser {

    Parser::Parser(Lexer lexer) : lexer(lexer) {
        parse();
    }

    void Parser::parse() {
        vector<ast::ASTStatementNode *> statements;
        // Program can contain 0 or more Statements. If the first token is
        // TOK_EOF, it indicates that the program is empty.
        try {
            while (lexer.previewNextToken().tokenType != TOK_EOF) {
                statements.push_back(parseStatement());
            }
            ast::Visitor * visitor = new ast::XMLConverterVisitor();
            ast::ASTNode * programNode = new ast::ASTNode(statements);
            programNode->accept(visitor);
        } catch (UnexpectedTokenWhileParsing &error) {
            cout << error.reasonForError << endl;
        }
    }

    ast::ASTStatementNode * Parser::parseStatement() {
        currentToken = lexer.getNextToken();

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
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                      "Expected name after var keyword.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Colon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                      "Expected ':' after Identifier when variable declaration");
        }

        tokenType = parseType();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Equals) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '=' after Variable Type.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ';' after declaration.");
        }

        return new ast::ASTVariableDeclaration(identifier, tokenType, exprNode);
    }

    ast::ASTAssignment * Parser::parseAssignmentStatement() {
        std::string identifier;
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. "
                                                      "Expected name after set keyword.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Equals) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '=' after identifier.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ';' after assignment.");
        }

        return new ast::ASTAssignment(identifier, exprNode);
    }

    ast::ASTPrintStatement * Parser::parsePrintStatement() {
        ast::ASTExprNode * exprNode = parseExpression();
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ';' after assignment.");
        }

        return new ast::ASTPrintStatement(exprNode);
    }

    ast::ASTIfStatement * Parser::parseIfStatement() {
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '(' after If.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expect ')' after Expression.");
        }

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after If declaration.");
        }

        ast::ASTBlock * ifBlock = parseBlock();

        if (lexer.previewNextToken().tokenType != TOK_Else) {
            return new ast::ASTIfStatement(exprNode, ifBlock);
        }

        // First one get else, other one {.
        currentToken = lexer.getNextToken();
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after Else.");
        }
        // ParseBlock will parse the else block.
        return new ast::ASTIfStatement(exprNode, ifBlock, parseBlock());
    }

    ast::ASTWhileStatement * Parser::parseWhileStatement() {
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '(' after While statement.");
        }

        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ')' after Expression.");
        }

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after Expression.");
        }

        return new ast::ASTWhileStatement(exprNode, parseBlock());
    }

    ast::ASTReturnStatement * Parser::parseReturnStatement() {
        ast::ASTExprNode * exprNode = parseExpression();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_SemiColon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expecting ';' after return Statement.");
        }

        return new ast::ASTReturnStatement(exprNode);
    }

    ast::ASTFunctionDeclaration * Parser::parseFunctionDeclarationStatement() {
        string identifier;
        TOKEN tokenType;

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Identifier) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected identifier after def keyword.");
        }

        identifier = currentToken.tokenName;
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '(' after identifier.");
        }

        vector<ast::ASTFormalParam *> formalParams = parseFormalParam();
        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_RightParenthesis) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ')' after FormalParams.");
        }

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_Colon) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ':' after parenthesis.");
        }

        tokenType = parseType();

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_LeftCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '{' after Type.");
        }

        return new ast::ASTFunctionDeclaration(identifier, formalParams, tokenType, parseBlock());
    }

    ast::ASTBlock * Parser::parseBlock() {
        ast::ASTBlock * block = new ast::ASTBlock();

        // Statement inside a block contains 0 or more statements. If there are no
        // Statements, do not call parseStatements since it will cause trouble.
        while (lexer.previewNextToken().tokenType != TOK_RightCurlyBracket) {
            block->addStatement(parseStatement());
        }

        currentToken = lexer.getNextToken();

        if (currentToken.tokenType != TOK_RightCurlyBracket) {
            throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '}' after Block.");
        }
        return block;
    }

    ast::ASTExprNode * Parser::parseExpression() {
        ast::ASTBinaryExprNode * parent = nullptr;
        ast::ASTExprNode *factorLeft = parseFactor(), *factorRight;
        string validateOperator;

        // TODO: ask if it is allowed.
        while (true) {
            validateOperator = checkOperator();
            // The expression can only be not binaryExpr if there are no operators.
            if (validateOperator == "") {
                break;
            }
            factorRight = parseFactor();
            // There was not a previous node.
            if (parent == nullptr) {
                parent = new ast::ASTBinaryExprNode(validateOperator, factorLeft, factorRight);
            } else {
                parent = combineExpressions(parent, validateOperator, factorRight);
            }
        }

        if (parent == nullptr) {
            return factorLeft;
        } else {
            return parent;
        }
    }

    vector<ast::ASTFormalParam *> Parser::parseFormalParam() {
        vector<ast::ASTFormalParam *> formalParams;
        string identifier;
        TOKEN tokenType;

        while (lexer.previewNextToken().tokenType != TOK_RightParenthesis) {
            currentToken = lexer.getNextToken();

            if (currentToken.tokenType != TOK_Identifier) {
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected Identifier.");
            }

            identifier = currentToken.tokenName;
            currentToken = lexer.getNextToken();

            if (currentToken.tokenType != TOK_Colon) {
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ':' after identifier.");
            }

            tokenType = parseType();
            formalParams.push_back(new ast::ASTFormalParam(identifier, tokenType));

            if (lexer.previewNextToken().tokenType != TOK_Comma) {
                break;
            }
            currentToken = lexer.getNextToken();
        }
        return formalParams;
    }

    ast::ASTExprNode * Parser::parseFactor() {
        currentToken = lexer.getNextToken();
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
            currentToken = lexer.getNextToken();

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

        if (lexer.previewNextToken().tokenType == TOK_LeftParenthesis) {
            currentToken = lexer.getNextToken();
            parseActualParams(arguments);
            currentToken = lexer.getNextToken();

            if (currentToken.tokenType != TOK_RightParenthesis) {
                throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected ')' after parameters.");
            }
            functionCall = new ast::ASTFunctionCall(identifier, arguments);
        }
        return functionCall;
    }

    TOKEN Parser::parseType() {
        currentToken = lexer.getNextToken();

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
        if (lexer.previewNextToken().tokenType != TOK_RightParenthesis) {

            arguments.push_back(parseExpression());

            if (lexer.previewNextToken().tokenType == TOK_Comma) {
                currentToken = lexer.getNextToken();

                if (lexer.previewNextToken().tokenType == TOK_RightParenthesis) {
                    throw UnexpectedTokenWhileParsing(
                            "Unexpected Token found while parsing. Expected Expression after ','.");
                }
                parseActualParams(arguments);
            }
        }
    }

    string Parser::checkOperator() {
        Token nextToken = lexer.previewNextToken();

        switch (nextToken.tokenType) {
            case TOK_MultiplicativeOperator:
                currentToken = lexer.getNextToken();
                return currentToken.tokenName;
            case TOK_Logic:
                currentToken = lexer.getNextToken();

                if (currentToken.tokenName == "and") {
                    return currentToken.tokenName;
                } else if (currentToken.tokenName == "or"){
                    return currentToken.tokenName;
                } else {
                    throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected 'and' or 'or' "
                                                              "as an operator.");
                }
            case TOK_AdditiveOperator:
                currentToken = lexer.getNextToken();
                return currentToken.tokenName;
            case TOK_RelationalOperator:
                currentToken = lexer.getNextToken();
                return currentToken.tokenName;
            case TOK_Equals:
                // For an expression, there need to be '=='.
                currentToken = lexer.getNextToken();
                currentToken = lexer.getNextToken();

                if (currentToken.tokenType != TOK_Equals) {
                    throw UnexpectedTokenWhileParsing("Unexpected Token found while parsing. Expected '==' for "
                                                              "expressions");
                }
                return "==";
            default:
                return "";
        }
    }

    ast::ASTBinaryExprNode *Parser::combineExpressions(ast::ASTBinaryExprNode *parent, std::string currentOperator,
                                                       ast::ASTExprNode *newFactor) {
        int currentOperatorPrecedence = getOperatorPrecedence(parent->operation),
                newOperatorPrecedence = getOperatorPrecedence(currentOperator);

        if (newOperatorPrecedence >= currentOperatorPrecedence) {
            return new ast::ASTBinaryExprNode(currentOperator, parent, newFactor);
        } else {
            ast::ASTBinaryExprNode * parentOfNextNode = parent;
            ast::ASTBinaryExprNode * childNode = nullptr;

            while (currentOperatorPrecedence > newOperatorPrecedence) {
                childNode = dynamic_cast<ast::ASTBinaryExprNode *>(parentOfNextNode->RHS);

                if (childNode != nullptr) {
                    currentOperatorPrecedence = getOperatorPrecedence(childNode->operation);
                    parentOfNextNode = childNode;
                } else {
                    parentOfNextNode->setRHS(new ast::ASTBinaryExprNode(currentOperator, parentOfNextNode->RHS, newFactor));
                    return parent;
                }
            }
            return parent;
        }
    }

    int Parser::getOperatorPrecedence(std::string currentOperator) {

        if (currentOperator == "*" || currentOperator == "/" || currentOperator == "and") {
            return 10;
        } else if (currentOperator == "+" || currentOperator == "-" || currentOperator == "or") {
            return 20;
        } else if (currentOperator == "<" || currentOperator == ">" || currentOperator == "=="
                   || currentOperator == "!=" || currentOperator == "<=" || currentOperator == ">=") {
            return 30;
        } else {
            throw OperatorNotFound("Operator was not found, Problem with the Lexer.");
        }

    }
}