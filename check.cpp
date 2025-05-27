#include<iostream>
#include<vector>
#include<list>
#include<bits/stdc++.h>
#include<iterator>
#include<cctype>
#include"modgraph.cpp"

using namespace std;

int matchPassword(string password, string candidatePass){
    return (password == candidatePass)? 1 : 0;
}

void checkExistence(Graph& graph){
    vector<list<pair<string, string>>> userNames(52);
    for(auto i : graph.Students){
        int ch = i.userName[0];
        int idx = (ch >= 65 && ch <= 90)? ch - 65 : ch - 97;
        userNames[idx].push_back({i.userName, i.password});
    }
    ifstream f("D:/DAA_project/QUERY.txt");
    ofstream output("D:/DAA_project/OUTPUT.txt");
    if(!f.is_open()){
        cout << "Error Opening File!!" << endl;
        return;
    }
    else{
        cout << "File opened successfully!!" << endl;
    }
    string line, password;
    getline(f, line);
    int ch = line[0];
    int idx = (ch >= 65 && ch <= 90)? ch - 65 : ch - 97;
    for(auto i : userNames[idx]){
        getline(f, password);
        if(i.first == line && matchPassword(password, i.second)){
            output << "0";
            return;
        }
    }
    output << "1";
}
int main(){
    Graph graph{};
    buildGraph(graph);
    checkExistence(graph);
}