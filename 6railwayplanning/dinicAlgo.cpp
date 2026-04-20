#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to, rev;
    long long cap;
};

class Dinic {
private:
    int n;
    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> iter;
    
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge& e : graph[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    
    long long dfs(int v, int t, long long f) {
        if (v == t) return f;
        
        for (int& i = iter[v]; i < graph[v].size(); i++) {
            Edge& e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
public:
    Dinic(int n) : n(n) {
        graph.resize(n);
        level.resize(n);
        iter.resize(n);
    }
    
    void addEdge(int from, int to, long long cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, cap});
    }
    
    long long maxFlow(int s, int t) {
        long long flow = 0;
        
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill(iter.begin(), iter.end(), 0);
            
            long long f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
    }
    
    // Reset graph to original capacities
    void reset(const vector<tuple<int,int,long long>>& edges) {
        graph.clear();
        graph.resize(n);
        for (const auto& [u, v, cap] : edges) {
            addEdge(u, v, cap);
        }
    }
    
    // Get current flow value quickly (for checking >= C)
    bool canFlow(int s, int t, long long required) {
        // Early stop if flow already >= required
        return maxFlow(s, t) >= required;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, P;
    long long C;
    cin >> N >> M >> C >> P;
    
    vector<tuple<int,int,long long>> edges(M);
    for (int i = 0; i < M; i++) {
        int u, v;
        long long cap;
        cin >> u >> v >> cap;
        edges[i] = {u, v, cap};
    }
    
    vector<int> removal_plan(P);
    for (int i = 0; i < P; i++) {
        cin >> removal_plan[i];
    }
    
    vector<bool> removed(M, false);
    Dinic dinic(N);
    
    // Initial graph with all edges
    dinic.reset(edges);
    
    int removed_count = 0;
    long long current_flow = dinic.maxFlow(0, N-1);
    
    // Try removing edges one by one
    for (int idx : removal_plan) {
        if (removed[idx]) continue;
        
        // Temporarily remove this edge
        removed[idx] = true;
        
        // Build graph without this edge
        Dinic testFlow(N);
        for (int i = 0; i < M; i++) {
            if (!removed[i]) {
                auto [u, v, cap] = edges[i];
                testFlow.addEdge(u, v, cap);
            }
        }
        
        long long new_flow = testFlow.maxFlow(0, N-1);
        
        if (new_flow >= C) {
            removed_count++;
            current_flow = new_flow;
            dinic = move(testFlow);
        } else {
            removed[idx] = false;
            break;
        }
    }
    
    cout << removed_count << " " << current_flow << endl;
    
    return 0;
}