//
// Created by dylan on 11/05/2017.
//
#include "../include/MiniLangI.h"
#include "../include/Lexer/Lexer.h"
#include "../include/Parser/Parser.h"
#include "../include/Visitors/SemanticAnalysis.h"
#include "../include/Visitors/InterpreterExecution.h"
#include "../include/Visitors/XMLConverterVisitor.h"

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
    Lexer lexer;
    Parser parser(lexer);
    ASTNode * programNode = new ASTNode();
    // Visitors
    Visitor * xmlConverter = new XMLConverterVisitor();
    Visitor * semanticAnalysis = new SemanticAnalysis();
    Visitor * interpreter = new InterpreterExecution();

    while (true) {
        cout << "MLi> ";
        getline(cin, lineRead);
        // Run Lexer;
        lexer.tokenizeProgram(lineRead);
        // Run parser and add the new statements to the main node.
        programNode->addStatements(parser.parse());
        // Run XML file
        programNode->accept(xmlConverter);
    }
}
