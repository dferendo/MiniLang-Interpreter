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

    long currentBlockAmount = 0;

    void readCommand();

    int checkCommand(std::string &lineRead);

    /**
     * Check if the program passed matched the file extension.
     *
     * @param programPassed
     * @return True if the program has the correct extension, false otherwise.
     */
    bool checkExtension(std::string & programPassed);

    /**
     * Convert the given file into a single string.
     *
     * @param program: The file stream.
     * @return String containing all the contents has the file.
     */
    std::string covertFileToString(std::ifstream & program);

    std::string multipleLineStatement(std::string lineRead);
public:
    void setup();
};

#endif //COMPILERTHEORY_MINILANGI_H
