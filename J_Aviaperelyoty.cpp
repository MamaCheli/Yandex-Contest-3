#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

const int64_t kMaxWeight = 1e9;

class Graph {
    Vertex start_ = 0;
    Vertex finish_ = 0;
    Vertex max_night_ = 0;

    struct Edge {
        Vertex from;
        Vertex to;
        DistT weight;
    };
    std::vector<Edge> edges_;
    std::vector<std::pair<DistT, DistT>> dist_;
    bool Relax(Edge);
    bool Bellman();

public:
    Graph(Vertex, Vertex, Vertex, Vertex, Vertex);
    void AddEdge(Vertex, Vertex, Vertex, DistT);
    DistT GetDistance();
};

Graph::Graph(Vertex num_vertex, Vertex num_edge, Vertex start, Vertex finish, Vertex max_night) {
    start_ = start;
    finish_ = finish;
    max_night_ = max_night;
    edges_.resize(num_edge + 1);
    dist_.resize(num_vertex + 1, std::make_pair(kMaxWeight, 0));
    dist_[start_].first = 0;
}

void Graph::AddEdge(Vertex num, Vertex u, Vertex v, DistT w) {
    edges_[num].from = u;
    edges_[num].to = v;
    edges_[num].weight = w;
}

bool Graph::Relax(Edge e) {
    if (dist_[e.from].first < kMaxWeight && dist_[e.to].first > dist_[e.from].first + e.weight &&
        dist_[e.from].second + static_cast<DistT>(e.to != finish_) < max_night_) {
        dist_[e.to].first = dist_[e.from].first + e.weight;
        dist_[e.to].second = dist_[e.from].second + 1;
        return true;
    }
    return false;
}

bool Graph::Bellman() {
    for (size_t v = 2; v < dist_.size(); v++) {
        for (auto& i : edges_) {
            Relax(i);
        }
    }
    for (auto& i : edges_) {
        if (Relax(i)) {
            return false;
        }
    }
    return true;
}

DistT Graph::GetDistance() {
    Bellman();
    return dist_[finish_].first == kMaxWeight ? -1 : dist_[finish_].first;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    Vertex num_vertex = 0;
    Vertex num_edge = 0;
    Vertex start = 0;
    Vertex finish = 0;
    Vertex max_nights = 0;
    std::cin >> num_vertex >> num_edge >> max_nights >> start >> finish;

    Graph g(num_vertex, num_edge, start, finish, max_nights);

    for (Vertex i = 0; i < num_edge; i++) {
        Vertex first;
        Vertex second;
        DistT weight;
        std::cin >> first >> second >> weight;
        g.AddEdge(i, first, second, weight);
    }

    std::cout << g.GetDistance();
    return 0;
}
