#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Scheme.h"

using namespace std;


class Tuple {

    private:
        vector<string> values;

    public:
        Tuple();
        Tuple(vector<string> inputValues) {
            values = inputValues;
        }

        unsigned size() const {
            return values.size();
        }

        const string& at(int index) const {
            return values[index];
        }

        bool operator<(const Tuple t) const {
            return values < t.values;
        }

        string toString(const Scheme& scheme) const {
            stringstream out;
            for (unsigned i = 0; i < size(); i++) {
                if (i > 0)
                    out << ", ";
                const string& name = scheme.at(i);
                const string& value = at(i);
                out << name << "=" << value;
            }
            return out.str();
        }

};