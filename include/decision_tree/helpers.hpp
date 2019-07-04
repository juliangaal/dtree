//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_HELPER_HPP
#define DECISIONTREE_HELPER_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <numeric>
#include <iterator>

namespace decision_tree {

using ClassCounter = std::unordered_map<std::string, int>;
using Data = std::vector<std::vector<std::string>>;
using VecS = std::vector<std::string>;

namespace helpers {

namespace iterators {

struct AddMapValue {
    template<typename S, typename T>
    int operator()(const S previous, const T map) const {
        return previous + map.second;
    }
};

} // namespace iterators

namespace tree {

template<typename T>
int mapValueSum(std::unordered_map<T, int> counts) {
    return std::accumulate(begin(counts), std::end(counts), 0, [](const auto& prev, const auto& curr) {
        return prev + curr.second;
    });
}

} // namespace tree

namespace print {
template<typename T>
void print_vector(const std::vector<T> &vec) {
    if (vec.empty())
        return;

    std::cout << "{ ";
    std::copy(begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, " "));
    std::cout << "}\n";
}

template<typename K, typename V>
void print_map(const std::unordered_map<K, V> &counter) {
    if (counter.empty())
        return;

    std::cout << "{ ";
    for (const auto&[key, val]: counter) {
        std::cout << key << ": " << val << " ";
    }
    std::cout << "}" << "\n";
}

} // namespace print

} // namespace decision_tree::helpers

} // namespace decision_tree

#endif //DECISIONTREE_HELPER_HPP
