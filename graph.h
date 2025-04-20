#ifndef GRAPH_H
#define GRAPH_H

#include<vector>
#include<string>
#include<list>

using namespace std;

class Node{
public:
    string name;
    int connections;
    long leetcode_rank;
    float cgpa;
    list<int> EdgeList;
    vector<string> interests;
    Node(string name, long leetcode_rank, float cgpa, vector<string> interests);
    void makeConnection(int idx);
};

class Graph{
public:
    vector<Node> graph;
    void addNode(string name, long leetcode_rank, float cgpa, vector<string>& interests);
    void addEdge(string src, string dest);
    void show();
};

string get_property(string line, int& idx);
void Build_graph(Graph& graph);

#endif