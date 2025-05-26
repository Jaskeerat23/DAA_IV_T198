#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Student {
    string userName;
    string name;
    int leetcodeRank;
    float cgpa;
    int year;
    vector<string> experiences;
    float score = 0.0;
};

vector<string> splitByComma(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, ',')) {
        if (!item.empty() && item[0] == ' ') item.erase(0, 1);
        if (!item.empty())
            result.push_back(item);
    }
    return result;
}

float computeScore(float cgpa, int year, int leetcodeRank, int expCount) {
    float cgpaScore = cgpa / 10.0f;
    float yearScore = year / 4.0f;
    float rankScore = 1.0f - min(1.0f, leetcodeRank / 100000.0f); // Better rank = higher score
    float expScore = min(1.0f, expCount / 5.0f); // Cap at 5 experiences

    return 1000*(0.3 * cgpaScore + 0.2 * yearScore + 0.3 * rankScore + 0.2 * expScore);
}

int main() {
    ifstream infile("NEWINPUT.txt");
    ofstream outfile("outputs.txt");

    if (!infile) {
        cerr << "Error: Could not open NEWINPUTS.txt\n";
        return 1;
    }

    if (!outfile) {
        cerr << "Error: Could not create outputs.txt\n";
        return 1;
    }

    vector<Student> students;
    string line;
    Student current;

    while (getline(infile, line)) {
        if (line.empty()) {
            current.score = computeScore(current.cgpa, current.year, current.leetcodeRank, current.experiences.size());
            students.push_back(current);
            current = Student();  // Reset
            continue;
        }

        size_t pos = line.find(": ");
        if (pos == string::npos) continue;
        string key = line.substr(0, pos);
        string value = line.substr(pos + 2);

        if (key == "USERNAME") current.userName = value;
        else if (key == "NAME") current.name = value;
        else if (key == "LEETCODERANK") current.leetcodeRank = stoi(value);
        else if (key == "CGPA") current.cgpa = stof(value);
        else if (key == "YEAR") current.year = stoi(value);
        else if (key == "EXPERIENCE") current.experiences = splitByComma(value);
    }

    // If last user wasn't added
    if (!current.userName.empty()) {
        current.score = computeScore(current.cgpa, current.year, current.leetcodeRank, current.experiences.size());
        students.push_back(current);
    }

    // Print and write output
    for (const auto& s : students) {
        cout << s.userName << " -> " << s.score << "\n";
        outfile << s.userName << "-" << s.score << "\n";
    }

    infile.close();
    outfile.close();
    return 0;
}
