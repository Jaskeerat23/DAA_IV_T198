#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "modgraph.cpp"
using namespace std;

int getNodeIndexByUserName(vector<Student>& graph, const string& userName) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].userName == userName) return i;
    }
    return -1;
}

void recommendUserAcademic(vector<Student>& graph, const string& userName, bool cgpa_constraint = true, bool year_constraint = true) {
    int srcIdx = getNodeIndexByUserName(graph, userName);
    if (srcIdx == -1) {
        cout << "User not found.\n";
        return;
    }

    float cgpa_threshold = 0.5;
    int bestIdx = -1;
    float bestCgpa = -1.0;

    Student& src = graph[srcIdx];

    for (int i = 0; i < graph.size(); i++) {
        if (i == srcIdx)
            continue;

        Student& candidate = graph[i];

        // Skip if year constraint is active and candidate is not senior
        if (year_constraint && candidate.year <= src.year)
            continue;

        // Skip if cgpa constraint is active and candidate is not better performing
        if (cgpa_constraint && candidate.cgpa < src.cgpa + cgpa_threshold)
            continue;

        if (candidate.cgpa > bestCgpa) {
            bestCgpa = candidate.cgpa;
            bestIdx = i;
        }
    }

    if (bestIdx != -1) {
        cout << "\nRecommended user for " << src.name << " (" << src.userName << ") based on academics:\n";
        cout << "\tName: " << graph[bestIdx].name << "\n";
        cout << "\tUsername: " << graph[bestIdx].userName << "\n";
        cout << "\tCGPA: " << graph[bestIdx].cgpa << "\n";
        cout << "\tYear: " << graph[bestIdx].year << "\n";
    } else if (cgpa_constraint) {
        // Retry without CGPA constraint
        recommendUserAcademic(graph, userName, false, year_constraint);
    } else if (year_constraint) {
        // Retry allowing same-year students
        recommendUserAcademic(graph, userName, false, false);
    } else {
        cout << "\nNo suitable academic recommendation found.\n";
    }
}


void recommendUserSkills(vector<Student>& graph, const string& userName) {
    int srcIdx = getNodeIndexByUserName(graph, userName);
    if (srcIdx == -1) {
        cout << "User not found.\n";
        return;
    }

    float bestScore = -1.0;
    int bestIdx = -1;
    float rank_threshold = 100.0;

    Student& src = graph[srcIdx];

    for (int i = 0; i < graph.size(); i++) {
        if (i == srcIdx) continue;

        Student& candidate = graph[i];

        if (candidate.leetcodeRank > src.leetcodeRank - rank_threshold)
            continue;

        // Match source interests with candidate domain
        bool domainMatch = false;
        for (string& interest : src.interests) {
            if (candidate.domain.find(interest) != string::npos) {
                domainMatch = true;
                break;
            }
        }

        // Match candidate exp with source interest
        bool expMatch = false;
        for (string& exp : candidate.exp) {
            for (string& interest : src.interests) {
                if (exp.find(interest) != string::npos) {
                    expMatch = true;
                    break;
                }
            }
            if (expMatch) break;
        }

        if (!expMatch && !domainMatch) continue;

        float score = 1.0 - abs(src.leetcodeRank - candidate.leetcodeRank) / 100000.0;

        if (score > bestScore) {
            bestScore = score;
            bestIdx = i;
        }
    }

    if (bestIdx != -1) {
        cout << "\nRecommended user for " << src.name << " (" << src.userName << ") based on skills:\n";
        cout << "\tName: " << graph[bestIdx].name << "\n";
        cout << "\tUsername: " << graph[bestIdx].userName << "\n";
        cout << "\tLeetcode Rank: " << graph[bestIdx].leetcodeRank << "\n";
        cout << "\tDomain: " << graph[bestIdx].domain << "\n";
        cout << "\tExperience: ";
        for (auto& exp : graph[bestIdx].exp) cout << exp << ", ";
        cout << "\n";
    } else {
        cout << "\nNo suitable recommendation found based on skills.\n";
    }
}

int main() {
    Graph graph;
    buildGraph(graph);

    string user = "user12"; // change this to test other users

    recommendUserAcademic(graph.Students, user);
    recommendUserSkills(graph.Students, user);

    return 0;
}
