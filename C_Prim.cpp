#include <iostream>
#include <vector>
#include <set>
#include <map>

const int64_t kMaxWeight = 1e9;

using Vertex = int64_t;
using DistT = int64_t;
using Three = std::pair<std::pair<Vertex, Vertex>, DistT>;

class GraphMatrix {
    Vertex num_vertex_;

public:
    std::vector<std::vector<Vertex>> matrix_;
    explicit GraphMatrix(Vertex);
    void AddEdge(Vertex, Vertex, DistT);
};

GraphMatrix::GraphMatrix(Vertex num_vertex) {
    num_vertex_ = num_vertex;
    for (Vertex i = 0; i < num_vertex_; i++) {
        std::vector<Vertex> tmp(num_vertex_, 0);
        matrix_.push_back(tmp);
    }
}

void GraphMatrix::AddEdge(Vertex u, Vertex v, DistT weight) {
    if (u == v) {
        return;
    }
    matrix_[u][v] = weight;
    matrix_[v][u] = weight;
}

class GraphList {
    Vertex num_vertex_;
    std::vector<std::vector<Vertex>> graph_;
    std::map<std::pair<Vertex, Vertex>, DistT> edges_;
    std::vector<std::pair<Vertex, Vertex>> mst_;

    void Prim();

public:
    GraphList(Vertex, const std::vector<Three>&);
    GraphList(Vertex, GraphMatrix);
    DistT GetMinWeight();
};

GraphList::GraphList(Vertex num_vertex, const std::vector<Three>& edges) {
    num_vertex_ = num_vertex;
    graph_.resize(num_vertex_ + 1);
    for (auto& i : edges) {
        graph_[i.first.first].emplace_back(i.first.second);
        graph_[i.first.second].emplace_back(i.first.first);
        if (edges_.find(i.first) == edges_.end() || edges_[i.first] > i.second) {
            edges_[i.first] = i.second;
            edges_[std::make_pair(i.first.second, i.first.first)] = i.second;
        }
    }
}

GraphList::GraphList(Vertex num_vertex, GraphMatrix gm) {
    num_vertex_ = num_vertex;
    graph_.resize(num_vertex_ + 1);
    for (Vertex u = 0; u <= num_vertex_; u++) {
        for (Vertex v = 0; v <= num_vertex_; v++) {
            if (gm.matrix_[u][v] == 0) {
                continue;
            }
            graph_[u].emplace_back(v);
            if (edges_.find(std::make_pair(u, v)) == edges_.end() || edges_[std::make_pair(u, v)] > gm.matrix_[u][v]) {
                edges_[std::make_pair(u, v)] = gm.matrix_[u][v];
                edges_[std::make_pair(v, u)] = gm.matrix_[u][v];
            }
        }
    }
}

void GraphList::Prim() {
    std::vector<DistT> dist;
    dist.resize(num_vertex_ + 1, kMaxWeight);
    dist[1] = 0;
    std::vector<Vertex> parent;
    parent.resize(num_vertex_ + 1, -1);
    std::set<Vertex> set;

    size_t graph_size = num_vertex_;
    while (set.size() != graph_size) {
        DistT minweight = kMaxWeight;
        Vertex minweight_vertex = 0;
        for (Vertex i = 1; i < num_vertex_ + 1; i++) {
            if (minweight > dist[i]) {
                minweight = dist[i];
                minweight_vertex = i;
            }
        }
        set.insert(minweight_vertex);
        dist[minweight_vertex] = kMaxWeight;
        if (parent[minweight_vertex] != -1) {
            mst_.emplace_back(std::make_pair(parent[minweight_vertex], minweight_vertex));
        }
        for (auto& u : graph_[minweight_vertex]) {
            if (set.find(u) == set.end() && dist[u] > edges_[std::make_pair(minweight_vertex, u)]) {
                dist[u] = edges_[std::make_pair(minweight_vertex, u)];
                parent[u] = minweight_vertex;
            }
        }
    }
}

DistT GraphList::GetMinWeight() {
    Prim();
    DistT minweight = 0;
    for (auto& i : mst_) {
        minweight += edges_[i];
    }
    return minweight;
}

int main() {
    Vertex num_vertex = 0;
    Vertex num_edges = 0;
    std::cin >> num_vertex >> num_edges;

    std::vector<Three> edges;
    edges.reserve(num_edges);
    for (Vertex i = 0; i < num_edges; ++i) {
        Vertex first;
        Vertex second;
        DistT weight;
        std::cin >> first >> second >> weight;
        edges.emplace_back(std::make_pair(std::make_pair(first, second), weight));
    }
    GraphList g(num_vertex, edges);
    std::cout << g.GetMinWeight();
    return 0;
}
