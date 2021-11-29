#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

class DSU {
    int num_of_bridge_ = 0;
    int size_ = 0;
    std::vector<int> parent_;
    std::vector<int> rank_;
    std::vector<int> weight_;

    void MakeSet();
    int FindSet(int);

public:
    explicit DSU(int);
    void Union(int, int, int);
    int GetWeight(int);
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
    parent_.resize(num_of_vertex + 1);
    rank_.resize(num_of_vertex + 1);
    weight_.resize(num_of_vertex + 1);
    for (int i = 0; i < num_of_vertex; i++) {
        MakeSet();
        weight_[i] = 0;
    }
}
void DSU::Union(int x, int y, int weight) {
    x = FindSet(x);
    y = FindSet(y);
    if (x != y) {
        size_--;
        if (rank_[x] < rank_[y]) {
            weight_[y] += weight_[x] + weight;
            parent_[x] = y;
        } else if (rank_[y] < rank_[x]) {
            weight_[x] += weight_[y] + weight;
            parent_[y] = x;
        } else {
            weight_[y] += weight_[x] + weight;
            parent_[x] = y;
            rank_[y]++;
        }
    } else {
        weight_[x] += weight;
    }
}
int DSU::GetWeight(int v) {
    return weight_[FindSet(v)];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int num_of_vertex;
    int num_of_command;
    std::cin >> num_of_vertex >> num_of_command;
    DSU graph(num_of_vertex);
    for (int i = 0; i < num_of_command; i++) {
        int command;
        std::cin >> command;
        if (command == 1) {
            int first;
            int second;
            int weight;
            std::cin >> first >> second >> weight;
            graph.Union(first, second, weight);
        } else {
            int comp;
            std::cin >> comp;
            std::cout << graph.GetWeight(comp) << "\n";
        }
    }
    return 0;
}
