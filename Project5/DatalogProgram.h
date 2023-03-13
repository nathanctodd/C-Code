#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Predicate.h"
#include "Token.h"
#include "Rule.h"
#include <set>

using namespace std;


class DatalogProgram {

private:
    vector<Predicate> schemeList;
    vector<Predicate> factList;
    vector<Rule> ruleList;
    vector<Predicate> queryList;
    set<string> domainList;

public:
    DatalogProgram() {

    }

    void addToSchemes(Predicate newPredicate) {
        schemeList.push_back(newPredicate);
    }
    void addToFacts(Predicate newPredicate) {
        factList.push_back(newPredicate);
        for (unsigned int i = 0; i < newPredicate.getVector().size(); i++) {
            domainList.insert(newPredicate.getVector()[i].toString());
        }
    }
    void addToRules(Rule newRule) {
        ruleList.push_back(newRule);
    }
    void addToQueries(Predicate newPredicate) {
        queryList.push_back(newPredicate);
    }

    void addToSet(string addedString) {
        domainList.insert(addedString);
    }

    vector<Predicate> getSchemeList() {
        return schemeList;
    }
    vector<Predicate> getFactList() {
        return factList;
    }
    vector<Rule> getRuleList() {
        return ruleList;
    }
    vector<Predicate> getQueryList() {
        return queryList;
    }
    set<string> getDomainList() {
        return domainList;
    }


    string toString() {
        stringstream output;
        output << "Success!" << endl;
        output << "Schemes(" << schemeList.size() << "):" << endl;
        for (unsigned int i = 0; i < schemeList.size(); i++) {
            output << "  " << schemeList[i].toString() << endl;
        }
        output << "Facts(" << factList.size() << "):" << endl;
        for (unsigned int i = 0; i < factList.size(); i++) {
            output << "  " << factList[i].toString() << "." << endl;
        }
        output << "Rules(" << ruleList.size() << "):" << endl;
        for (unsigned int i = 0; i < ruleList.size(); i++) {
            output << "  " << ruleList[i].toString() << "." << endl;
        }
        output << "Queries(" << queryList.size() << "):" << endl;
        for (unsigned int i = 0; i < queryList.size(); i++) {
            output << "  " << queryList[i].toString() << "?" << endl;
        }
        output << "Domain(" << domainList.size() << "):" << endl;
        set<string>::iterator it = domainList.begin();
        while (it != domainList.end()) {
            output << "  " << (*it) << endl;
            it++;
        }
        return output.str();
    }



};