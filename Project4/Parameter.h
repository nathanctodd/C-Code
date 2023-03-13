#pragma once

#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Parameter {

    private:
        string data;

    public: 

        Parameter(string dataInput) {
            data = dataInput;
        }

        void setParameter(string newData) {
            data = newData;
        }

        string toString() {
            return data;
        }
};