#include <iostream>
#include <vector>
#include <set>
#include <map>

const int64_t kMaxWeight = 2009000999;

using Vertex = int64_t;
using DistT = int64_t;

class Graph {
    Vertex num_vertex_;
    std::vector<std::vector<DistT>> graph_;
    std::vector<DistT> dist_;
    std::map<std::pair<Vertex, Vertex>, DistT> edges_;
    void Dijkstra(Vertex);

public:
    Graph(Vertex, const std::vector<std::pair<std::pair<Vertex, Vertex>, DistT>>&);
    std::vector<DistT> GetWay(Vertex);
};

Graph::Graph(Vertex num_vertex, const std::vector<std::pair<std::pair<Vertex, Vertex>, DistT>>& vertex) {
    num_vertex_ = num_vertex;
    graph_.resize(num_vertex_);
    dist_.resize(num_vertex_, kMaxWeight);
    for (auto& i : vertex) {
        graph_[i.first.first].emplace_back(i.first.second);
        graph_[i.first.second].emplace_back(i.first.first);
        if (edges_.find(i.first) == edges_.end() || edges_[i.first] > i.second) {
            edges_[i.first] = i.second;
            edges_[std::make_pair(i.first.second, i.first.first)] = i.second;
        }
    }
}

void Graph::Dijkstra(Vertex v) {
    dist_[v] = 0;
    std::set<std::pair<Vertex, Vertex>> heap;
    for (Vertex i = 0; i < num_vertex_; i++) {
        heap.insert(std::make_pair(dist_[i], i));
    }
    while (!heap.empty()) {
        std::pair<Vertex, Vertex> argmin = *heap.begin();
        heap.erase(argmin);
        Vertex u = argmin.second;
        for (auto& i : graph_[u]) {
            if (heap.find(std::make_pair(dist_[i], i)) != heap.end() &&
                dist_[i] > dist_[u] + edges_[std::make_pair(i, u)]) {
                DistT old_dist = dist_[i];
                dist_[i] = dist_[u] + edges_[std::make_pair(i, u)];
                heap.erase(std::make_pair(old_dist, i));
                heap.insert(std::make_pair(dist_[i], i));
            }
        }
    }
}

std::vector<DistT> Graph::GetWay(Vertex v) {
    Dijkstra(v);
    return dist_;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int num_command = 0;
    std::cin >> num_command;

    std::vector<std::vector<DistT>> path;
    path.reserve(num_command);
    for (int i = 0; i < num_command; i++) {
        Vertex num_vertex = 0;
        Vertex num_edges = 0;
        std::cin >> num_vertex >> num_edges;

        std::vector<std::pair<std::pair<Vertex, Vertex>, DistT>> edges;
        edges.reserve(num_edges);
        for (Vertex j = 0; j < num_edges; j++) {
            Vertex first;
            Vertex second;
            DistT weight;
            std::cin >> first >> second >> weight;
            edges.emplace_back(std::make_pair(std::make_pair(first, second), weight));
        }
        Vertex v;
        std::cin >> v;
        Graph g(num_vertex, edges);
        path.emplace_back(g.GetWay(v));
    }
    for (auto& i : path) {
        for (auto& j : i) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
