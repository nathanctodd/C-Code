#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;

class Parser {
    
    private:
        vector<Token> tokenList;
        DatalogProgram datalogParsed;
        
    public:
        Parser(const vector<Token> tokens) {
            tokenList = tokens;
        }

        TokenType tokenType() const {
            return tokenList.at(0).getType();
        }

        DatalogProgram getDatalog() {
            return datalogParsed;
        }

        void advanceToken() {
            tokenList.erase(tokenList.begin());
        }

        void throwError(Token t) {
            cout << "Failure!" << endl << "  " << t.toString() << endl;
            exit(1);

            try {
                throw t;
            } catch (Token token) {
                cout << "Failure!" << endl << "  " << token.toString() << endl;
                exit(1);
            }
        }

        bool match(TokenType t) {
            //cout << "Match: " << t << endl;
            if (tokenType() == t) {
                advanceToken();
                while (tokenList.size() > 0 && tokenType() == COMMENT) {
                    advanceToken();
                }
                return true;        
            } else   {
                throwError(tokenList[0]);
                return false;
            }  

        }

        //0 - COMMA
        //1 - PERIOD
        //2 - Q_MARK
        //3 - LEFT_PAREN
        //4 - RIGHT_PAREN
        //5 - COLON
        //6 - COLON_DASH
        //7 - MULTIPLY
        //8 - ADD
        //9 - SCHEMES
        //10 - FACTS
        //11 - RULES
        //12 - QUERIES
        //13 - ID
        //14 - STRING
        //15 - COMMENT
        //16 - UNDEFINED
        //17 - EOF

      

        void parseDatalogProgram() {
                
            while (tokenList.size() > 0 && tokenType() == COMMENT) {
                advanceToken();
            }

            if (tokenType() == SCHEMES) {
                match(SCHEMES);
                match(COLON);
                scheme();
                schemeList();
                match(FACTS);
                match(COLON);
                factList();
                match(RULES);
                match(COLON);
                ruleList();
                match(QUERIES);
                match(COLON);
                query();
                queryList();
                match(ENDFILE);
            }

        }

        void schemeList() {
            if (tokenList[0].getType() == ID) {
                scheme();
                schemeList();
            } else {
                //Lambda
            }
        }

        void factList() {
            if (tokenList[0].getType() == ID) {
                fact();
                factList();
            } else {
                //Lambda
            }
        }

        void ruleList() {
            if (tokenList[0].getType() == ID) {
                rule();
                ruleList();
            } else {
                //Lambda
            }
        }

        void queryList() {
            if (tokenList[0].getType() == ID) {
                query();
                queryList();
            } else {
                //Lambda
            }
        }

        void scheme() {
            Predicate schemeObject;
            if (tokenType() == ID) {
                schemeObject.setName(tokenList[0].getValue());
                match(ID);
                match(LEFT_PAREN);
                vector<Parameter> addedParameters;
                Parameter firstParameter = tokenList[0].getValue();
                match(ID);
                addedParameters = idList(addedParameters);
                addedParameters.insert(addedParameters.begin(), firstParameter);
                match(RIGHT_PAREN);
                schemeObject.setVector(addedParameters);
                schemeObject.toString();
                datalogParsed.addToSchemes(schemeObject);
            } else {
                throwError(tokenList[0]);
            }
        }

        void fact() {
            Predicate factObject;
            if(tokenType() == ID) {
                factObject.setName(tokenList[0].getValue());
                match(ID);
                match(LEFT_PAREN);
                vector<Parameter> addedParameters;
                Parameter firstParameter = tokenList[0].getValue();
                match(STRING);
                addedParameters = stringList(addedParameters);
                addedParameters.insert(addedParameters.begin(), firstParameter);
                match(RIGHT_PAREN);
                match(PERIOD);
                factObject.setVector(addedParameters);
                datalogParsed.addToFacts(factObject);
            } else {
                throwError(tokenList[0]);
            }
        }

        void rule() {
            Rule ruleObject;
            if (tokenList[0].getType() == ID) {
                ruleObject.setHeadPredicate(headPredicate());
                match(COLON_DASH);
                Predicate firstPred = predicate();
                vector<Predicate> predicates;
                predicates = predicateList(predicates);
                predicates.insert(predicates.begin(), firstPred);
                match(PERIOD);
                ruleObject.setPredicateList(predicates);
                datalogParsed.addToRules(ruleObject);
            } else {
                throwError(tokenList[0]);
            }
        }

        void query() {
            Predicate queryObject;
            if (tokenList[0].getType() == ID) {
                queryObject = predicate();
                match(Q_MARK);
                datalogParsed.addToQueries(queryObject);
            } else {
                throwError(tokenList[0]);
            }         
        }


        Predicate headPredicate() {
            Predicate head;
            if (tokenType() == ID) {
                head.setName(tokenList[0].getValue());
                match(ID);
                match(LEFT_PAREN);
                vector<Parameter> paramList;
                Parameter firstParam = tokenList[0].getValue();
                match(ID);
                paramList = idList(paramList);
                paramList.insert(paramList.begin(), firstParam);
                match(RIGHT_PAREN);
                head.setVector(paramList);
                return head;
            }
            Predicate pred;
            return pred;
        }

        Predicate predicate() {
            Predicate addedPredicate;
            if (tokenType() == ID) {
                addedPredicate.setName(tokenList[0].getValue());
                match(ID);
                match(LEFT_PAREN);
                Parameter newParam = parameter();
                vector <Parameter> parameterList2;
                parameterList2 = parameterList(parameterList2);
                parameterList2.insert(parameterList2.begin(), newParam);
                match(RIGHT_PAREN);
                addedPredicate.setVector(parameterList2);
                return addedPredicate;
            }
            return addedPredicate;
        }


        vector<Predicate> predicateList(vector<Predicate> list) {
            if (tokenType() == COMMA) {
                match(COMMA);
                list.push_back(predicate());
                return predicateList(list);
            } else {
                //Lambda
                return list;         
            }
            return list;
        }


        vector<Parameter> parameterList(vector<Parameter> list) {
            if(tokenType() == COMMA) {
                match(COMMA);
                Parameter listItem(tokenList[0].getValue());
                list.push_back(parameter());
                return parameterList(list);
            } else {
                //Lambda
                return list;
            }
            return list;      
        }


        vector<Parameter> stringList(vector<Parameter> list) {
            if (tokenType() == COMMA) {
                match(COMMA);
                Parameter listItem(tokenList[0].getValue());
                list.push_back(listItem);
                match(STRING);
                return stringList(list);
            } else {
                //Lambda
                return list;
            }
            return list;
        }


        vector<Parameter> idList(vector<Parameter> list) {
            if (tokenType() == COMMA) {
                match(COMMA);
                Parameter listItem(tokenList[0].getValue());
                list.push_back(listItem);
                match(ID);
                list = idList(list);
                return list;
            } else {
                //Lambda
                return list;
            }
            return list;
        }


        Parameter parameter() {
            if (tokenType() == STRING) {
                Parameter param = tokenList[0].getValue();
                match(STRING);
                return param;
            } else {
                Parameter param = tokenList[0].getValue();
                match (ID);
                return param;
            }
        }
        




};