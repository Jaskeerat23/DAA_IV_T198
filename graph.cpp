#include"graph.h"
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<cctype>
#include<bits/stdc++.h>
using namespace std;

/*This class Node represent Student with members:
1.) USERNAME
2.) NAME
3.) LEETCODE RANK
4.) CGPA
5.) INTERESTS
6.) CONNECTIONS COUNTS
7.) LIST REPRESNTING CONNECTIONS
*/
Node :: Node(string userName, string name, long leetcode_rank, float cgpa, vector<string> interests) { 
    this->connections = 0;
    transform(name.begin(), name.end(), name.begin(),::tolower);
    this->userName = userName;
    this->name = name;
    this->leetcode_rank = leetcode_rank;
    this->cgpa = cgpa;
    this->interests = interests;
}
void Node :: makeConnection(int idx){
    this->EdgeList.push_back(idx);
    (this->connections)++;
}


void Graph :: addNode(string userName, string name, long leetcode_rank, float cgpa, vector<string>& interests){
    Node newNode(userName, name, leetcode_rank, cgpa, interests);
    this->graph.push_back(newNode);
}
void Graph :: addEdge(string src, string dest){
    int srcIdx=-1, destIdx=-1, idx=0;
    transform(src.begin(), src.end(), src.begin(), ::tolower);
    transform(dest.begin(), dest.end(), dest.begin(), ::tolower);
    for(auto i : graph){
        if(i.name == src)
            srcIdx = idx;
        else if(i.name == dest)
            destIdx = idx;
        idx++;
    }
    if(srcIdx == destIdx){
        // cout << srcIdx << " " << destIdx << endl;
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
void Graph :: show(){
    cout << "Profile " << 1 << " : " << endl;
    for(int i = 0; i<this->graph.size(); i++){
        cout << "Profile " << i + 1 << endl;
        cout << "\tName : " << this->graph[i].name << endl;
        cout << "\tUser_Name : " << this->graph[i].userName << endl;

        cout << "\tConnections : " << this->graph[i].connections << endl;
        cout << "\tConnections List : " << endl;
        for(auto j : this->graph[i].EdgeList){
            cout << "\t\t" << this->graph[j].name << endl; 
        }

        cout << "\tInterests : " << endl;
        for(auto j : this->graph[i].interests) {
            cout << "\t\t" << j << endl;
        }
    }
}

/*This function is a helper function that helps us 
to determine that the current LINE from INPUT.txt
refers to NAME, RANK, CGPA, INTERESTS or CONNECTIONS
of the current person 

This function returns a string "NAME", "CGPA", "LEETCODE_RANK", "INTERESTS", "CONNECTIONS"
*/
string get_property(string line, int& idx){
    for(int i = 0; i<line.length(); i++){
        if(line[i] == ':'){
            idx = i;
            return line.substr(0, i);
        }
    }
}


void Build_graph(Graph& graph){
    ifstream f("D:/DAA_project/INPUTS.txt");
    string line, name, userName;
    long leetcode_rank;
    float cgpa;
    vector<string> interests, connections;
    if(!f.is_open()){
        cout << "Error Opening File!" << endl;
        return;
    }
    while(getline(f, line)){
        if(line == "" || line == "\n"){
            cout << name << endl;
            graph.addNode(userName, name, leetcode_rank, cgpa, interests);

            for(int i = 0; i<connections.size(); i++){
                graph.addEdge(name, connections[i]);
            }

            // Clearing the vector for next entry
            interests.clear();
            connections.clear();
            continue;
        }

        int idx = 0;
        string prop = get_property(line, idx);

        /*If current property is NAME then save the
        name of the Student in name variableclear

        */
        if(prop == "NAME"){
            name = line.substr(idx+2, line.length());
        }
        
        /*If current property is LEETCODE RANK then
        store that rank in 'leetcode_rank' variable by
        converting it to long datatype using C++ 
        in-built function 'stol'
        */
        else if(prop == "USERNAME"){
            userName = line.substr(idx+2, line.length());
            // cout << "userName is : " << userName << endl;
        }

        else if(prop == "LEETCODE RANK")
            leetcode_rank = stol(line.substr(idx+2, line.length()));
        
        /*If current property is CGPA then
        store that rank in 'cgpa' variable by
        converting it to float datatype using C++ 
        in-built function 'stof'
        */
        else if(prop == "CGPA")
            cgpa = stof(line.substr(idx+2, line.length()));
        
        /*If current property is INTERESTS then traverse
        over the current line and store each interest in a
        vector(STL container)
        */
        else if(prop == "INTERESTS"){
            for(int i = idx+2; i<line.length() + 1; i++){
                if(line[i] == ','){
                    string n = line.substr(idx+2, i - (idx+2));
                    interests.push_back(n);
                    idx = i;
                }
            }
        }
        
        /*If current property is CONNECTIONS then traverse
        over the current line and store each connection in a
        vector(STL container)
        */
        else if(prop == "CONNECTIONS"){
            for(int i = idx+2; i<line.length(); i++){
                if(line[i] == ','){
                    string n = line.substr(idx+2, i - (idx+2));
                    connections.push_back(n);
                    idx = i;
                }
            }
        }
        else{
            cout << "Wrong Property" << endl;
        }
        
    }
    f.close();
}
// int main(){
//     Graph graph{};
//     Build_graph(graph);
//     graph.show();
// }