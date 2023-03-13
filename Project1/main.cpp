#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "Token.h"
#include "Scanner.h"

using namespace std;



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
    scanner.printVector();
    cout << "Total Tokens = " << scanner.getSize() << endl;

}