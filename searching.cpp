/*
TASK ASSIGNED TO : ADITYA

THE TASK IS TO CREATE A VECTOR OF NODES AND THEN APPLY AN ALGORITHM FOR SEARCHING SUCH THAT
WHEN A USER SEARCH FOR ANOTHER USER THEN THE RECOMMENDATIONS WILL BE BASED ON PARAMETERS:
    LEETCODE RANK
    CGPA
    INTERESTS

COME UP WITH SUCH AN ALGORITHM , YOUR CREATIVITY WILL BE APPRECIATED!!

HINTS : 
    USE Build_graph function from the graph.cpp and then use that graph to apply searching!! since graph is like:

    [ student_1, student_2, student_3, student_4..........]

    and each student have parameters mentioned above

    GRAPH HAVE ALREADY BEEN BUILT FOR YOU JUST RUN THIS FILE BY TYPING COMMAND:

    g++ .\searching.cpp
    .\a.exe

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
    void bfs(Graph& graph){

    }
};

int main() {
    Graph graph{};
    Build_graph(graph);
    graph.show();
}