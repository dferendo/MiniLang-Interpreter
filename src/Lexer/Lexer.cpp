//
// Created by dylan on 27/02/2017.
//

#include "../../include/Lexer/Lexer.h"
#include "../../include/Exceptions/LexerFailed.h"
#include <regex>

using namespace std;

namespace lexer {

    void Lexer::tokenization(std::string &program) {
        int charIndex = 0;
        Token currentToken(TOK_Error);

        while (currentToken.tokenType != TOK_EOF) {
            currentToken = nextWord(program, charIndex);

            // Error with the Lexer.
            if (currentToken.tokenType == TOK_Error) {
                cout << currentToken.tokenName << endl;
                exit(1);
            }
            // Comments TOKENS will be ignored.
            if (currentToken.tokenType != TOK_Comment) {
                allTokens.push_back(currentToken);
            }
        }
    }

    Token Lexer::nextWord(std::string &program, int &charIndex) {
        STATE currentState = S_00;
        char currentChar;
        string lexeme = "", error;
        stack<STATE> stack;
        stack.push(S_ERR);

        // Scanning loop
        while (currentState != S_ERR) {
            currentChar = nextChar(program, charIndex, lexeme);
            lexeme += currentChar;
            if (checkFinalState(currentState)) {
                clear(stack);
            }
            stack.push(currentState);
            currentState = miniLangTransitions[currentState][getClassifier(currentChar)];
            if (currentChar == EOF || currentChar == '\0') {
                break;
            }
        }

        // Rollback Loop
        while (!checkFinalState(currentState) && currentState == S_ERR) {
            currentState = stack.top();
            stack.pop();
            lexeme.pop_back();
            charIndex--;
        }

        // Determine Token or Error.
        if (checkFinalState(currentState)) {
            return determineToken(lexeme, currentState);
        } else {
            error = "Lexer failed at Line: " + to_string(determineErrorLine(program, charIndex)) + ". Please fix and try again.";
            throw exceptions::LexerFailed(error);
        }
    }

    char Lexer::nextChar(string &program, int &charIndex, string &lexeme) {
        while (true) {
            if ((size_t) charIndex == program.length()) {
                return EOF;
            } else if (lexeme.length() == 0){
                // When a new Token is being created, spaces and newlines can be skipped
                // since Tokens do not depend on them.
                if (program[charIndex] == ' ') {
                    charIndex++;
                } else if (program[charIndex] == '\n') {
                    charIndex++;
                } else {
                    return program[charIndex++];
                }
            } else {
                return program[charIndex++];
            }
        }
    }

    void Lexer::printTokens() {
        for (auto &token : allTokens) {
            cout << token.toString() << endl;
        }
    }

    void Lexer::clear(std::stack<STATE> &filledStack) {
        stack<STATE> emptyStack;
        swap(filledStack, emptyStack);
    }

    int Lexer::determineErrorLine(std::string &program, int &currentCharCount) {
        int counter = 1;
        for (int i = 0; i < currentCharCount; i++) {
            if (program[i] == '\n') {
                counter++;
            }
        }
        return counter;
    }

    Token Lexer::getNextToken() {

        if (currentIndex >= allTokens.size()) {
            return Token(TOK_Error, "All tokens have already been passed.");
        }
        return allTokens[currentIndex++];
    }

    Token Lexer::previewNextToken() {
        if (currentIndex >= allTokens.size()) {
            return Token(TOK_Error, "All tokens have already been passed.");
        }
        return allTokens[currentIndex];
    }

    Lexer::Lexer() {}

    void Lexer::tokenizeProgram(std::string &program) {
        allTokens.clear();
        currentIndex = 0;
        tokenization(program);
    }
}
