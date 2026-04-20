# Lab 3: Making Friends - Discussion Answers

## Results

```
admins@sandbox:~/Desktop/Algoritm_lab/3makingfriends$ g++ -std=c++11 -o main main.cpp Edge.hpp UnionFind.hpp 
admins@sandbox:~/Desktop/Algoritm_lab/3makingfriends$ time ./check_solution.sh ./main
data/sample/1.in
Correct!
data/sample/2.in
Correct!
data/secret/1small.in
Correct!
data/secret/2med.in
Correct!
data/secret/3large.in
Correct!
data/secret/4huge.in
Correct!

real	0m6.712s
user	0m5.681s
sys	0m0.232s
admins@sandbox:~/Desktop/Algoritm_lab/3makingfriends$ time ./main ./data/secret/4huge.in 
^C
real	0m15.209s
user	0m0.012s
sys	0m0.005s

admins@sandbox:~/Desktop/Algoritm_lab/3makingfriends$ time ./main < ./data/secret/4huge.in 
2022919678

real	0m4.864s
user	0m4.641s
sys	0m0.094s
admins@sandbox:~/Desktop/Algoritm_lab/3makingfriends$ 
```

**Performance on largest input (4huge.in):**
- Runtime: ~4.86 seconds
- Input size: N = 100,000 nodes, M = 3,000,000 edges

**What takes the majority of time?**
- **Sorting the edges** dominates (O(M log M))
- Sorting 3 million edges requires ~66 million comparisons
- Union-Find operations are nearly linear and much faster

---

## Why does Kruskal's algorithm produce a minimal spanning tree?

Kruskal's algorithm produces an MST because of the **cut lemma** (safe edge theorem):

1. **Initial state**: Each node is its own component (forest)

2. **Greedy choice**: Process edges in increasing weight order

3. **Safety**: For edge (u, v) with weight w:
   - If u and v are in different components, this edge is the **cheapest edge crossing the cut** between those components
   - By the cut lemma, this edge is **safe** – it belongs to some MST

4. **No cycles**: Adding an edge between different components cannot create a cycle

5. **Termination**: After adding N-1 edges, all nodes are connected in a single tree

The greedy choice of always taking the smallest safe edge leads to the global optimum.

---

## Time Complexity and Why

**Overall time complexity: O(M log M)**

| Operation | Complexity | Explanation |
|-----------|------------|-------------|
| Reading input | O(M) | One pass through all edges |
| **Sorting edges** | **O(M log M)** | **Dominant term** |
| Union-Find (find) | O(α(M,N)) ≈ O(1) | Path compression makes it nearly constant |
| Union-Find (union) | O(1) | Union by size is constant time |
| Total | O(M log M) | Sorting dominates |

**Why sorting dominates:**
- M can be 3,000,000 → M log M ≈ 3e6 × 22 = 66 million operations
- Union-Find with path compression + union-by-size is nearly O(1) per operation
- The constant factor for sorting is larger than for Union-Find

**Why this is optimal:**
- Any MST algorithm must examine all edges in the worst case
- Comparison-based sorting has a lower bound of Ω(M log M)

---

## What happens if an edge in the MST collapses?

**Immediate effects:**
- The spanning tree becomes **disconnected** (splits into two components)
- Some nodes can no longer reach others
- The "all connected" property is violated

**Problems in real applications:**

| Application | Consequence of edge failure |
|-------------|----------------------------|
| Electrical grid | Power outage for one entire region |
| Network design | Loss of connectivity between network segments |
| Pipeline (water/gas) | Disruption of flow to certain areas |
| Transportation | Road becomes unusable, detours needed |
| Communication | Network partition, data cannot route |

**Mitigation strategies:**
- **Redundancy**: Build 2-edge-connected networks (more expensive)
- **Backup edges**: Maintain alternative connections
- **Monitoring**: Detect failures and recompute MST for remaining graph
- **N-1 reliability**: Design to tolerate single edge failures

**In the "Making Friends" context:**
If a friendship introduction fails, the affected people lose that direct connection. However, they may remain connected through other friends (if alternative paths exist). If no alternative path exists, they become disconnected from the group.

---

## Real Applications of MST

| Application | Description |
|-------------|-------------|
| **Network design** | Minimum cost to connect computers/telephone exchanges |
| **Electrical grids** | Connecting power plants to cities with minimal cable length |
| **Pipeline systems** | Laying water/gas/oil pipes with minimal total length |
| **Transportation** | Building roads/railways to connect all cities |
| **Clustering** | Single-linkage clustering in machine learning |
| **Image segmentation** | Grouping similar pixels together |
| **Circuit design** | Minimizing wire length in printed circuit boards |
| **Biology** | Constructing phylogenetic trees from genetic data |
| **Civil engineering** | Planning utility networks (water, sewer, electricity) |

**Requirements for MST to be the right solution:**

1. **Connectivity requirement** – All nodes must be connected (not just some)

2. **No central hub** – No node is more important than others (undirected graph)

3. **Cost minimization** – Minimize total cost, not individual path costs

4. **No redundancy needed** – Single connection between components is sufficient

5. **Costs are additive** – Total cost = sum of individual edge costs

6. **Static graph** – Graph structure does not change frequently

7. **Undirected edges** – Connection cost is the same in both directions

**When NOT to use MST:**

| Scenario | Better solution |
|----------|-----------------|
| Need shortest path from A to B | Dijkstra / Shortest Path |
| Need redundant connections | 2-edge-connected or k-connected graph |
| Different node priorities | Steiner tree or shortest path tree |
| Directed connections | Arborescence or directed MST |
| Individual path optimization | Single-source shortest paths |

---

## Implementation Summary

**Data structures used:**
- `struct Edge` – stores u, v, weight with operator< for sorting
- `vector<Edge>` – dynamic array for storing all edges
- `UnionFind` class – parent[] and size[] arrays
- Path compression in find()
```
Before: parent = [0, 0, 1, 2, 4]
find(3):
  - parent[3] = 2, not root → find(2)
  - parent[2] = 1, not root → find(1)
  - parent[1] = 0, not root → find(0)
  - parent[0] = 0, is root → return 0
  
  Path compression sets:
  parent[3] = 0
  parent[2] = 0
  parent[1] = 0
  
After: parent = [0, 0, 0, 0, 4]  // Flattened! Future find() calls on these nodes become O(1)
```
- Union-by-size in unionSets()
```
Before union:
Component A (root=0): size=3
Component B (root=2): size=1

unionSets(any node from A, any node from B):
  - rootA = 0, rootB = 2
  - size[0] = 3, size[2] = 1
  - 3 >= 1 → attach rootB under rootA
  - parent[2] = 0
  - size[0] = 3 + 1 = 4

After:
Component A+B (root=0): size=4
```

**Optimizations:**
- Early termination after N-1 edges
- 0-indexing for easier array access
- Pass by const reference to avoid copies

**Overall running time: O(M log M)** – passes all tests within time limits
