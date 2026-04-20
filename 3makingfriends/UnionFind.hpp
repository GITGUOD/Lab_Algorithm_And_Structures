#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <iostream>
#include <vector>

class UnionFind
{
private:
    std::vector<int> parent; // parent[i] = parent of node i
    std::vector<int> size;   // size[i] = size of component rooted at i

public:
    // Constructor
    UnionFind(int N)
    {
        parent.resize(N);
        size.resize(N, 1); // Each component starts with size 1
        for (int i = 0; i < N; i++)
        {
            parent[i] = i; // Each node is its own parent
        }
    }

    // Find with path compression
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    // Union by size
    void unionSets(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB)
        {
            if (size[rootA] < size[rootB])
                std::swap(rootA, rootB);
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
        }
    }
};

#endif