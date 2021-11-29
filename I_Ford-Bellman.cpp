#include <iostream>
#include <vector>

const uint64_t kInf = 30000;

class Graph {
    uint64_t num_vertex_;
    uint64_t num_edge_;
    struct Edge {
        int from;
        int to;
        uint64_t weight;
    };
    std::vector<uint64_t> dist_;
    std::vector<Edge> edges_;

public:
    Graph(int, int);
    void AddEdge(int, int, int, int);
    void BellmanFord();
    void GetDist();
};

Graph::Graph(int num_vertex, int num_edge) {
    num_vertex_ = num_vertex;
    num_edge_ = num_edge;
    dist_.resize(num_vertex_);
    dist_[0] = 0;
    for (uint64_t i = 1; i < num_vertex_; i++) {
        dist_[i] = kInf;
    }
    edges_.resize(num_edge_);
}

void Graph::AddEdge(int num, int u, int v, int w) {
    edges_[num].from = u - 1;
    edges_[num].to = v - 1;
    edges_[num].weight = w;
}

void Graph::BellmanFord() {
    for (uint64_t i = 1; i < num_vertex_; i++) {
        for (auto& e : edges_) {
            if (dist_[e.from] + e.weight < dist_[e.to] && dist_[e.from] < kInf) {
                dist_[e.to] = dist_[e.from] + e.weight;
            }
        }
    }
    for (uint64_t i = 0; i < num_vertex_; i++) {
        for (auto& e : edges_) {
            if (dist_[e.from] + e.weight < dist_[e.to] && dist_[e.from] < kInf) {
                dist_[e.to] = -kInf;
            }
        }
    }
}

void Graph::GetDist() {
    for (uint64_t i = 0; i < num_vertex_; i++) {
        std::cout << dist_[i] << " ";
    }
}

int main() {
    uint64_t num_vertex;
    uint64_t num_edge;
    std::cin >> num_vertex >> num_edge;

    Graph g(num_vertex, num_edge);
    for (uint64_t i = 0; i < num_edge; i++) {
        int first;
        int second;
        uint64_t w;
        std::cin >> first >> second >> w;
        g.AddEdge(i, first, second, w);
    }

    g.BellmanFord();
    g.GetDist();
    return 0;
}
