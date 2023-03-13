#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "Token.h"

using namespace std;



class Scanner {

    public:
        Scanner(const string& input) {
            this->input = input;
            currentLineNumber = 1;
            vector<Token> tokenVector;
        
        }

        vector<Token> getTokenVector() {
            return tokenVector;
        }

        int getSize() {
            return tokenVector.size();
        }

        string getInput() {
                return input;
        }

        void printVector() {
            for (unsigned int i = 0; i < tokenVector.size(); i++) {
                cout << tokenVector[i].toString() << endl;
            }
        }

        
        void scanTokens(string inputString) {
            int length = 0;
            int tokenIndex = 0;
            Token nextToken;

            while (inputString.size() > 0) {
                while((inputString.size() > 1) && (isspace(inputString.at(0)))) {
                    if (inputString.at(0) == '\n') {
                        currentLineNumber++;
                    }
                    inputString.erase(0, 1);
                }
                if (inputString.size() < 2) {
                    Token newToken = Token(ENDFILE, "", currentLineNumber);
                    tokenVector.push_back(newToken);
                    return;
                } else if (inputString.at(0) == EOF) {
                    Token newToken = Token(ENDFILE, "", currentLineNumber);
                    tokenVector.push_back(newToken);
                    return;
                }

                if (isalpha(inputString.at(0))) {
                    unsigned int currentIndex = 1;
                    bool isUndefined = false;
                    bool otherTokenFound = false;
                        if (inputString.size() > 1) {
                            while ((isUndefined == false) && ((!tokenFound(inputString.at(currentIndex)))) && (!isspace(inputString.at(currentIndex))) && (otherTokenFound == false)) {
                                if (currentIndex >= inputString.size()) {
                                    nextToken = Token(UNDEFINED, inputString.substr(0, currentIndex - 1), currentLineNumber);
                                    tokenVector.push_back(nextToken);
                                    isUndefined = true;
                                    length = currentIndex;
                                    Token newToken = Token(ENDFILE, "", currentLineNumber);
                                    tokenVector.push_back(newToken);
                                    return;
                                }
                                currentIndex += 1;
                                if ((inputString.substr(0, currentIndex) == "Queries") && (currentIndex < inputString.size()) && (!isalpha(inputString.at(currentIndex)) || (inputString.at(currentIndex) == '\n' ))) {
                                    otherTokenFound = true;
                                    nextToken = Token(QUERIES, "Queries", currentLineNumber);
                                    tokenVector.push_back(nextToken);
                                    length = 7;
                                } else if ((inputString.substr(0, currentIndex) == "Facts") && (currentIndex < inputString.size())  && (!isalpha(inputString.at(currentIndex)) || (inputString.at(currentIndex) == '\n' ))) {
                                    otherTokenFound = true;
                                    nextToken = Token(FACTS, "Facts", currentLineNumber);
                                    tokenVector.push_back(nextToken);
                                    length = 5;
                                } else if ((inputString.substr(0, currentIndex) == "Schemes") && (currentIndex < inputString.size())  && (!isalpha(inputString.at(currentIndex)) || (inputString.at(currentIndex) == '\n' ))) {
                                    otherTokenFound = true;
                                    nextToken = Token(SCHEMES, "Schemes", currentLineNumber);
                                    tokenVector.push_back(nextToken);
                                    length = 7;
                                } else if ((inputString.substr(0, currentIndex) == "Rules") && (currentIndex < inputString.size())  && (!isalpha(inputString.at(currentIndex)) || (inputString.at(currentIndex) == '\n' ))) {
                                    otherTokenFound = true;
                                    nextToken = Token(RULES, "Rules", currentLineNumber);
                                    tokenVector.push_back(nextToken);
                                    length = 5;
                                }
                                
                            }
                            if ((currentIndex <= inputString.size()) && (otherTokenFound == false)) {
                                nextToken = Token(ID, inputString.substr(0, currentIndex), currentLineNumber);
                                tokenVector.push_back(nextToken);
                                length = currentIndex;
                            }
                        }
                }
                if (isdigit(inputString.at(0))) {
                    Token newToken = Token(UNDEFINED, inputString.substr(0,1), currentLineNumber);
                    tokenVector.push_back(newToken);
                    length = 1;
                }

                switch (inputString.at(0)) {
                    case ',':
                        nextToken = Token(COMMA, ",", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '.':
                        nextToken = Token(PERIOD, ".", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '?':
                        nextToken = Token(Q_MARK, "?", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '(':
                        nextToken = Token(LEFT_PAREN, "(", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case ')':
                        nextToken = Token(RIGHT_PAREN, ")", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case ':':
                        if ((inputString.size() > 1) && (inputString.at(1) == '-')) {
                            nextToken = Token(COLON_DASH, ":-", currentLineNumber);
                            tokenVector.push_back(nextToken);
                            length = 2;
                        } else {
                            nextToken = Token(COLON, ":", currentLineNumber);
                            tokenVector.push_back(nextToken);
                            length = 1;
                        }
                        break;
                    case '*':
                        nextToken = Token(MULTIPLY, "*", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '+':
                        nextToken = Token(ADD, "+", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '$':
                        nextToken = Token(UNDEFINED, "$", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '&':
                        nextToken = Token(UNDEFINED, "&", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '@':
                        nextToken = Token(UNDEFINED, "@", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '#':
                        tokenIndex = 1;
                        while (inputString.at(tokenIndex) != '\n') {
                            tokenIndex = tokenIndex + 1;
                        }
                        nextToken = Token(COMMENT, inputString.substr(0, tokenIndex), currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = tokenIndex;
                        break;
                    case '^':
                        nextToken = Token(UNDEFINED, "^", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '!':
                        nextToken = Token(UNDEFINED, "!", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '%':
                        nextToken = Token(UNDEFINED, "%", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;
                    case '-':
                        nextToken = Token(UNDEFINED, "-", currentLineNumber);
                        tokenVector.push_back(nextToken);
                        length = 1;
                        break;

                    case '\'':
                        unsigned int currentIndex = 1;
                        int linesPassed = 0;
                        bool isUndefined = false;
                        if (inputString.size() > 2) {
                            while ((isUndefined == false) && (inputString.at(currentIndex) != '\'')) {
                                if (currentIndex + 1 >= inputString.size()) {
                                    nextToken = Token(UNDEFINED, inputString.substr(0, currentIndex), currentLineNumber - linesPassed);
                                    tokenVector.push_back(nextToken);
                                    isUndefined = true;
                                    length = currentIndex;
                                    //cout << "END OF FILE" << currentLineNumber;
                                    Token newToken = Token(ENDFILE, "", currentLineNumber);
                                    tokenVector.push_back(newToken);
                                    return;
                                }
                                if (isspace(inputString.at(currentIndex))) {
                                    if (inputString.at(currentIndex) == '\n') {
                                        currentLineNumber++;
                                        linesPassed++;
                                    }
                                }
                                
                                currentIndex += 1;
                            }
                            if (currentIndex <= inputString.size()) {
                                currentIndex += 1;
                                nextToken = Token(STRING, inputString.substr(0, currentIndex), currentLineNumber);
                                tokenVector.push_back(nextToken);
                                length = currentIndex;
                            }
                        }

                        break;           
                }

                inputString = inputString.substr(length);

            }

        }

            /*
                ScanTaken(string input) {
                    while (input.size > 0) {
                        while (isspace(input.at(0)) {
                            if (input.at(0) == "\n") {
                                currentLineNumber++;
                            }
                            input.erase(0,1);
                        }

                        switch (input.at(0)) {
                            case ':': 


                        }
                    }
                }




        */
       
       bool tokenFound(char input) {
           switch (input) {
                    case ',':
                        return true;
                        break;
                    case '.':
                        return true;
                        break;
                    case '?':
                        return true;
                        break;
                    case '(':
                        return true;
                        break;
                    case ')':
                        return true;
                        break;
                    case ':':
                        return true;
                        break;
                    case '*':
                        return true;
                        break;
                    case '+':
                        return true;
                        break;
                    case '$':
                        return true;
                        break;
                    case '&':
                        return true;
                        break;
                    case '@':
                        return true;
                        break;
                    case '#':
                        return true;
                        break;
                    case '^':
                        return true;
                        break;
                    case '\'':
                        return true;
                        break;
                    case '!':
                        return true;
                        break;
                    case '%':
                        return true;
                        break;
                    case '-':
                        return true;
                        break;
           }
        return false;
    }
      

    private:
        string input;
        int currentLineNumber;
        vector<Token> tokenVector;



};