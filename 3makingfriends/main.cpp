#include <iostream>
#include <vector>
#include <algorithm>
#include "Edge.hpp"
#include "UnionFind.hpp"

using namespace std;

long long kruskal(int N, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // Uses Edge::operator<
    UnionFind uf(N);
    long long total = 0;
    int edgesUsed = 0;
    
    for (const Edge& e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            uf.unionSets(e.u, e.v);
            total += e.weight;
            edgesUsed++;
            if (edgesUsed == N - 1) break;  // MST complete
        }
    }
    return total;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        // Convert to 0-index if needed (input uses 1-index)
        edges[i].u--;
        edges[i].v--;
    }
    
    long long result = kruskal(N, edges);
    cout << result << endl;
    
    return 0;
}