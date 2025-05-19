#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#include<iterator>
#include"graph.cpp"
using namespace std;


int getNodeIndexByUserName(vector<Node>& graph,const string& userName) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].userName == userName) return i;
    }
    return -1;
}

void recommendUser(vector<Node>& graph,const string& userUserName) {
    int srcIdx = getNodeIndexByUserName(graph,userUserName);
    if (srcIdx == -1) {
        cout << "User not found.\n";
        return;
    }

    float alpha = 0.5, beta = 0.5;
    float bestScore = -1.0;
    int bestIdx = -1;

    float cgpa_threshold = 0.1;
    long rank_threshold = 100;

    Node& src = graph[srcIdx];

    for (int i = 0; i < graph.size(); i++) {
        if (i == srcIdx) continue;

        

        Node& candidate = graph[i];

        // Applying threshold criteria
        if (candidate.cgpa < src.cgpa + cgpa_threshold) continue;
        if (candidate.leetcode_rank > src.leetcode_rank - rank_threshold) continue;

        //calculating similarity by assuming max leetcode_rank is 100000
        float cgpaSim = 1.0 - abs(src.cgpa - candidate.cgpa) / 10.0;
        float rankSim = 1.0 - abs(src.leetcode_rank - candidate.leetcode_rank) / 10000.0;

        float score = alpha * cgpaSim + beta * rankSim;

        if (score > bestScore) {
            bestScore = score;
            bestIdx = i;
        }
    }

    if (bestIdx != -1) {
        cout << "\nRecommended user for " << src.name << " (" << src.userName << ") is:\n";
        cout << "\tName: " << graph[bestIdx].name << "\n";
        cout << "\tUsername: " << graph[bestIdx].userName << "\n";
        cout << "\tCGPA: " << graph[bestIdx].cgpa << "\n";
        cout << "\tLeetcode Rank: " << graph[bestIdx].leetcode_rank << "\n";
    } else {
        cout << "\nNo suitable recommendation found, no one significantly better found.\n";
    }
}
int main() {
    Graph graph{};
    Build_graph(graph);
    recommendUser(graph.graph,"yash_rana93");
}