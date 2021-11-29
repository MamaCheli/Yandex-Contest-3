#include <iostream>
#include <vector>
#include <set>
#include <map>

const int64_t kMaxWeight = 1e9;

using Vertex = int64_t;
using DistT = int64_t;

class Graph {
    Vertex num_vertex_;
    std::vector<std::vector<Vertex>> graph_;
    std::map<std::pair<Vertex, Vertex>, DistT> edges_;
    std::vector<std::pair<Vertex, Vertex>> mst_;

    void Prim();

public:
    Graph(Vertex, const std::vector<std::pair<std::pair<Vertex, Vertex>, DistT>>&);
    DistT MinWeight();
};

Graph::Graph(Vertex num_vertex, const std::vector<std::pair<std::pair<Vertex, Vertex>, DistT>>& vertex) {
    num_vertex_ = num_vertex;
    graph_.resize(num_vertex_ + 1);
    for (auto& i : vertex) {
        graph_[i.first.first].emplace_back(i.first.second);
        graph_[i.first.second].emplace_back(i.first.first);
        if (edges_.find(i.first) == edges_.end() || edges_[i.first] > i.second) {
            edges_[i.first] = i.second;
            edges_[std::make_pair(i.first.second, i.first.first)] = i.second;
        }
    }
}

void Graph::Prim() {
    std::vector<DistT> dist;
    dist.resize(num_vertex_ + 1, kMaxWeight);
    dist[1] = 0;
    std::vector<Vertex> parent;
    parent.resize(num_vertex_ + 1, -1);
    std::set<Vertex> s;

    Vertex set_size = 0;
    while (set_size != num_vertex_) {
        DistT minweight = kMaxWeight;
        Vertex argmin = 0;
        for (Vertex i = 1; i < num_vertex_ + 1; i++) {
            if (minweight > dist[i]) {
                minweight = dist[i];
                argmin = i;
            }
        }
        s.insert(argmin);
        set_size++;
        dist[argmin] = kMaxWeight;
        if (parent[argmin] != -1) {
            mst_.emplace_back(std::make_pair(parent[argmin], argmin));
        }
        for (auto& u : graph_[argmin]) {
            if (s.find(u) == s.end() && dist[u] > edges_[std::make_pair(argmin, u)]) {
                dist[u] = edges_[std::make_pair(argmin, u)];
                parent[u] = argmin;
            }
        }
    }
}

DistT Graph::MinWeight() {
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

    std::vector<std::pair<std::pair<Vertex, Vertex>, DistT>> edges;
    edges.reserve(num_edges);
    for (Vertex i = 0; i < num_edges; ++i) {
        Vertex first;
        Vertex second;
        DistT weight;
        std::cin >> first >> second >> weight;
        edges.emplace_back(std::make_pair(std::make_pair(first, second), weight));
    }
    Graph g(num_vertex, edges);
    std::cout << g.MinWeight();
    return 0;
}
