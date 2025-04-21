/*
TASK ASSIGNED TO : YASH
THE MAIN FUNCTION OF graph.cpp IS COMMENTED OUT SO IT CAN BE RUN FROM ANY WHERE SO 
JUST WRITE THE LOGIC FOR DFS, TEST IT, COMMIT AND PUSH THE FILE!

BEST OF LUCK!!
*/

#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#include<iterator>
#include"graph.cpp"
using namespace std;

class DFS {
public:
    void dfs(Graph& graph) {
        string startName;
        cout << "\nEnter starting profile name for DFS traversal: ";
        getline(cin, startName);
        transform(startName.begin(), startName.end(), startName.begin(), ::tolower);

        int startIndex = -1;
        for (int i = 0; i < graph.graph.size(); i++) {
            if (graph.graph[i].name == startName) {
                startIndex = i;
                break;
            }
        }

        if (startIndex == -1) {
            cout << "Start profile not found!" << endl;
            return;
        }

        vector<bool> visited(graph.graph.size(), false);
        stack<int> s;

        s.push(startIndex);
        cout << "\nDFS Traversal starting from \"" << startName << "\": ";

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                visited[current] = true;
                cout << graph.graph[current].name << " -> ";

                for (auto it = graph.graph[current].EdgeList.rbegin(); it != graph.graph[current].EdgeList.rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }

        cout << "END" << endl;
    }
};

int main() {
    Graph graph{};
    Build_graph(graph);
    graph.show();
}
