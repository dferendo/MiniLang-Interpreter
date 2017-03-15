#include <iostream>
#include <fstream>
#include "Lexer/Lexer.h"

bool checkExtension(char *programPassed);
std::string covertFileToString(std::ifstream & program);

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Program not passed through the arguments!" << std::endl;
    } else if (!checkExtension(argv[1])) {
        std::cout << "Extension of file not compatible" << std::endl;
    } else {
        std::ifstream program(argv[1]);
        lexer::Lexer(covertFileToString(program));
    }
    return 0;
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