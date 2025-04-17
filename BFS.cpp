#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#include<iterator>
#include"graph.cpp"
using namespace std;

int main() {
    Graph graph{};
    Build_graph(graph);
    graph.show();
}