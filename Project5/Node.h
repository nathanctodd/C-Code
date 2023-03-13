#pragma once
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>

using namespace std;

class Node {

    private:
        int id;
        set<int> adjacentNodeIDs;
        bool beenVisited;
        int postOrderNumber;

    public:

    Node() {
    }
    Node(int setID) {
        id = setID;
    }

    Node(set<int> adjacentNodes, bool been, int post) {
        adjacentNodeIDs = adjacentNodes;
        beenVisited = been;
        postOrderNumber = post;
    }

    set<int> returnAdjacentNodes() {
        return adjacentNodeIDs;
    }

    int getID() {
        return id;
    }

    void setID(int ident) {
        id = ident;
    }

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID); 
    }

    bool hasBeenVisited() {
        return beenVisited;
    }

    void setVisited(bool visited) {
        beenVisited = visited;
    }

    void setPostOrderNumber(int num) {
        postOrderNumber = num;
    }

    int getPostOrderNumber() {
        return postOrderNumber;
    }

   

    string toString() {
        stringstream out;
        set<int>::iterator itr;
        for (itr = adjacentNodeIDs.begin(); itr != adjacentNodeIDs.end(); itr++) {
            if (itr == adjacentNodeIDs.begin()) {
                out << "R" << (*itr);
            } else {
                out << ",R" << (*itr);
            }
        }   
        return out.str();
    }

};