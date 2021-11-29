#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

class Graph {
    class DSU {
        Vertex size_ = 0;
        void MakeSet();
        std::vector<Vertex> parent_;
        std::vector<Vertex> rank_;

    public:
        explicit DSU(Vertex);
        Vertex FindSet(Vertex);
        void Union(Vertex, Vertex);
    };

    Vertex num_vertex_ = 0;
    struct Edge {
        Vertex from;
        Vertex to;
        DistT weight;
    };
    std::vector<Edge> edges_;
    std::vector<Edge> mst_;
    void Kruskal();

public:
    Graph(Vertex, Vertex);
    void AddEdge(Vertex, Vertex, Vertex, DistT);
    DistT MinWeight();
};

Graph::DSU::DSU(Vertex num_vertex) {
    parent_.resize(num_vertex + 1);
    rank_.resize(num_vertex + 1);
    for (Vertex i = 0; i < num_vertex + 1; i++) {
        MakeSet();
    }
}

void Graph::DSU::MakeSet() {
    parent_[size_] = size_;
    size_++;
}

Vertex Graph::DSU::FindSet(Vertex v) {
    if (v == parent_[v]) {
        return v;
    }
    return parent_[v] = FindSet(parent_[v]);
}

void Graph::DSU::Union(Vertex x, Vertex y) {
    x = FindSet(x);
    y = FindSet(y);

    if (x != y) {
        size_--;
        if (rank_[x] < rank_[y]) {
            parent_[x] = y;
        } else if (rank_[y] < rank_[x]) {
            parent_[y] = x;
        } else {
            parent_[x] = y;
            rank_[y]++;
        }
    }
}

Graph::Graph(Vertex num_vertex, Vertex num_edge) {
    num_vertex_ = num_vertex;
    edges_.resize(num_edge);
}

void Graph::AddEdge(Vertex num, Vertex u, Vertex v, DistT w) {
    edges_[num].from = u;
    edges_[num].to = v;
    edges_[num].weight = w;
}

void Graph::Kruskal() {
    DSU d(num_vertex_);
    for (auto& v : edges_) {
        if (d.FindSet(v.from) != d.FindSet(v.to)) {
            d.Union(v.from, v.to);
            mst_.emplace_back(v);
        }
    }
}

DistT Graph::MinWeight() {
    Kruskal();
    DistT minweight = 0;
    for (auto& i : mst_) {
        minweight += i.weight;
    }
    return minweight;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    Vertex num_vertex = 0;
    Vertex num_edge = 0;
    std::cin >> num_vertex >> num_edge;

    Graph g(num_vertex, num_edge);
    for (Vertex i = 0; i < num_edge; i++) {
        Vertex first = 0;
        Vertex second = 0;
        DistT weight = 0;
        std::cin >> first >> second >> weight;
        g.AddEdge(i, first, second, weight);
    }
    std::cout << g.MinWeight();
    return 0;
}
