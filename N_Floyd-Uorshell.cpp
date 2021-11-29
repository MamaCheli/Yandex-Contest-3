#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

class Graph {
    Vertex num_vertex_;
    std::vector<std::vector<DistT>> matrix_;
    void FloydWarshall();

public:
    explicit Graph(Vertex);
    void AddEdge(Vertex, Vertex, DistT);
    std::vector<std::vector<DistT>> GetPath();
};

Graph::Graph(Vertex num_vertex) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    for (Vertex i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
    }
}

void Graph::AddEdge(Vertex first, Vertex second, DistT weight) {
    matrix_[first][second] = weight;
}

void Graph::FloydWarshall() {
    for (Vertex k = 0; k < num_vertex_; k++) {
        for (Vertex x = 0; x < num_vertex_; x++) {
            for (Vertex y = 0; y < num_vertex_; y++) {
                matrix_[x][y] = std::min(matrix_[x][y], matrix_[x][k] + matrix_[k][y]);
            }
        }
    }
}

std::vector<std::vector<DistT>> Graph::GetPath() {
    FloydWarshall();
    return matrix_;
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    Vertex num_vertex;
    std::cin >> num_vertex;

    Graph g(num_vertex);
    for (Vertex i = 0; i < num_vertex; i++) {
        for (Vertex j = 0; j < num_vertex; j++) {
            DistT weight = 0;
            std::cin >> weight;
            g.AddEdge(i, j, weight);
        }
    }

    std::vector<std::vector<DistT>> new_path = g.GetPath();
    for (auto& i : new_path) {
        for (auto& j : i) {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
