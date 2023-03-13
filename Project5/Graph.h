#pragma once
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"

using namespace std;

class Graph {

    private:
        map<int, Node> nodes;
        int postOrderIndex;
        vector<int> postOrderVector; 
        set<int> scc;
        vector< set<int> > sccs;


    public:

        Graph(int size) {
            for (int nodeID = 0; nodeID < size; nodeID++) {
                nodes[nodeID] = Node(nodeID);
            }
            postOrderIndex = 0;
        }

        Graph(map<int, Node> inputNodes) {
            nodes = inputNodes;
            postOrderIndex = 0;
        }

        void addEdge(int fromNodeID, int toNodeID) {
            nodes[fromNodeID].addEdge(toNodeID);
        }

        vector< set<int> > getSCCs() {
            return sccs;
        }

        Node findNode(int index) {
            return nodes[index];
        }

        string toString() {
            stringstream out;
            map<int, Node>::iterator itr;
            for (itr = nodes.begin(); itr != nodes.end(); itr++) {
                int nodeID = (*itr).first;
                Node node = (*itr).second;
                out << "R" << nodeID << ":" << node.toString() << endl;
            }
            return out.str();

        }

        Graph reverseGraph() {
            Graph returnableGraph(nodes.size());
            for (long unsigned i = 0; i < nodes.size(); i++) {
                set<int> adjacentNodes = nodes[i].returnAdjacentNodes();
                set<int>::iterator itr;
                for (itr = adjacentNodes.begin(); itr != adjacentNodes.end(); itr++) {
                    returnableGraph.addEdge((*itr), i);
                }
            }
            return returnableGraph;
        }



        vector<int> reverseOrder () {
            vector<int> returnable;
            for (int i = postOrderVector.size() - 1; i >= 0; i--) {
                returnable.push_back(postOrderVector[i]);
            }
            return returnable;
        }

        void DepthFirstSearch() {
            postOrderIndex = 0;
            for (long unsigned i = 0; i < nodes.size(); i++) {
                if (!nodes[i].hasBeenVisited() ){
                    dfs(nodes[i]);
                }
            }
        }

        void dfs (Node& x) {
            x.setVisited(true);
            set<int> adjacent = x.returnAdjacentNodes();
            set<int>::iterator itr;
            for (itr = adjacent.begin(); itr != adjacent.end(); itr++) {
                if (!nodes[(*itr)].hasBeenVisited()) {
                    dfs(nodes[(*itr)]);
                }
            }
            postOrderVector.push_back(x.getID());
        }

        void sccFunc(Node& x) {
            x.setVisited(true);
            set<int> adjacent = x.returnAdjacentNodes();
            set<int>::iterator itr;
            for (itr = adjacent.begin(); itr != adjacent.end(); itr++) {
               if (!nodes[(*itr)].hasBeenVisited()) {
                   sccFunc(nodes[(*itr)]);
               }
            }
            scc.insert(x.getID());
        }

        void getSCCs(vector<int> reverse) {
            for (long unsigned i = 0; i < reverse.size(); i++) {
                scc.clear();
                if (!nodes[reverse[i]].hasBeenVisited()) {
                    sccFunc(nodes[reverse[i]]);
                } else {
                    continue;
                }
                sccs.push_back(scc);
            }
        }




    /*
 nodes[x].setVisited(true);
            cout << nodes[x].toString() << " has been visited." << endl;
            set<int> adjacent = nodes[x].returnAdjacentNodes();
            set<int>::iterator itr;
            for (itr = adjacent.begin(); itr != adjacent.end(); itr++) {
                cout << "Checking node " << (*itr) << endl;
                if (!nodes[(*itr)].hasBeenVisited()) {
                    dfs(nodes[(*itr)]);
                }
            }
            cout << "This is the currentPostOrder: " << postOrderIndex << endl;
            nodes[x].setPostOrderNumber(postOrderIndex);
            postOrderIndex++;
    */
       

};