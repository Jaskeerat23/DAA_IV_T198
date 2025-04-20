/*
TASK ASSIGNED TO : ADARSH
THE MAIN FUNCTION OF graph.cpp IS COMMENTED OUT SO IT CAN BE RUN FROM ANY WHERE SO 
JUST WRITE THE LOGIC FOR BFS, TEST IT, COMMIT AND PUSH THE FILE!

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

class BFS{
public:
    void bfs(Graph& g){
        vector<Node> graph=g.graph;
        for(int i=0;i<graph.size();i++)
        {
            queue<int> q;
            vector<bool> visited(graph.size(),false);
            cout<<"\n\nNode : ";
            if(!graph[i].EdgeList.empty())
            {
                q.push(i);
                visited[i]=true;
                while(!q.empty())
                {
                    int node_idx=q.front();
                    cout <<graph[node_idx].name<<"--->";
                    q.pop();
                    for(int idx : graph[node_idx].EdgeList)
                    {
                        if(!visited[idx])
                        {
                            q.push(idx);
                            visited[idx]=true;
                        }
                    }
                }
            }
        }
    }
};


int main() {
    Graph graph{};
    Build_graph(graph);
    graph.show();
    BFS obj;
    obj.bfs(graph);
}