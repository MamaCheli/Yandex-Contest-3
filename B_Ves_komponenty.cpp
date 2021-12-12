#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

template <typename T>
class DSU {
    T num_of_bridge_ = 0;
    int size_ = 0;
    std::vector<T> parent_;
    std::vector<int> rank_;
    std::vector<T> weight_;

    T FindSet(T);
    void ChangeWeightAndParent(T, T, T);

public:
    explicit DSU(int);
    void Union(T, T, T);
    T GetWeight(T);
};

template <typename T>
T DSU<T>::FindSet(T v) {
    if (v == parent_[v]) {
        return v;
    }
    return parent_[v] = FindSet(parent_[v]);
}

template <typename T>
DSU<T>::DSU(int num_of_vertex) {
    parent_.resize(num_of_vertex + 1);
    rank_.resize(num_of_vertex + 1);
    weight_.resize(num_of_vertex + 1);
    for (int i = 0; i < num_of_vertex; i++) {
        parent_[size_] = size_;
        size_++;
        weight_[i] = 0;
    }
}

template <typename T>
void DSU<T>::ChangeWeightAndParent(T first, T second, T weight) {
    weight_[first] += weight_[second] + weight;
    parent_[second] = first;
}

template <typename T>
void DSU<T>::Union(T first, T second, T weight) {
    first = FindSet(first);
    second = FindSet(second);
    if (first != second) {
        size_--;
        if (rank_[first] < rank_[second]) {
            ChangeWeightAndParent(second, first, weight);
        } else if (rank_[second] < rank_[first]) {
            ChangeWeightAndParent(first, second, weight);
        } else {
            ChangeWeightAndParent(second, first, weight);
            rank_[second]++;
        }
    } else {
        weight_[first] += weight;
    }
}

template <typename T>
T DSU<T>::GetWeight(T v) {
    return weight_[FindSet(v)];
}

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int num_of_vertex;
    int num_of_command;
    std::cin >> num_of_vertex >> num_of_command;
    DSU<int> graph(num_of_vertex);
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
