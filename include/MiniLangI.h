//
// Created by dylan on 11/05/2017.
//

#ifndef COMPILERTHEORY_MINILANGI_H
#define COMPILERTHEORY_MINILANGI_H

#include <string>
#include "Lexer/Lexer.h"

class MiniLangI {
private:
    /**
     * Creates an instance of the lexer. One instance is enough, it will not be needed
     * to re-instance.
     */
    lexer::Lexer * lexer = new lexer::Lexer();

    /**
     * This is used for multi line commands and it holds the number of { used.
     * When there is a } the number will decrease.
     */
    long currentBlockAmount = 0;

    /**
     * The main loop of MiniLangI. Will continue to read commands until #quit is found.
     */
    void readCommand();

    /**
     * Checks if the user entered a special command starting with '#'. If so the appriopiate
     * action and return are completed.
     * @param lineRead: The command inputted in the terminal.
     * @return -1: If the command inputted was bad (like empty string). Re-read another command.
     *          0: No special command found.
     *          1: #load command was successful.
     *          2: Quit program.
     *          3: Show statements in the symbol table.
     *          4: Printed #help.
     */
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

    /**
     * Reads multiple line.
     * @param lineRead The command that enable multiple lines.
     * @return All the commands inputted.
     */
    std::string multipleLineStatement(std::string lineRead);
public:
    void setup();

    virtual ~MiniLangI();
};

#endif //COMPILERTHEORY_MINILANGI_H
