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
        // TODO: Remove?
        Token currentToken(TOK_LeftCurlyBracket);

        while (currentToken.tokenType != TOK_EOF) {
            currentToken = nextWord(program, charIndex);
            allTokens.push_back(currentToken);
        }
    }

    Token Lexer::nextWord(std::string &program, int &charIndex) {
        STATE currentState = S_00;
        char currentChar;
        string lexeme = "";
        stack<STATE> stack;
        stack.push(S_ERR);

        // Scanning loop
        while (currentState != S_ERR) {
            currentChar = nextChar(program, charIndex);
            lexeme += currentChar;
            if (checkFinalState(currentState)) {
                clear(stack);
            }
            stack.push(currentState);
            currentState = *miniLangTable[currentState, getClassifier(currentChar)];
        }

        // Rollback Loop
        while (checkFinalState(currentState) && currentState != S_ERR) {
            currentState = stack.top();
            stack.pop();
            lexeme.pop_back();
            charIndex--;
        }

        if (checkFinalState(currentState)) {
            return determineToken(lexeme, currentState);
        } else {
            cout << "Error occorded";
            // TODO
            exit(1);
        }
    }

    char Lexer::nextChar(std::string &program, int &charIndex) {
        while (true) {
            if (program[++charIndex] == '\n' || program[charIndex] == ' ') {
                continue;
            } else {
                return program[charIndex];
            }
        }
    }

    void Lexer::printTokens() {
        for (auto const &token : allTokens) {

        }

    }

    void Lexer::clear(std::stack<STATE> &filledStack) {
        stack<STATE> emptyStack;
        swap(filledStack, emptyStack);
    }

}
