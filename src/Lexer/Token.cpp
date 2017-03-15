//
// Created by dylan on 15/03/2017.
//

#include "Token.h"
using namespace std;

namespace lexer {

    Token::Token(TOKEN tokenType) : tokenType(tokenType) {}

    Token::Token(lexer::TOKEN tokenType, const string &tokenName) : tokenType(tokenType), tokenName(tokenName) {}

    Token::Token(lexer::TOKEN tokenType, double tokenValue) : tokenType(tokenType), tokenValue(tokenValue) {}

    Token::Token(lexer::TOKEN tokenType, const string &tokenName, double tokenValue) : tokenType(tokenType),
                                                                                              tokenName(tokenName),
                                                                                              tokenValue(tokenValue) {}

    Token determineToken(std::string &lexeme, lexer::STATE &acceptState) {
        switch (acceptState) {
            case S_01:
                if (lexeme.length() == 1) {
                    if (lexeme.find("{") != string::npos) {
                        return Token(TOK_LeftCurlyBracket);
                    } else if (lexeme.find("}") != string::npos) {
                        return Token(TOK_RightCurlyBracket);
                    }
                }
                break;
            case S_02:
                return Token(TOK_EOF);
            case S_00:
            case S_ERR:
                cout << "Error has occurred" << endl;
                break;
        }
    }
}


