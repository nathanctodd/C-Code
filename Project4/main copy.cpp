#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DatalogProgram.h"
#include "Database.h"
#include "Scanner.h"
#include "Relation.h"
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[]) {

    string fileName = argv[1];
    //string fileName = "test.txt";
    ifstream input(fileName);
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
    vector<Relation> relationVector;
    Database database(data, relationVector);
    database.evaluateSchemes();
    database.evaluateFacts();
    database.evaluateAllRules();
    database.evaluateQueries();
    //cout << data.toString();

}
