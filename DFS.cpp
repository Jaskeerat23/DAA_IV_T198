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
    vector<bool> visited;

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

        visited.assign(graph.graph.size(), false); 
        cout << "\nDFS Traversal starting from \"" << startName << "\": ";
        dfsRecursive(graph, startIndex);
        cout << "END" << endl;
    }

private:
    void dfsRecursive(Graph& graph, int idx) {
        visited[idx] = true;
        cout << graph.graph[idx].name << " -> ";

        for (int neighbor : graph.graph[idx].EdgeList) {
            if (!visited[neighbor]) {
                dfsRecursive(graph, neighbor);
            }
        }
    }
};

int main() {
    Graph graph{};
    Build_graph(graph);
    graph.show();
}
