#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

const int64_t kInf = 30000;

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
}

class GraphList {
    Vertex num_vertex_;
    Vertex num_edge_;
    struct Edge {
        Vertex from;
        Vertex to;
        DistT weight;
    };
    std::vector<DistT> dist_;
    std::vector<Edge> edges_;

public:
    GraphList(Vertex, Vertex);
    GraphList(Vertex, Vertex, GraphMatrix);
    void AddEdge(Vertex, Vertex, DistT);
    void BellmanFord();
    void GetDist();
};

GraphList::GraphList(Vertex num_vertex, Vertex num_edge) {
    num_vertex_ = num_vertex;
    num_edge_ = num_edge;
    dist_.resize(num_vertex_);
    dist_[0] = 0;
    for (Vertex i = 1; i < num_vertex_; i++) {
        dist_[i] = kInf;
    }
    edges_.resize(num_edge_);
}

GraphList::GraphList(Vertex num_vertex, Vertex num_edge, GraphMatrix gm) {
    num_vertex_ = num_vertex;
    num_edge_ = num_edge;
    dist_.resize(num_vertex_);
    dist_[0] = 0;
    for (Vertex i = 1; i < num_vertex_; i++) {
        dist_[i] = kInf;
    }
    edges_.resize(num_edge_);

    for (Vertex u = 0; u < num_vertex_; u++) {
        for (Vertex v = 0; v < num_vertex_; v++) {
            AddEdge(u, v, gm.matrix_[u][v]);
        }
    }
}

void GraphList::AddEdge(Vertex u, Vertex v, DistT w) {
    Edge add_e;
    add_e.from = u - 1;
    add_e.to = v - 1;
    add_e.weight = w;
    edges_.push_back(add_e);
}

void GraphList::BellmanFord() {
    for (Vertex i = 1; i < num_vertex_; i++) {
        for (auto& e : edges_) {
            if (dist_[e.from] + e.weight < dist_[e.to] && dist_[e.from] < kInf) {
                dist_[e.to] = dist_[e.from] + e.weight;
            }
        }
    }
    for (Vertex i = 0; i < num_vertex_; i++) {
        for (auto& e : edges_) {
            if (dist_[e.from] + e.weight < dist_[e.to] && dist_[e.from] < kInf) {
                dist_[e.to] = -kInf;
            }
        }
    }
}

void GraphList::GetDist() {
    for (Vertex i = 0; i < num_vertex_; i++) {
        std::cout << dist_[i] << " ";
    }
}

int main() {
    Vertex num_vertex;
    Vertex num_edge;
    std::cin >> num_vertex >> num_edge;

    GraphList g(num_vertex, num_edge);
    for (Vertex i = 0; i < num_edge; i++) {
        Vertex first;
        Vertex second;
        DistT w;
        std::cin >> first >> second >> w;
        g.AddEdge(first, second, w);
    }

    g.BellmanFord();
    g.GetDist();
    return 0;
}
