#include <iostream>
#include <vector>

using Vertex = int64_t;
using DistT = int64_t;

const int64_t kInf = 1e9;

class Graph {
    Vertex num_vertex_;
    std::vector<std::vector<Vertex>> matrix_;

    std::vector<DistT> dist_;

public:
    explicit Graph(Vertex);
    void AddEdge(Vertex, Vertex, DistT);
    DistT Calculation(Vertex, Vertex);
};

Graph::Graph(Vertex num_vertex) {
    num_vertex_ = num_vertex;
    matrix_.resize(num_vertex_);
    dist_.resize(num_vertex_);
    for (Vertex i = 0; i < num_vertex_; i++) {
        matrix_[i].resize(num_vertex_);
        dist_[i] = kInf;
    }
}

void Graph::AddEdge(Vertex first, Vertex second, DistT weight) {
    matrix_[first][second] = weight;
}

DistT Graph::Calculation(Vertex start, Vertex finish) {
    std::vector<bool> visit(num_vertex_, false);

    Vertex curr = start;
    dist_[curr] = 0;
    while (true) {
        visit[curr] = true;
        for (Vertex i = 0; i < num_vertex_; ++i) {
            if (curr != i) {
                int way = matrix_[curr][i];
                if (way != -1) {
                    dist_[i] = std::min(dist_[i], dist_[curr] + way);
                }
            }
        }
        DistT mindist = kInf;
        Vertex minindex = -1;
        for (Vertex i = 0; i < num_vertex_; i++) {
            if (!visit[i]) {
                if (mindist > dist_[i]) {
                    mindist = dist_[i];
                    minindex = i;
                }
            }
        }
        if (minindex == -1) {
            break;
        }
        curr = minindex;
    }

    if (dist_[finish] == kInf) {
        return -1;
    }
    return dist_[finish];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    Vertex num_vertex;
    Vertex start;
    Vertex finish;
    std::cin >> num_vertex >> start >> finish;
    start--;
    finish--;
    Graph g(num_vertex);

    for (Vertex i = 0; i < num_vertex; i++) {
        for (Vertex j = 0; j < num_vertex; j++) {
            DistT w;
            std::cin >> w;
            g.AddEdge(i, j, w);
        }
    }

    std::cout << g.Calculation(start, finish);
    return 0;
}
