//
// Created by dylan on 11/05/2017.
//

#ifndef COMPILERTHEORY_MINILANGI_H
#define COMPILERTHEORY_MINILANGI_H

#include <string>
#include "Lexer/Lexer.h"

class MiniLangI {
private:
    lexer::Lexer * lexer = new lexer::Lexer();

    void readCommand();

    int checkCommand(std::string &lineRead);

    bool checkExtension(std::string & programPassed);

    std::string covertFileToString(std::ifstream & program);
public:
    void setup();
};

#endif //COMPILERTHEORY_MINILANGI_H
