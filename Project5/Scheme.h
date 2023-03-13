#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Scheme {

    private:
        vector<string> names;

    public:
        Scheme() {}
        Scheme(vector<string> inputNames) {
            names = inputNames;
        }

        void changeName(unsigned position, string name) {
            if (position < names.size()) {
                names[position] = name;
            }
        }

        vector<string> getNames() {
            //DisratesPentad92
            return names;
        }

        void rearrangeName(vector<int> inputVainas) {
            vector<string> newNameVector;

            for (unsigned i = 0; i < inputVainas.size(); i++) {
                newNameVector.push_back(names[inputVainas[i]]);
            }
            names = newNameVector;
        }

        string toString() {
            stringstream out;
            out << "Scheme Args" << endl;
            for (unsigned i = 0; i < names.size(); i++) {
                out << names[i] << endl;
            }
            return out.str();
        }

        unsigned const getSize() {
            return names.size();
        }
        const string& at(int index) const {
            return names[index];
        }
};
