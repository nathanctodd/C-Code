#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include "DatalogProgram.h"
#include "Relation.h"
#include "Rule.h"

using namespace std;


class Database {

    private:
        DatalogProgram data;
        vector<Relation> relations;
        bool moreThanOne;

    public:

        Database(DatalogProgram dataInput, vector<Relation> relationInput) {
            data = dataInput;
            relations = relationInput;
        }  

        void evaluateSchemes() {
            vector<Predicate> schemes = data.getSchemeList();
            for (unsigned i = 0; i < schemes.size(); i++) {
                string name = schemes[i].getName();
                vector<string> inputNames;
                inputNames = schemes[i].getStringVector();
                Relation newestRelation(name, inputNames);
                relations.push_back(newestRelation);
            }
        }

        void evaluateFacts() {
            vector<Predicate> facts = data.getFactList();
            for (unsigned i = 0; i < facts.size(); i++) {
                string name = facts[i].getName();
                vector<string> inputFact;
                inputFact = facts[i].getStringVector();
                Tuple newestTuple(inputFact);
                for (unsigned k = 0; k < relations.size(); k++ ) {
                    if (name == relations[k].getName()) {
                        relations[k].addTuple(newestTuple);
                    }
                }
            }
        }

        int getRelationSize(Relation rel) {
            int count = 0;
            for (int i = 0; i < rel.getNumberTuples(); i++) {
                count++;
            }
            return count;
        }

        int getAllRelationSize() {
            int count = 0;
            for (unsigned i = 0; i < relations.size(); i++) {
                count = count + getRelationSize(relations[i]);
            }
            return count;
        }

        void evaluateAllRules() {
            cout << "Rule Evaluation" << endl;
            vector<Rule> rules = data.getRuleList();
            int preValue = -1;
            int postValue = 0;
            int totalCount = 0;
            while (preValue != postValue) {
                preValue = getAllRelationSize();
                for (unsigned i = 0; i < rules.size(); i++) {
                    evaluateRule(rules[i]);
                    //cout << "PREVALUE: " << preValue << "  POSTVALUE: " << postValue << endl;
                    //cout << getAllRelationSize();
                }
                totalCount++;
                postValue = getAllRelationSize();
                //cout << "PREVALUE: " << preValue << "  POSTVALUE: " << postValue << endl;
            }
            cout << endl << "Schemes populated after " << totalCount << " passes through the Rules." << endl << endl;
            //printAllRelations();
        }

        void printAllRelations() {
            for (unsigned i = 0; i < relations.size(); i++) {
                cout << "Relation Name: " << relations[i].getName() << endl;
                cout << relations[i].toString();
                cout << endl;
            }
        }

        void evaluateRule(Rule rule) {

            vector<Relation> relationVector;
            for (int i = 0; i < rule.getPredicateSize(); i++) {
                Relation newRelation = evaluatePredicate(rule.getPredicateList()[i]);
                relationVector.push_back(newRelation);
            }
            Relation joinRelation = relationVector[0];
            for (unsigned i = 1; i < relationVector.size(); i++) {
                joinRelation = joinRelation.join(relationVector[i]);
            }

            joinRelation.setName(rule.getHeadPredicate().getName());
            vector<int> indexes = findColumns(rule.getHeadPredicate(), joinRelation);
            joinRelation = joinRelation.project(indexes);



            //RENAME GOES HERE
            stringstream out;
            for (unsigned i = 0; i < relations.size(); i++) {
                if (relations[i].getName() == joinRelation.getName()) {
                    joinRelation.rename(relations[i].getScheme().getNames());
                    set<Tuple> newSet = joinRelation.getTupleSet();
                    set<Tuple>::iterator itr;
                    for (itr = newSet.begin(); itr != newSet.end(); itr++) {
                        bool alrightThen = relations[i].addTuple((*itr));

                        if (alrightThen) {
                            out << "  " << (*itr).toString(relations[i].getScheme()) << endl;
                        }
                    }
                }
            }

            cout << rule.toString() << endl;
            cout << out.str();
        }

        vector<int> findColumns(Predicate headPredicate, Relation secondRelation) {

            vector<string> predicateParams = headPredicate.getStringVector();
            Scheme newestScheme = secondRelation.getScheme();
            vector<int> indexVector;
            for (unsigned i = 0; i < predicateParams.size(); i++) {
                for (unsigned j = 0; j < newestScheme.getSize(); j++) {
                    string str1 = predicateParams[i];
                    string str2 = newestScheme.at(j);
                    // std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
                    // std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
                    if (str1 == str2 ) {
                        indexVector.push_back(j);
                    }
                }
            }
            return indexVector;
        }

    
        Relation evaluatePredicate(Predicate pred) {
            string schemeName = pred.getName();
                for (unsigned k = 0; k < relations.size(); k++) {
                    if (schemeName == relations[k].getName()) {
                        vector<Parameter> parameters = pred.getVector();
                        Relation newRelation = relations[k];
                        vector<int> projectionIndexes;
                        vector<string> newNames;
                        moreThanOne = false;
                        map <string, int> constants;
                        for (unsigned p = 0; p < pred.getVector().size(); p ++) {
                            char newChar = '\'';
                            if (parameters[p].toString().at(0) == newChar) {
                                newRelation = newRelation.select(p, parameters[p].toString());
                            } else {
                                bool found = false;
                                map<string, int>::iterator itr;
                                for (itr = constants.begin(); itr != constants.end(); itr++) {
                                    if (parameters[p].toString() == itr->first) {
                                        found = true;
                                        newRelation = newRelation.select(p, itr->second);
                                    }
                                }
                                if (found == false) {
                                    projectionIndexes.push_back(p);
                                    newNames.push_back(parameters[p].toString());
                                    constants.insert(pair<string, int>(parameters[p].toString(), p));
                                    moreThanOne = true;
                                }
                            }
                        }
                        newRelation = newRelation.project(projectionIndexes);
                        newRelation = newRelation.rename(newNames);
                        return newRelation;
                    }
                }
            return Relation();
        }

        void evaluateQueries() {
            cout << "Query Evaluation" << endl;
            vector<Predicate> queries = data.getQueryList();
            for (unsigned i = 0; i < queries.size(); i++) {
                Relation newRelation = evaluatePredicate(queries[i]);
                printOutQuery(newRelation, queries[i], moreThanOne);
            }
        }

         void printOutQuery(Relation relate, Predicate localQuery, bool moreThanOne) {
            if (relate.getNumberTuples() == 0) {
                cout << localQuery.toString() << "? " << "No" << endl;
            } else {
                cout << localQuery.toString() << "? "  << "Yes(" << relate.getNumberTuples() << ")" << endl;
                if (moreThanOne)
                    cout << relate.toString();
            }
        }


};