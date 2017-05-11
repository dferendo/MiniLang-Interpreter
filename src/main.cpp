#include <iostream>
#include <fstream>
#include "../include/Lexer/Lexer.h"
#include "../include/Parser/Parser.h"
#include "../include/MiniLangI.h"

bool checkExtension(char *programPassed);
std::string covertFileToString(std::ifstream & program);

using namespace lexer;
using namespace parser;

int main(int argc, char **argv) {
    MiniLangI miniLangI;
    miniLangI.setup();
}

/**
 * Check if the program passed matched the file extension.
 * @param programPassed
 * @return
 */
bool checkExtension(char *programPassed) {
    std::string program(programPassed);
    return program.substr(program.find_last_of(".") + 1) == "gulp";
}

/**
 * Convert the given file into a single string.
 * @param program
 * @return
 */
std::string covertFileToString(std::ifstream & program) {
    std::string sProgram, temp;

    if (program) {
        while (std::getline(program, temp)) {
            sProgram.append(temp + "\n");
        }
    } else {
        std::cout << "Error opening file!" << std::endl;
    }
    return sProgram;
}