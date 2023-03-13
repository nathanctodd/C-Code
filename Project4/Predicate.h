#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Parameter.h"
#include "Token.h"


using namespace std;

class Predicate {

    private:
        string name;
        vector<Parameter> parameters;

    public:

    Predicate() {
    }

    Predicate(string inputName) {
        name = inputName;
    }

    void setName(string inputName) {
        name = inputName;
    }

    void addParameter(Parameter parameter) {
        parameters.push_back(parameter);
    }

    void setVector(vector<Parameter> addedParameters) {
        parameters = addedParameters;
    }

    string getName() {
        return name;
    }

    vector<Parameter> getVector() {
        return parameters;
    }

    vector<string> getStringVector() {
        vector<string> stringVector;
        for (unsigned i = 0; i < parameters.size(); i++) {
            stringVector.push_back(parameters[i].toString());
        }
        return stringVector;
    }

    string toString() {
       stringstream output;
       output << this->name << "(";
       output << parameters[0].toString();
       for(unsigned int i = 1; i < parameters.size(); i++) {
            output << "," << parameters[i].toString();
       }
       output << ")";
       return output.str();
    }

};







 