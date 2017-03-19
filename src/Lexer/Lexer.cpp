//
// Created by dylan on 27/02/2017.
//

#include "Lexer.h"
#include <regex>

using namespace std;

namespace lexer {

    Lexer::Lexer(string program) {
        tokenization(program);
    }

    void Lexer::tokenization(std::string &program) {
        int charIndex = 0;
        Token currentToken(TOK_Error);

        while (currentToken.tokenType != TOK_EOF) {
            currentToken = nextWord(program, charIndex);
            // Comments TOKENS will be ignored.
            if (currentToken.tokenType != TOK_Comment) {
                allTokens.push_back(currentToken);
            }
        }
        printTokens();
    }

    Token Lexer::nextWord(std::string &program, int &charIndex) {
        STATE currentState = S_00;
        char currentChar;
        string lexeme = "";
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
            if (currentChar == EOF) {
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
            cout << "Lexer failed at Line: " << determineErrorLine(program, charIndex) << ". Please "
                    "fix and try again. The Lexer will terminate." << endl;
            exit(1);
        }
    }

    char Lexer::nextChar(string &program, int &charIndex, string &lexeme) {
        while (true) {
            if (charIndex == program.length()) {
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

}
