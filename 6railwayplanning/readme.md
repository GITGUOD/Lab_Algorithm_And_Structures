# Result
```bash
admins@sandbox:~/Desktop/Algoritm_lab/6railwayplanning$ time ./check_solution.sh ./fulkerson 
data/sample/1.in
Correct!
data/secret/0mini.in
Correct!
data/secret/1small.in
Correct!
data/secret/2med.in
Correct!
data/secret/3large.in
^C

real	12m20.830s
user	12m3.019s
sys	0m1.023s
admins@sandbox:~/Desktop/Algoritm_lab/6railwayplanning$ time ./check_solution.sh ./dinic
data/sample/1.in
Correct!
data/secret/0mini.in
Correct!
data/secret/1small.in
Correct!
data/secret/2med.in
Correct!
data/secret/3large.in
Correct!
data/secret/4huge.in
Correct!

real	4m47.116s
user	4m39.484s
sys	0m0.681s
admins@sandbox:~/Desktop/Algoritm_lab/6railwayplanning$ 
```

---
# 16.3 Goals of the lab
1. Implementing a Network-Flow-algorithm
   1. Ford-Fulkerso, DFS (one path at a time)
   2. Dinic's BFS + multiple DFS 
| Factor | Ford–Fulkerson | Dinic's |
|---|---:|---:|
| Path finding | DFS (one path at a time) | BFS (level graph) + multiple DFS |
| Augmentations per phase | Many | Few |
| Complexity | O(E × max_flow) | O(E × √V) or O(V²E) |
| For large graphs | Terrible | Good |

3. Debugging your code.
   1. Checked!
4. Structuring your code in a logical fashion.
   1. checked!
5. Reason about correctness of your algorithm.
   1. **Dinic's** algorithm is correctly computes the maximum flow because Dinic's algorithm repeatedly finds augmenting paths in a level graph using BFS and sends flow along all possible blocking flows via DFS, which guarantees termination at the maximum flow due to the max-flow min-cut theorem.
   2. **Ford-Fulkerson** is correct because it repeatedly finds augmenting paths via DFS and increases flow until no path exists, which by the max-flow min-cut theorem yields the maximum flow.
6. Reason about upper bounds for time complexity.
   1. Ford-Fulkerson (DFS):
      1. Upper bound: O(E × f_max)
      2. Each DFS finds one augmenting path and increases flow by at least 1. Worst case: f_max augmentations, each costing O(E).
   2. Dinic's Algorithm:
      1. Upper bound: O(min(V^(2/3), √E) × E) for unit capacities, or O(V² × E) in general
      2. Each BFS phase creates a level graph. The number of phases is bounded by O(V²) because each phase increases the distance from source to sink. Within each phase, multiple DFS find blocking flows in O(E) total.
   3. For this lab (N ≤ 1000, M ≤ ~1e6, capacities ≤ 100):
      1. Dinic's practical bound: O(√V × E) ≈ O(1000 × 1e6) = 1e9 operations worst-case
      2. But with early stopping when flow ≥ C, often much faster
----
# 16.7 Examination and Points of Discussion
1. Have successfully implemented the algorithm with the correct time complexity.
   1. First i implemented the **Ford-Fulkerson (DFS)**, it was not fast enough with O(E × f_max)
   2. SEcond i implemented the **Dinic's Algorithm**, it was good enough with time complexity of Upper bound: O(min(V^(2/3), √E) × E)
2. Have neat and understandable code.
   1. Checked!
3. Have reasonable variable names.
   1. Checked!
4. Have filled in the blanks in the report.
   1. Checked!
5. Have run the check_solutions.sh script to validate your solution.
   1. See REsult.
---
## What is the time complexity, and more importantly why?

1. **Ford-fulkerson** O(E × f_max) because each DFS finds one augmenting path increasing flow by at least 1, requiring up to f_max iterations, each costing O(E) to traverse the graph.

2. **Dinic's** O(min(V^(2/3), √E) × E) for unit capacities or O(V² × E) in general, because each BFS phase creates a level graph and multiple DFS find blocking flows in O(E), with the number of phases bounded by O(V²).
---
## Which other (well-known) algorithmic problems can be solved using NetworkFlow?
1. Bipartite Matching- Source to left nodes, edges capacity 1, right nodes to sink
2. Maximum Matching in General Graphs	More complex but possible with Edmonds' algorithm
---
## If the capacities of the edges are very large, how can one get a different (better) time complexity?
1. Ford-Fulkerson: O(E × f_max) → f_max huge → very slow
2. Dinic's: Still O(V² × E) which is independent of capacity size
   
   For very large capacities, use Dinic's algorithm which has complexity O(V² × E) independent of capacity size, or capacity scaling which processes bits from most significant to least, giving O(E² log f_max) instead of O(E × f_max).
---
# Report
## Results
1. Briefly comment the results, did the script say all your solutions were correct?
   1. Yes, see the resutls.
2. Approximately how long time does it take for the program to run on the largest input?
```
admins@sandbox:~/Desktop/Algoritm_lab/6railwayplanning$ time ./fulkerson < ./data/secret/4huge.in 
^C
real	26m49.217s
user	26m8.049s
sys	0m2.359s

admins@sandbox:~/Desktop/Algoritm_lab/6railwayplanning$ time ./dinic < ./data/secret/4huge.in 
5734 9512

real	4m1.823s
user	3m55.618s
sys	0m0.496s
admins@sandbox:~/Desktop/Algoritm_lab/6railwayplanning$ 
```
#### Why Ford-Fulkerson is so slow on this input:
    1. N = 1000 nodes
    2. M = 100,000 edges
    3. C = 9500 (required flow)
    4. P = 10,000 removal attempts
    5. Capacities = 21-95 (small but many edges)
I canceled the fukolerson algorithm becuase to took alot of time.

1. What takes the majority of the time?
* For Ford-Fulkerson, the majority of time is spent on repeated DFS traversals finding single augmenting paths; for Dinic's, the majority of time is spent on BFS level graph construction and multiple DFS augmentations within each phase, though both are dominated by edge traversals due to the large graph size (100,000 edges) and many removal attempts (10,000).

## Implementation details
1. How did you implement the solution?
   1. Dinic's algorithm with BFS for level graphs and DFS for blocking flow, testing removals sequentially until flow drops below required C.
   2. 
2. Which data structures were used?
   1. vector< vector< Edge>> – adjacency list for graph
   2. vector< int> – level array and iterator array
   3. struct Edge – with to, rev (reverse index), cap (capacity)
   4. vector< bool> – to track removed edges
3. Which modifications to these data structures were used?
   1. Edge structure stores reverse edge index for O(1) residual updates
   2. Iterator array for current edge index (Dinic's optimization)
   3. Early stop condition when flow ≥ C
4. What is the overall running time? Why?
   1. O(P × V² × E) in worst case, but with early stopping it runs in ~4 minutes for largest input because Dinic's finds multiple augmenting paths per BFS phase and capacities are small.



