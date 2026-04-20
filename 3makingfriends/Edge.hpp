#ifndef EDGE_H
#define EDGE_H

struct Edge {
    int u;      
    int v;
    int weight;

    // For sorting by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

#endif