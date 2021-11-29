#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

class DSU {
    int num_of_bridge_ = 0;
    int size_ = 0;
    std::vector<int> parent_;
    std::vector<int> rank_;

    void MakeSet();
    int FindSet(int);

public:
    explicit DSU(int);
    void Union(int, int);
    int NumEdges();
};

void DSU::MakeSet() {
    parent_[size_] = size_;
    size_++;
}
int DSU::FindSet(int v) {
    if (v == parent_[v]) {
        return v;
    }
    return parent_[v] = FindSet(parent_[v]);
}

DSU::DSU(int num_of_vertex) {
    parent_.resize(num_of_vertex);
    rank_.resize(num_of_vertex);
    for (int i = 0; i < num_of_vertex; i++) {
        MakeSet();
    }
}
void DSU::Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);
    if (size_ > 1) {
        num_of_bridge_++;
    }
    if (x != y) {
        size_--;
        if (rank_[x] < rank_[y]) {
            parent_[x] = y;
        } else if (rank_[y] < rank_[x]) {
            parent_[y] = x;
        } else {
            parent_[x] = y;
            rank_[y]++;
        }
    }
}
int DSU::NumEdges() {
    return num_of_bridge_;
}

int main() {
    int num_of_vertex = 0;
    int num_of_edges = 0;
    std::cin >> num_of_vertex >> num_of_edges;
    DSU island(num_of_vertex);
    for (int i = 0; i < num_of_edges; i++) {
        int first = 0;
        int second = 0;
        std::cin >> first >> second;
        island.Union(first, second);
    }
    std::cout << island.NumEdges();
    return 0;
}
