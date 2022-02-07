#include <iostream>
#include <vector>
#include <string>
#include "Parser.h"
#include "Token.h"
#include "Scanner.h"
#include "DatalogProgram.h"
#include <fstream>


int main(int argc, char *argv[]) {

    ifstream input(argv[1]);
    //ifstream input("input.txt");
    stringstream inputStream;
    while (!input.eof()) {
        string next;
        getline(input, next);
        inputStream << next << endl;
    }
    
    Scanner scanner = Scanner(inputStream.str());
    scanner.scanTokens(inputStream.str());
    vector<Token> tokenInput = scanner.getTokenVector();
    Parser p = Parser(tokenInput);
    p.parseDatalogProgram();
    DatalogProgram data = p.getDatalog();
    cout << data.toString();


}