#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

const uint64_t kInf = 1e9;

class Graph {
    Vertex num_vertex_;
    std::vector<std::vector<DistT>> matrix_;
    std::vector<std::vector<DistT>> curf_;

    void Inquiry(std::vector<DistT>&);

public:
    explicit Graph(Vertex);
    void AddEdge(Vertex, Vertex, DistT);
    void Calculating();
    DistT GetFlow();
};

Graph::Graph(Vertex num_vertex) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    curf_.resize(num_vertex_);
    for (Vertex i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
        curf_[i].resize(num_vertex_);
    }
}

void Graph::AddEdge(Vertex first, Vertex second, DistT weight) {
    matrix_[first][second] = weight;
}

void Graph::Inquiry(std::vector<DistT>& from) {
    DistT cf = kInf;
    for (Vertex cur = num_vertex_ - 1; cur != 0;) {
        DistT prev = from[cur];
        cf = std::min(cf, matrix_[prev][cur] - curf_[prev][cur]);
        cur = prev;
    }
    for (Vertex cur = num_vertex_ - 1; cur != 0;) {
        DistT prev = from[cur];
        curf_[prev][cur] += cf;
        curf_[cur][prev] -= cf;
        cur = prev;
    }
}

void Graph::Calculating() {
    while (true) {
        std::vector<DistT> from(num_vertex_, -1);
        std::vector<DistT> path(num_vertex_);
        DistT h = 0;
        DistT t = 0;
        path[t++] = 0;
        from[0] = 0;
        for (DistT cur; h < t;) {
            cur = path[h++];
            for (Vertex v = 0; v < num_vertex_; v++) {
                if (from[v] == -1 && matrix_[cur][v] - curf_[cur][v] > 0) {
                    path[t++] = v;
                    from[v] = cur;
                }
            }
        }
        if (from[num_vertex_ - 1] == -1) {
            break;
        }
        Inquiry(from);
    }
}

DistT Graph::GetFlow() {
    DistT flow = 0;
    for (Vertex i = 0; i < num_vertex_; i++) {
        if (matrix_[0][i]) {
            flow += curf_[0][i];
        }
    }
    return flow;
}

int main() {
    Vertex num_vertex;
    Vertex num_edge;
    std::cin >> num_vertex >> num_edge;

    Graph g(num_vertex);

    for (Vertex i = 0; i < num_edge; i++) {
        Vertex first;
        Vertex second;
        DistT weight;
        std::cin >> first >> second >> weight;
        first--;
        second--;
        g.AddEdge(first, second, weight);
    }

    g.Calculating();
    std::cout << g.GetFlow();
    return 0;
}
