#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 1e9;

// Edge structure for Ford-Fulkerson
struct Edge {
    int to;
    int capacity;
    int reverse_index;  // index of reverse edge in adjacency list of 'to'
};

class MaxFlow {
private:
    int n;
    vector<vector<Edge>> graph;
    vector<bool> visited;
    
    // DFS to find augmenting path
    int dfs(int u, int sink, int flow) {
        if (u == sink) return flow;
        visited[u] = true;
        
        for (Edge& edge : graph[u]) {
            if (!visited[edge.to] && edge.capacity > 0) {
                int pushed = dfs(edge.to, sink, min(flow, edge.capacity));
                if (pushed > 0) {
                    edge.capacity -= pushed;
                    graph[edge.to][edge.reverse_index].capacity += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    
public:
    MaxFlow(int n) : n(n) {
        graph.resize(n);
    }
    
    // Add edge (undirected = add two directed edges)
    void addEdge(int from, int to, int capacity) {
        // Forward edge
        Edge forward = {to, capacity, (int)graph[to].size()};
        // Backward edge (residual)
        Edge backward = {from, capacity, (int)graph[from].size()};
        
        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }
    
    // Compute max flow from source to sink
    int maxFlow(int source, int sink) {
        int total_flow = 0;
        
        while (true) {
            visited.assign(n, false);
            int pushed = dfs(source, sink, INF);
            if (pushed == 0) break;
            total_flow += pushed;
        }
        
        return total_flow;
    }
    
    // Reset capacities to original (for reusing graph)
    void resetCapacities(const vector<tuple<int,int,int>>& original_edges) {
        // Rebuild graph from original edges
        graph.clear();
        graph.resize(n);
        for (const auto& [from, to, cap] : original_edges) {
            addEdge(from, to, cap);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, C, P;
    cin >> N >> M >> C >> P;
    
    // Store original edges (u, v, capacity)
    vector<tuple<int,int,int>> edges(M);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges[i] = {u, v, c};
    }
    
    // Read removal plan (edge indices to remove in order)
    vector<int> removal_plan(P);
    for (int i = 0; i < P; i++) {
        cin >> removal_plan[i];
    }
    
    // Track which edges are removed
    vector<bool> removed(M, false);
    
    // Initial graph with all edges
    MaxFlow maxFlow(N);
    vector<tuple<int,int,int>> active_edges;
    for (int i = 0; i < M; i++) {
        auto [u, v, cap] = edges[i];
        maxFlow.addEdge(u, v, cap);
        active_edges.push_back({u, v, cap});
    }
    
    int removed_count = 0;
    int current_flow = maxFlow.maxFlow(0, N-1);
    
    // Try removing edges one by one
    for (int idx : removal_plan) {
        // Check if edge exists and not already removed
        if (idx < 0 || idx >= M || removed[idx]) {
            continue;
        }
        
        // Temporarily remove this edge
        removed[idx] = true;
        
        // Rebuild graph with only active edges
        MaxFlow testFlow(N);
        for (int i = 0; i < M; i++) {
            if (!removed[i]) {
                auto [u, v, cap] = edges[i];
                testFlow.addEdge(u, v, cap);
            }
        }
        
        // Compute new max flow
        int new_flow = testFlow.maxFlow(0, N-1);
        
        if (new_flow >= C) {
            // Can remove this edge
            removed_count++;
            current_flow = new_flow;
            // Update the actual maxFlow object
            maxFlow = move(testFlow);
        } else {
            // Cannot remove - put it back
            removed[idx] = false;
            break;
        }
    }
    
    // Output result
    cout << removed_count << " " << current_flow << endl;
    
    return 0;
}