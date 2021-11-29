#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

const int64_t kInf = 1000000000;
const int64_t kMaxWeihgt = 100000;

class Graph {
    Vertex num_vertex_;
    Vertex num_edge_;
    struct Edge {
        Vertex from;
        Vertex to;
        DistT weight;
    };
    std::vector<DistT> dist_;
    std::vector<Vertex> prev_;
    std::vector<Edge> edges_;

public:
    explicit Graph(Vertex);
    void AddEdge(Vertex, Vertex, DistT);
    Vertex IsCycle();
    void PrintCycle();
};

Graph::Graph(Vertex num_vertex) {
    num_vertex_ = num_vertex;
    dist_.resize(num_vertex_);
    prev_.resize(num_vertex_);
    for (Vertex i = 0; i < num_vertex_; i++) {
        dist_[i] = 0;
        prev_[i] = -1;
    }
}

void Graph::AddEdge(Vertex first, Vertex second, DistT weight) {
    if (weight != kMaxWeihgt) {
        edges_.push_back({first, second, weight});
    }
}

Vertex Graph::IsCycle() {
    Vertex flag = -1;
    for (Vertex k = 0; k < num_vertex_; k++) {
        flag = -1;
        for (auto& e : edges_) {
            if (dist_[e.from] + e.weight < dist_[e.to] && dist_[e.from] < kInf) {
                dist_[e.to] = dist_[e.from] + e.weight;
                prev_[e.to] = e.from;
                flag = e.from;
            }
        }
    }
    return flag;
}

void Graph::PrintCycle() {
    Vertex flag = IsCycle();
    if (flag == -1) {
        std::cout << "NO\n";
    } else {
        Vertex last = flag;
        for (Vertex i = 0; i < num_vertex_; i++) {
            last = prev_[last];
        }
        std::vector<Vertex> cycle;
        for (Vertex cur = last;; cur = prev_[cur]) {
            cycle.push_back(cur);
            if (cur == last && cycle.size() > 1) {
                break;
            }
        }
        std::cout << "YES\n";
        std::cout << cycle.size() << "\n";
        std::cout << cycle[0] + 1 << " ";
        for (Vertex i = cycle.size() - 2; i >= 0; i--) {
            std::cout << cycle[i] + 1 << " ";
        }
    }
}

int main() {
    Vertex num_vertex;
    std::cin >> num_vertex;
    Graph g(num_vertex);
    for (Vertex i = 0; i < num_vertex; i++) {
        for (Vertex j = 0; j < num_vertex; j++) {
            DistT w;
            std::cin >> w;
            g.AddEdge(i, j, w);
        }
    }

    g.PrintCycle();
    return 0;
}
