#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum TokenType {

    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDFILE

};

class Token {

    public:
        Token(TokenType type, string valueGiven, int line) {
            selfTokenType = type;
            value = valueGiven;
            lineNumber = line;
        }
        Token() {
            selfTokenType = UNDEFINED;
            value = "";
            lineNumber = -1;
        }

        string toString() const {
            stringstream out;
            out << "(" << typeName(selfTokenType) << "," << "\"" << value << "\"," << lineNumber << ")";
            return out.str();
        }

        TokenType getType() const{
            return selfTokenType;
        }

        string getValue() const {
            return value;
        }

        string typeName(TokenType type) const {
            switch (type) {
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case Q_MARK:
                return "Q_MARK";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case ENDFILE:
                return "EOF";
            default:
                return "";
                break;
            }
            return "ERROR";
        }

    private:

    TokenType selfTokenType;
    string value;
    int lineNumber;
    


};