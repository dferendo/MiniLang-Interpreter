//
// Created by dylan on 20/03/2017.
//

#ifndef COMPILERTHEORY_PARSER_H
#define COMPILERTHEORY_PARSER_H

#include "../Lexer/Lexer.h"

namespace parser {
    class Parser {
    private:
        lexer::Lexer lexer;
        lexer::Token currentToken = lexer::Token(lexer::TOK_Error);

        void parse();

        void parseStatement();

        void parseVariableDeclarationStatement();

        void parseAssignmentStatement();

        void parsePrintStatement();

        void parseIfStatement();

        void parseWhileStatement();

        void parseReturnStatement();

        void parseFunctionDeclarationStatement();

        void parseBlock();

        void parseExpression();

        void parseFormalParam();

        void parseType();

        bool parseLiteral();

        void parseFactor();

        void parseTerm();

        void parseSimpleExpression();

        void parseFunctionCall();

        void parseActualParams();
    public:

        Parser(lexer::Lexer lexer);
    };
}


#endif //COMPILERTHEORY_PARSER_H
