//
// Created by dylan on 15/03/2017.
//

#include <sstream>
#include "Token.h"
using namespace std;

namespace lexer {

    Token::Token(TOKEN tokenType) : tokenType(tokenType) {}

    Token::Token(lexer::TOKEN tokenType, const string &tokenName) : tokenType(tokenType), tokenName(tokenName) {}

    Token::Token(lexer::TOKEN tokenType, double tokenValue) : tokenType(tokenType), tokenValue(tokenValue) {}

    Token::Token(lexer::TOKEN tokenType, const string &tokenName, double tokenValue) : tokenType(tokenType),
                                                                                              tokenName(tokenName),
                                                                                              tokenValue(tokenValue) {}

    std::string Token::toString() {
        stringstream temp;
        temp << "[" + TOKEN_STRING[tokenType] << ", " << tokenName << ", " << tokenValue << "]";
        return temp.str();
    }

    Token determineToken(std::string &lexeme, lexer::STATE &acceptState) {
        switch (acceptState) {
            case S_01:
                return determinePunctuationToken(lexeme);
            case S_02:
                return Token(TOK_EOF);
            case S_03:
                return determineDigit(lexeme);
            case S_05:
                return determineWords(lexeme);
            case S_07:
                return determinePrintable(lexeme);
            case S_08:
            case S_14:
                return Token(TOK_MultiplicativeOperator, lexeme);
            case S_10:
            case S_13:
                return Token(TOK_Comment);
            case S_15:
                return Token(TOK_AdditiveOperator, lexeme);
            case S_16:
            case S_18:
                return Token(TOK_RelationalOperator, lexeme);
            case S_19:
                return Token(TOK_Equals);
            case S_00:
            case S_04:
            case S_06:
            case S_09:
            case S_11:
            case S_12:
            case S_17:
            case S_ERR:
            case S_TOTAL:
                return Token(TOK_Error, "A non-final state was selected");
        }
    }

    Token determinePunctuationToken(std::string &lexeme) {
        if (lexeme.length() != 1) {
            return Token(TOK_Error, "The length for punctuation is not correct.");
        }

        if (lexeme.find("{") != string::npos) {
            return Token(TOK_LeftCurlyBracket);
        } else if (lexeme.find("}") != string::npos) {
            return Token(TOK_RightCurlyBracket);
        } else if (lexeme.find("(") != string::npos) {
            return Token(TOK_LeftParenthesis);
        } else if (lexeme.find(")") != string::npos) {
            return Token(TOK_RightParenthesis);
        } else if (lexeme.find(",") != string::npos) {
            return Token(TOK_Comma);
        } else if (lexeme.find(":") != string::npos) {
            return Token(TOK_Colon);
        } else if (lexeme.find(";") != string::npos) {
            return Token(TOK_SemiColon);
        } else if (lexeme.find(".") != string::npos) {
            return Token(TOK_Period);
        } else {
            return Token(TOK_Error, "Punctuation not found.");
        }
    }

    Token determineDigit(std::string &lexeme) {
        if (lexeme.find(".") == string::npos) {
            return Token(TOK_IntegerLiteral, stod(lexeme));
        } else {
            return Token(TOK_RealLiteral, stod(lexeme));
        }
    }

    Token determineWords(std::string &lexeme) {
        string keyWords[] = {"real", "int", "bool", "string", "true", "false", "and", "or", "not", "set",
                             "var", "print", "return", "if", "else", "while", "def"
        };
        Token keyWordsToken[] = {Token(TOK_RealType), Token(TOK_IntType), Token(TOK_BoolType), Token(TOK_StringType),
                                 Token(TOK_BooleanLiteral, "true"), Token(TOK_BooleanLiteral, "false"),
                                 Token(TOK_Logic, "and"), Token(TOK_Logic, "or"), Token(TOK_Logic, "not"),
                                 Token(TOK_Set), Token(TOK_Var), Token(TOK_Print), Token(TOK_Return), Token(TOK_If),
                                 Token(TOK_Else), Token(TOK_While), Token(TOK_Def)
        };

        // Check if the lexeme is a key word.
        for (unsigned int i = 0; i < sizeof(keyWords)/sizeof(keyWords[0]); i++) {
            if (lexeme.length() == keyWords[i].length() && keyWords[i].find(lexeme) != string::npos) {
                return keyWordsToken[i];
            }
        }

        // If the lexeme is not a key word, it is an identifier.
        return Token(TOK_Identifier, lexeme);
    }

    Token determinePrintable(std::string &lexeme) {
        // Remove the first and last element of the string.
        return Token(TOK_Printable, lexeme.substr(1, lexeme.size() - 2));
    }

}


