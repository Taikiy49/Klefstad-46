#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <algorithm>
#include "dijkstras.h"
using namespace std;

vector<int> dijkstra_shortest_path(const Graph & G, int source, vector<int> & previous){
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push(make_pair(0, source));

    while (!minHeap.empty()){
        int u = minHeap.top().second;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge & e : G[u]){
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push(make_pair(distances[v], v));
            }
        }
    }
    previous[source] = -1;
    return distances;
}

vector<int> extract_shortest_path(const vector<int> & distances, const vector<int> & previous, int destination){
    vector<int> path;
    int curr = destination;
    while (curr != -1){
        path.push_back(curr);
        curr = previous[curr];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int> & v, int total){
    for (int i = 0; i < v.size(); ++i) cout << v[i] << " ";
    cout << "\nTotal cost is " << total << endl;
}