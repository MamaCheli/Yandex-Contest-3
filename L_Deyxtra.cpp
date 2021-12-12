#include <iostream>
#include <vector>
#include <set>
#include <map>

using VERTEX = int64_t;
using DIST = int64_t;
using Three = std::pair<std::pair<VERTEX, VERTEX>, DIST>;

const int64_t kMaxWeight = 2009000999;

class GraphMatrix {
    VERTEX num_vertex_;

public:
    std::vector<std::vector<VERTEX>> matrix_;
    explicit GraphMatrix(VERTEX);
    void AddEdge(VERTEX, VERTEX, DIST);
};

GraphMatrix::GraphMatrix(VERTEX num_vertex) {
    num_vertex_ = num_vertex;
    for (VERTEX i = 0; i < num_vertex_; i++) {
        std::vector<VERTEX> tmp(num_vertex_, 0);
        matrix_.push_back(tmp);
    }
}

void GraphMatrix::AddEdge(VERTEX u, VERTEX v, DIST weight) {
    if (u == v) {
        return;
    }
    matrix_[u][v] = weight;
    matrix_[v][u] = weight;
}

class GraphList {
    VERTEX num_vertex_;
    std::vector<std::vector<DIST>> graph_;
    std::vector<DIST> dist_;
    std::map<std::pair<VERTEX, VERTEX>, DIST> edges_;
    void Dijkstra(VERTEX);

public:
    GraphList(VERTEX, const std::vector<Three>&);
    GraphList(VERTEX, GraphMatrix);
    std::vector<DIST> GetWay(VERTEX);
};

GraphList::GraphList(VERTEX num_vertex, const std::vector<Three>& vertex) {
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

GraphList::GraphList(VERTEX num_vertex, GraphMatrix gm) {
    num_vertex_ = num_vertex;
    graph_.resize(num_vertex_ + 1);
    dist_.resize(num_vertex_, kMaxWeight);
    for (VERTEX u = 0; u <= num_vertex_; u++) {
        for (VERTEX v = 0; v <= num_vertex_; v++) {
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

void GraphList::Dijkstra(VERTEX v) {
    dist_[v] = 0;
    std::set<std::pair<VERTEX, VERTEX>> heap;
    for (VERTEX i = 0; i < num_vertex_; i++) {
        heap.insert(std::make_pair(dist_[i], i));
    }
    while (!heap.empty()) {
        std::pair<VERTEX, VERTEX> argmin = *heap.begin();
        heap.erase(argmin);
        VERTEX u = argmin.second;
        for (auto& i : graph_[u]) {
            if (heap.find(std::make_pair(dist_[i], i)) != heap.end() &&
                dist_[i] > dist_[u] + edges_[std::make_pair(i, u)]) {
                DIST old_dist = dist_[i];
                dist_[i] = dist_[u] + edges_[std::make_pair(i, u)];
                heap.erase(std::make_pair(old_dist, i));
                heap.insert(std::make_pair(dist_[i], i));
            }
        }
    }
}

std::vector<DIST> GraphList::GetWay(VERTEX v) {
    Dijkstra(v);
    return dist_;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int num_command = 0;
    std::cin >> num_command;

    std::vector<std::vector<DIST>> path;
    path.reserve(num_command);
    for (int i = 0; i < num_command; i++) {
        VERTEX num_vertex = 0;
        VERTEX num_edges = 0;
        std::cin >> num_vertex >> num_edges;

        std::vector<Three> edges;
        edges.reserve(num_edges);
        for (VERTEX j = 0; j < num_edges; j++) {
            VERTEX first;
            VERTEX second;
            DIST weight;
            std::cin >> first >> second >> weight;
            edges.emplace_back(std::make_pair(std::make_pair(first, second), weight));
        }
        VERTEX v;
        std::cin >> v;
        GraphList g(num_vertex, edges);
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
