#include<iostream>
#include<vector>
#include<list>
#include<bits/stdc++.h>
#include<iterator>
#include<cctype>
#include"graph.h"

using namespace std;
void checkExistence(Graph& graph){
    vector<list<string>> userNames(52);
    for(auto i : graph.graph){
        int ch = i.userName[0];
        int idx = (ch >= 65 && ch <= 90)? ch - 65 : ch - 97;
        userNames[idx].push_back(i.userName);
        cout << userNames[idx].back() << "." << endl;
    }
    ifstream f("D:/DAA_project/CHECK.txt");
    ofstream output("D:/DAA_project/OUTPUT.txt");
    if(!f.is_open()){
        cout << "Error Opening File!!" << endl;
        return;
    }
    string line;
    getline(f, line);
    int ch = line[0];
    int idx = (ch >= 65 && ch <= 90)? ch - 65 : ch - 97;
    for(auto i : userNames[idx]){
        if(i == line){
            output << "0";
            return;
        }
    }
    output << "1";
}
int main(){
    Graph graph{};
    Build_graph(graph);
    checkExistence(graph);
}