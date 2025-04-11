#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<cctype>
using namespace std;
class Node{
public:
    string name;
    list<int> EdgeList;
    int Edges;
    Node(string name) { 
        this->Edges = 0;
        transform(name.begin(), name.end(), name.begin(),::tolower); 
        this->name = name;
    }
    void makeConnection(int idx){
        this->EdgeList.push_back(idx);
        (this->Edges)++;
    }
};
class Graph{
public:
    vector<Node> graph;
    void addNode(string name){
        Node newNode(name);
        this->graph.push_back(newNode);
    }
    void addEdge(string src, string dest){
        int srcIdx=-1, destIdx=-1, idx=0;
        for(auto i : graph){
            if(i.name == src)
                srcIdx = idx;
            else if(i.name == dest)
                destIdx = idx;
            idx++;
        }
        if(srcIdx == destIdx){
            cout << "Not possible to connect same node with each other" << endl;
            return;
        }
        else if(srcIdx==-1 || destIdx==-1){
            cout << "Either of the source or destination not found!!" << endl;
            return;
        }
        this->graph[srcIdx].makeConnection(destIdx);
        this->graph[destIdx].makeConnection(srcIdx);
    }
    void show(){
        for(int i = 0; i<this->graph.size(); i++){
            cout << this->graph[i].name;
            for(auto j : this->graph[i].EdgeList){
                cout << "->" << this->graph[j].name; 
            }
            cout << endl;
        }
    }
};
int main(){
    Graph graph{};
    graph.addNode("Jaskeerat Singh");
    graph.addNode("Adarsh Chaube");
    graph.addNode("Yash Rana");
    graph.addNode("Aditya Sharma");
    graph.addEdge("jaskeerat singh", "adarsh chaube");
    graph.addEdge("jaskeerat singh", "yash rana");
    graph.addEdge("yash rana", "adarsh chaube");
    graph.show();
}