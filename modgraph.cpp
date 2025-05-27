#include<iostream>
#include<vector>
#include<list>
#include<bits/stdc++.h>
#include<string>
#include<algorithm>
#include<cctype>
#include<unordered_map>
#include<iterator>
using namespace std;

unordered_map<string, int> propIdxs = {
    {"USERNAME", 1},
    {"NAME", 2},
    {"LEETCODERANK", 3},
    {"CGPA", 4},
    {"YEAR", 5},
    {"INTERESTS", 6},
    {"DOMAIN", 7},
    {"EXPERIENCE", 8},
    {"GOAL", 9},
    {"CONNECTIONS", 10},
    {"PASSWORD", 11}
};

unordered_map<int, string> idxtoProp = {
    {1, "USERNAME"},
    {2, "NAME"},
    {3, "LEETCODE RANK"},
    {4, "CGPA"},
    {5, "YEAR"},
    {6, "INTERESTS"},
    {7, "DOMAIN"},
    {8, "EXPERIENCE"},
    {9, "GOAL"},
    {10, "CONNECTIONS"},
    {11, "PASSWORD"}
};

class Student{
public:
    string userName;
    string name;
    string password;
    int leetcodeRank;
    double cgpa;
    int year;
    int edges;
    vector<string> interests;
    string domain;
    vector<string> exp;
    string goal;
    list<int> connections;

    Student(string userName, string name, string password, int leetcodeRank, double cgpa, int year, string domain, string goal, vector<string> interests, vector<string> experience){
        this->userName = userName;
        this->name = name;
        this->password = password;
        this->leetcodeRank = leetcodeRank;
        this->cgpa = cgpa;
        this->year = year;
        this->domain = domain;
        this->goal = goal;
        this->interests = interests;
        this->exp = experience;
        this->edges = 0;
    }
    void addEdge(int idx){
        this->connections.push_back(idx);
        cout << "Connection added successfully!!" << endl;
        (this->edges)++;
    }
};
class Graph{
public:
    vector<Student> Students;
    
    void addNode(string userName, string name, string password, int leetcodeRank, double cgpa, int year, string domain, string goal, vector<string> interest, vector<string> experience){
        Student newNode{userName, name, password, leetcodeRank, cgpa, year, domain, goal, interest, experience};
        Students.push_back(newNode);
    }
    void connect(int srcIdx, unordered_map<string, int>& Users, vector<vector<string>>& connections){
        cout << srcIdx << " ";
        for(int i = 0; i<connections[srcIdx].size(); i++){
            if(Users.find(connections[srcIdx][i]) != Users.end())    {
                int destIdx = Users[connections[srcIdx][i]];
                cout << destIdx << " ";
                this->Students[srcIdx].addEdge(destIdx);
                cout << "added!" <<endl;
            }
            else{
                cout << "ERROR!! NAME DOESN'T EXIST" << connections[srcIdx][i] << "." << endl;
            }
        }
        cout << endl;
    }
    void showProfile(int i){
        cout << "Profile " << i + 1 << endl;
        cout << "User Name : " << this->Students[i].userName;
        cout << "\tName : " << this->Students[i].name;
        cout << "\tLeetcode Rank : " << this->Students[i].leetcodeRank;
        cout << "\tC.G.P.A. : " << this->Students[i].cgpa;
        cout << "\tCurrent Year : " << this->Students[i].year << endl;
        cout << "\tCurrent Domain : " << this->Students[i].domain << endl;
        cout << "\tGoal : " << this->Students[i].goal << endl;
        cout << "\tInterests : " << endl;
        showIterProp(this->Students[i].interests);
        cout << "\tExperience : " << endl;
        showIterProp(this->Students[i].exp);
        cout << "Connections : " << endl;
        for(auto it : this->Students[i].connections){
            cout << " " << this->Students[it].name << endl;
        }
    }
    void show(){
        for(int i = 0; i<this->Students.size(); i++){
            cout << "Profile " << i + 1 << endl;
            cout << "\tUser Name : " << this->Students[i].userName << "." << endl;
            cout << "\tName : " << this->Students[i].name << "." << endl;
            cout << "\tPassword : " << this->Students[i].password << endl;
            cout << "\tLeetcode Rank : " << this->Students[i].leetcodeRank << "." << endl;
            cout << "\tC.G.P.A. : " << this->Students[i].cgpa << "." << endl;
            cout << "\tCurrent Year : " << this->Students[i].year << "." << endl;
            cout << "\tCurrent Domain : " << this->Students[i].domain << "." << endl;
            cout << "\tGoal : " << this->Students[i].goal << "." << endl;
            cout << "\tInterests : " << endl;
            showIterProp(this->Students[i].interests);
            cout << "\tExperience : " << endl;
            showIterProp(this->Students[i].exp);
            cout << "\tConnections : " << endl;
            for(auto it : this->Students[i].connections){
                cout << " " << this->Students[it].userName << "." << endl;
            }
        }
    }

