#include <iostream>
#include <unordered_map>
#include <vector>

using VERTEX = int64_t;
using DIST = int64_t;

class GraphList {
public:
    VERTEX num_vertex_;
    VERTEX num_edge_;
    struct Edge {
        VERTEX from;
        VERTEX to;
        DIST weight;
    };
    std::vector<Edge> list_;

    GraphList(VERTEX, VERTEX);
    void AddEdge(VERTEX, VERTEX, DIST);
};

GraphList::GraphList(VERTEX num_vertex, VERTEX num_edge) {
    num_vertex_ = num_vertex;
    num_edge_ = num_edge;
    list_.resize(num_edge_);
}

void GraphList::AddEdge(VERTEX u, VERTEX v, DIST weight) {
    if (u == v) {
        return;
    }
    Edge add_e;
    add_e.from = u;
    add_e.to = v;
    add_e.weight = weight;
    list_.push_back(add_e);
}

class GraphMatrix {
    const uint64_t inf_ = 1e9;
    VERTEX num_vertex_;
    std::vector<std::vector<DIST>> matrix_;
    std::vector<std::vector<DIST>> curf_;

    void Inquiry(std::vector<DIST>&);

public:
    explicit GraphMatrix(VERTEX);
    GraphMatrix(VERTEX, VERTEX, GraphList);
    void AddEdge(VERTEX, VERTEX, DIST);
    DIST GetFlow();
};

GraphMatrix::GraphMatrix(VERTEX num_vertex) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    curf_.resize(num_vertex_);
    for (VERTEX i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
        curf_[i].resize(num_vertex_);
    }
}

GraphMatrix::GraphMatrix(VERTEX num_vertex, VERTEX num_edge, GraphList gl) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    curf_.resize(num_vertex_);
    for (VERTEX i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
        curf_[i].resize(num_vertex_);
    }
    for (auto i = 0; i < num_edge; i++) {
        matrix_[gl.list_[i].from][gl.list_[i].to] = gl.list_[i].weight;
        matrix_[gl.list_[i].to][gl.list_[i].from] = gl.list_[i].weight;
    }
}

void GraphMatrix::AddEdge(VERTEX first, VERTEX second, DIST weight) {
    matrix_[first][second] = weight;
}

void GraphMatrix::Inquiry(std::vector<DIST>& from) {
    DIST cf = inf_;
    for (VERTEX cur = num_vertex_ - 1; cur != 0;) {
        DIST prev = from[cur];
        cf = std::min(cf, matrix_[prev][cur] - curf_[prev][cur]);
        cur = prev;
    }
    for (VERTEX cur = num_vertex_ - 1; cur != 0;) {
        DIST prev = from[cur];
        curf_[prev][cur] += cf;
        curf_[cur][prev] -= cf;
        cur = prev;
    }
}

DIST GraphMatrix::GetFlow() {
    while (true) {
        std::vector<VERTEX> from(num_vertex_, -1);
        std::vector<VERTEX> path(num_vertex_);
        VERTEX flag_1 = 0;
        VERTEX flag_2 = 0;
        path[flag_2++] = 0;
        from[0] = 0;
        for (VERTEX current; flag_1 < flag_2;) {
            current = path[flag_1++];
            for (VERTEX v = 0; v < num_vertex_; v++) {
                if (from[v] == -1 && matrix_[current][v] - curf_[current][v] > 0) {
                    path[flag_2++] = v;
                    from[v] = current;
                }
            }
        }
        if (from[num_vertex_ - 1] == -1) {
            break;
        }
        Inquiry(from);
    }

    DIST flow = 0;
    for (VERTEX i = 0; i < num_vertex_; i++) {
        if (matrix_[0][i]) {
            flow += curf_[0][i];
        }
    }
    return flow;
}

int main() {
    VERTEX num_vertex;
    VERTEX num_edge;
    std::cin >> num_vertex >> num_edge;

    GraphMatrix g(num_vertex);

    for (VERTEX i = 0; i < num_edge; i++) {
        VERTEX first;
        VERTEX second;
        DIST weight;
        std::cin >> first >> second >> weight;
        first--;
        second--;
        g.AddEdge(first, second, weight);
    }

    std::cout << g.GetFlow();
    return 0;
}
