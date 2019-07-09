//
// Created by Julian on 29.06.18.
//

#ifndef DECISIONTREE_GRAPHELEMENTS_HPP
#define DECISIONTREE_GRAPHELEMENTS_HPP

#include <string>
#include <unordered_map>
#include <memory>

using branch = bool;
namespace decision_tree::graph_element {

std::string label(const std::string &label);

std::string box(const std::string &label, size_t hash);

std::string node(size_t hash);

std::string result(const std::unordered_map<std::string, int> &data, branch b);

}

#endif //DECISIONTREE_GRAPHELEMENTS_HPP
