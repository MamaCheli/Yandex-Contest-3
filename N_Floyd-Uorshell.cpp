#include <iostream>
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
    VERTEX num_vertex_;
    std::vector<std::vector<DIST>> matrix_;
    void FloydWarshall();

public:
    explicit GraphMatrix(VERTEX);
    GraphMatrix(VERTEX, VERTEX, GraphList);
    void AddEdge(VERTEX, VERTEX, DIST);
    std::vector<std::vector<DIST>> GetPath();
};

GraphMatrix::GraphMatrix(VERTEX num_vertex) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    for (VERTEX i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
    }
}

GraphMatrix::GraphMatrix(VERTEX num_vertex, VERTEX num_edge, GraphList gl) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    for (VERTEX i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
    }
    for (auto i = 0; i < num_edge; i++) {
        matrix_[gl.list_[i].from][gl.list_[i].to] = gl.list_[i].weight;
    }
}

void GraphMatrix::AddEdge(VERTEX first, VERTEX second, DIST weight) {
    matrix_[first][second] = weight;
}

void GraphMatrix::FloydWarshall() {
    for (VERTEX k = 0; k < num_vertex_; k++) {
        for (VERTEX x = 0; x < num_vertex_; x++) {
            for (VERTEX y = 0; y < num_vertex_; y++) {
                matrix_[x][y] = std::min(matrix_[x][y], matrix_[x][k] + matrix_[k][y]);
            }
        }
    }
}

std::vector<std::vector<DIST>> GraphMatrix::GetPath() {
    FloydWarshall();
    return matrix_;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    VERTEX num_vertex;
    std::cin >> num_vertex;

    GraphMatrix g(num_vertex);
    for (VERTEX i = 0; i < num_vertex; i++) {
        for (VERTEX j = 0; j < num_vertex; j++) {
            DIST weight = 0;
            std::cin >> weight;
            g.AddEdge(i, j, weight);
        }
    }

    std::vector<std::vector<DIST>> new_path = g.GetPath();
    for (auto& i : new_path) {
        for (auto& j : i) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
