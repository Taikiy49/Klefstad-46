#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>
using namespace std;
#include "graph.h"

void error(string msg){ cout << "ERROR: " << msg << endl; }

DisjointSet::DisjointSet(int numVertices){
    subsets.resize(numVertices);
    for (Vertex i = 0; i < numVertices; ++i){ subsets[i].parent = i; }
}

void DisjointSet::makeSet(Vertex x){ subsets[x].parent = x; }

Vertex DisjointSet::findSet(Vertex x){
    if (subsets[x].parent != x) subsets[x].parent = findSet(subsets[x].parent);
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y){
    Vertex xRoot = findSet(x);
    Vertex yRoot = findSet(y);
    if (xRoot == yRoot) return;
    subsets[yRoot].parent = xRoot;
}

////

Graph Graph::sort_edges() const{
    Graph sortedGraph(*this);
    std::sort(sortedGraph.begin(), sortedGraph.end(), [](const Edge & a, const Edge & b){ return a.weight < b.weight; });
    return sortedGraph;
}

VertexList Graph::edges_from(Vertex vertex) const{
    VertexList edges;
    for (const Edge & edge : *this){
        if (edge.u == vertex) edges.push_back(edge.v);}
    return edges;
}

////

EdgeList Kruskals(const Graph & G){
    DisjointSet ds{G.numVertices};
    const Graph & sorted_edges = G.sort_edges();
    size_t solution_size = G.numVertices - 1;
    EdgeList result;

    for (Edge e : sorted_edges){
        Vertex uRoot = ds.findSet(e.u);
        Vertex vRoot = ds.findSet(e.v);

        if (uRoot != vRoot){
            ds.unionSets(uRoot, vRoot);
            result.push_back(e);
            if (result.size() >= solution_size) break;
        }
    }
    return result;
}

int sum_weights(EdgeList const & L){
    int totalWeight = 0;
    for (const Edge & edge : L) totalWeight += edge.weight;
    return totalWeight;
}

void file_to_graph(string filename, Graph & G){
    ifstream file(filename);
    if (!file){
        cout << "Error opening file: " << filename << endl;
        return;
    }
    file >> G;
    file.close();
}


VertexList dfs(const Graph& graph, Vertex startVertex){
    VertexList result;
    vector<bool> visited(graph.size(), false);

    stack<Vertex> stk;
    visited[startVertex] = true;
    stk.push(startVertex);
    while (!stk.empty()) {
        Vertex vertex = stk.top();
        stk.pop();
        result.push_back(vertex);
            for (Vertex v : graph.edges_from(vertex))
                if (!visited[v]) {
                    visited[v] = true;
                    stk.push(v);
                }
    }
    return result;
}

VertexList bfs(const Graph& graph, Vertex startVertex){
    VertexList  result;
    vector<bool> visited(graph.size(), false);
    queue<Vertex> queue;
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        Vertex vertex = queue.front();
        queue.pop();
        result.push_back(vertex);
        for (Vertex v : graph.edges_from(vertex))
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
    }
    return result;

}

string get_arg(int argc, char *argv[], string def){
    if (argc > 1 && argv[1] != nullptr) return string(argv[1]);
    return def;
}