    void showIterProp(vector<string>& iterProp){
        for(int i = 0; i<iterProp.size(); i++){
            cout << "\t\t" << iterProp[i] << "." << endl;
        }
    }
};

void extractInterests(vector<string>& interests, string line, int startIdx){
    string interest;
    for(int i = startIdx; i<line.length(); i++){
        if(line[i] == ','){
            interests.push_back(interest);
            interest.clear();
            i++;
        }
        interest+=line[i];
    }
}
void extractExperience(vector<string>& experiences, string line, int startIdx){
    string experience;
    for(int i = startIdx; i<line.length(); i++){
        if(line[i] == ','){
            experiences.push_back(experience);
            experience.clear();
            i++;
        }
        experience+=line[i];
    }
}
void extractConnections(vector<vector<string>>& connections, string line, int startIdx){
    cout << "StartIdx is : " << startIdx << endl;
    string connection; 
    vector<string> userConnections;
    for(int i = startIdx; i<line.length(); i++){
        if(line[i] == ','){
            cout << connection << endl; 
            userConnections.push_back(connection);
            connection.clear();
            i++;
            continue;
        }
        connection+=line[i];
    }
    connections.push_back(userConnections);
}
int property(string line){
    string prop;
    for(int i=0; i<line.length(); i++){
        if(line[i] == ':')
            break;
        prop+=line[i];
    }
    return propIdxs[prop];
}
void buildGraph(Graph& graph){
    int leetcodeRank, year, index = 0;
    double cgpa;
    unordered_map<string, int> Users;
    ifstream file("NEWINPUT.txt");

    if(!file.is_open()){
        cerr << "Error opening file!!" << endl;
    }


    string line, userName, name, goal, domain, password;
    vector<string> interests, experience;
    vector<vector<string>> connections;
    while(getline(file, line)){
        if(line == ""){
            graph.addNode(userName, name, password, leetcodeRank, cgpa, year, domain, goal, interests, experience);
            interests.clear();
            experience.clear();
            password.clear();
            index++;
            continue;
        }
        int propIdx = property(line);
        switch(propIdx){
            case 1 : userName = line.substr(idxtoProp[propIdx].length() + 2);
                Users.insert({userName, index});
                break;
            case 2 : name = line.substr(idxtoProp[propIdx].length() + 2); break;
            case 3 : leetcodeRank = stoi(line.substr(idxtoProp[propIdx].length() + 2)); break;
            case 4 : cgpa = stod(line.substr(idxtoProp[propIdx].length() + 2)); break;
            case 5 : year = stoi(line.substr(idxtoProp[propIdx].length() + 2)); break;
            case 6 : extractInterests(interests, line, idxtoProp[propIdx].length() + 2); break;
            case 7 : domain = line.substr(idxtoProp[propIdx].length() + 2); break;
            case 8 : extractExperience(experience, line, idxtoProp[propIdx].length() + 2); break;
            case 9 : goal = line.substr(idxtoProp[propIdx].length() + 2); break;
            case 10 : extractConnections(connections, line, idxtoProp[propIdx].length() + 2); break;
            case 11 : password = line.substr(idxtoProp[propIdx].length() + 2); break;
            default : cout << "Wrong property" << endl; break;
        }
    }
    cout << "Connections size are "  << connections.size() << endl;
    cout << "Map is : " << endl;
    for(auto it : Users){
        cout << it.first << " " << it.second << endl;
    }

    cout << "Connections vector is : " << endl;
    for(auto it : connections){
        for(auto iit : it){
            cout << "|" << iit << " ";
        }
        cout << endl;
    }
    cout << "Student graph size is : " << graph.Students.size() << endl;

    for(auto it : Users){
        int srcIdx = it.second;
        cout << "Src Idx is : " << srcIdx << endl;
        graph.connect(srcIdx, Users, connections);
    }
}

// int main(){
//     Graph graph{};
//     buildGraph(graph);
//     graph.show();
// }