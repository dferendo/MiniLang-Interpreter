//
// Created by dylan on 11/05/2017.
//
#include "../include/MiniLangI.h"
#include "../include/Parser/Parser.h"
#include "../include/Visitors/SemanticAnalysis.h"
#include "../include/Visitors/InterpreterExecution.h"
#include "../include/Visitors/XMLConverterVisitor.h"
#include <algorithm>

using namespace std;
using namespace lexer;
using namespace parser;
using namespace visitor;
using namespace ast;

void MiniLangI::setup() {
    cout << "MiniLangI 1.0.0" << endl;
    cout << "Type '#help' for list of available commands." << endl;

    readCommand();
}

void MiniLangI::readCommand() {
    std::string lineRead;
    // Set up lexer and parser.
    Parser parser(lexer);
    ASTNode * programNode = new ASTNode();
    // Visitors
    Visitor * xmlConverter = new XMLConverterVisitor();
    Visitor * semanticAnalysis = new SemanticAnalysis();
    Visitor * interpreter = new InterpreterExecution();

    while (true) {
        cout << "MLi> ";
        getline(cin, lineRead);
        checkCommand(lineRead);
        // Run Lexer;
//        lexer.tokenizeProgram(lineRead);
        // Run parser and add the new statements to the main node.
        programNode->addStatements(parser.parse());
        // Run XML file
        programNode->accept(xmlConverter);
    }
}

int MiniLangI::checkCommand(string &lineRead) {
    string fileRead;
    // Check if first character is #
    if (lineRead.at(0) != '#') {
        return 0;
    }
    // Load command.
    if (lineRead.find("#load") != string::npos) {
        // Remove load command
        lineRead = lineRead.substr(6, lineRead.size() - 6);
        // Remove " " from word, resulting in the file name.
        lineRead.erase(remove(lineRead.begin(), lineRead.end(), '\"'), lineRead.end());

        if (!checkExtension(lineRead)) {
            cout << "Wrong file extension, .gulp accepted only." << endl;
            return -2;
        }
        // Should remain the file name.
        std::ifstream program(lineRead);
        fileRead = covertFileToString(program);

        if (fileRead == "") {
            return -3;
        } else {
            lexer->tokenizeProgram(fileRead);
            return 1;
        }
    } else {
        cout << "Command not found." << endl;
        return -1;
    }
}

/**
 * Check if the program passed matched the file extension.
 *
 * @param programPassed
 * @return True if the program has the correct extension, false otherwise.
 */
bool MiniLangI::checkExtension(string & programPassed) {
    return programPassed.substr(programPassed.find_last_of(".") + 1) == "gulp";
}

/**
 * Convert the given file into a single string.
 *
 * @param program: The file stream.
 * @return String containing all the contents has the file.
 */
std::string MiniLangI::covertFileToString(std::ifstream & program) {
    std::string sProgram = "", temp;

    if (program) {
        while (std::getline(program, temp)) {
            sProgram.append(temp + "\n");
        }
    } else {
        std::cout << "Error opening file!" << std::endl;
    }
    return sProgram;
}