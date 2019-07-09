//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_HELPER_HPP
#define DECISIONTREE_HELPER_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>
#include <iterator>
#include <fmt/format.h>
#include <iostream>

namespace decision_tree {

using ClassCounter = std::unordered_map<std::string, int>;
using Data = std::vector<std::vector<std::string>>;
using VecS = std::vector<std::string>;

namespace help::print {

template<typename T>
void print_vector(const std::vector<T> &vec) {
    if (vec.empty())
        return;

    fmt::print("[ ");
    std::copy(begin(vec), std::end(vec), std::ostream_iterator<T>(std::cout, " "));
    fmt::print(" ]\n");
}

template<typename K, typename V>
void print_map(const std::unordered_map<K, V> &counter) {
    if (counter.empty())
        return;

    for (const auto&[key, val]: counter) {
        fmt::print("[{:>3}, {:0.1f}%", key, val);
        if (counter.size() > 1) fmt::print(" | ");
    }

    fmt::print(" ]\n");
}

} // namespace decision_tree::help::print

} // namespace decision_tree

#endif //DECISIONTREE_HELPER_HPP
