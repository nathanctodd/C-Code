#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {

    private:
        string name;
        Scheme mainScheme;
        set<Tuple> tuples;

    public:

        Relation(){

        }

        Relation(string inputName, Scheme inputScheme) {
            name = inputName;
            mainScheme = inputScheme;
        }

        Relation(string inputName, Scheme inputScheme, set<Tuple> listTuple) {
            name = inputName;
            mainScheme = inputScheme;
            tuples = listTuple;
        }

        string getName() {
            return name;
        }

        void setName(string nameInput) {
            name = nameInput; 
        }

        bool addTuple(const Tuple& tuple) {
            bool ok = tuples.insert(tuple).second;
            return ok;
        }

        set<Tuple> getTupleSet() {
            return tuples;
        }

        int getNumberTuples() {
            return tuples.size();
        }

        Scheme getScheme() {
            return mainScheme;
        }

        string toString() const {
            stringstream out;
            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                out << "  " << (*itr).toString(mainScheme) << endl;
            }
            return out.str();
        }

        Relation select(int index, const string& value) const {
            Relation result(name, mainScheme);
            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                if ((*itr).at(index) == value) {
                    result.addTuple((*itr));
                }
            }    
            return result;    
        }

        Relation select(int index1, int index2) const {
            Relation result(name, mainScheme);
            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                if ((*itr).at(index1) == (*itr).at(index2)) {
                    result.addTuple((*itr));
                }
            }
            return result;
        }

        Relation project(vector<int> indexes) const {

            Scheme newestScheme = mainScheme;
            newestScheme.rearrangeName(indexes);
            Relation result(name, newestScheme);

            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                vector<string> newestTuple;
                for (unsigned i = 0; i < indexes.size(); i++) {
                    newestTuple.push_back((*itr).at(indexes[i]));
                }
                Tuple newTuple(newestTuple);
                result.addTuple(newTuple);
            }
            return result;
        }

        Relation rename(vector<string> newNames) const {
            Scheme newScheme(newNames);
            Relation result(name, newScheme, tuples);
            return result;          
        }

        static bool joinable(Scheme leftScheme, Scheme rightScheme, const Tuple& leftTuple, const Tuple& rightTuple) {
            for (unsigned leftIndex = 0; leftIndex < leftScheme.getSize(); leftIndex++) {
                string leftName = leftScheme.at(leftIndex);
                string leftValue = leftTuple.at(leftIndex);
                for (unsigned rightIndex = 0; rightIndex < rightScheme.getSize(); rightIndex++) {
                    const string& rightName = rightScheme.at(rightIndex);
                    const string& rightValue = rightTuple.at(rightIndex);
                    if (leftName == rightName) {
                        if (leftValue != rightValue)
                            return false;
                    }
                }
            }
            return true;
        }

        Relation join( Relation r) {
            const Scheme& leftScheme = mainScheme;
            Scheme rightScheme = r.mainScheme;
            vector< pair<unsigned int, unsigned int> > pairedSchemesList;
            Scheme combinedScheme = joinSchemes(leftScheme, rightScheme, pairedSchemesList);
            Relation combinedRelation(this->name, combinedScheme);

            set<Tuple>::iterator itr;
            for (itr = tuples.begin(); itr != tuples.end(); itr++) {
                set<Tuple>::iterator itr2;
                for (itr2 = r.tuples.begin(); itr2 != r.tuples.end(); itr2++) {
                    if (joinable(leftScheme, rightScheme, (*itr), (*itr2))) {
                        Tuple newTuple = joinTuples((*itr), (*itr2), pairedSchemesList);
                        if (newTuple.size() > 0) {
                            combinedRelation.addTuple(newTuple);
                        }
                    }
                }
            }
            return combinedRelation;
        }

        Tuple joinTuples(Tuple tuple1, Tuple tuple2, vector< pair<unsigned int, unsigned int> >& listOfPairs) {
            vector<string> tupleValues;
            bool canBeAdded = true;
            for (unsigned k = 0; k < tuple1.size(); k++) {
                for (unsigned m = 0; m < listOfPairs.size(); m++) {
                    if (k == listOfPairs[m].first) {
                        if (tuple1.at(listOfPairs[m].first) != tuple2.at(listOfPairs[m].second)) {
                            canBeAdded = false;
                        }
                    }
                }
                if (canBeAdded == true) {
                    tupleValues.push_back(tuple1.at(k));
                }
            }
            for (unsigned k = 0; k < tuple2.size(); k++) {
                canBeAdded = true;
                for (unsigned m = 0; m < listOfPairs.size(); m++) {
                    if (k == listOfPairs[m].second) {
                        canBeAdded = false;
                    }
                }
                if (canBeAdded == true) {
                    tupleValues.push_back(tuple2.at(k));
                }
            }
            Tuple tuple(tupleValues);
            return tuple;
        }

        Scheme joinSchemes(Scheme scheme1, Scheme scheme2, vector< pair<unsigned int, unsigned int> >& listOfPairs) {
            vector<string> schemeArgs;
            for (unsigned i = 0; i < scheme1.getSize(); i++) {
                bool foundInSchemeArgs = false;
                for (unsigned k = 0; k < schemeArgs.size(); k++) {
                   if (scheme1.at(i) == schemeArgs[k]) {
                       foundInSchemeArgs = true;
                    }
                }
                for (unsigned m = 0; m < scheme2.getSize(); m++) {
                    if (scheme1.at(i) == scheme2.at(m)) {
                        pair<unsigned int, unsigned int> newPair;
                        newPair.first = i;
                        newPair.second = m;
                        listOfPairs.push_back(newPair);
                    }
                }
                if (!foundInSchemeArgs) {
                    schemeArgs.push_back(scheme1.at(i));
                }
            }
            for (unsigned i = 0; i < scheme2.getSize(); i++) {
                bool foundInSchemeArgs = false;
                for (unsigned k = 0; k < schemeArgs.size(); k++) {
                   if (scheme2.at(i) == schemeArgs[k]) {
                       foundInSchemeArgs = true;
                    }
                }
                if (!foundInSchemeArgs) {
                    schemeArgs.push_back(scheme2.at(i));
                }
            }
            Scheme newestScheme(schemeArgs);
            return newestScheme;
        }

};