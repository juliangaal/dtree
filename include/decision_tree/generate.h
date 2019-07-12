//
// Created by Julian on 25.06.18.
//

#ifndef DECISIONTREE_GRAPHGENERATOR_HPP
#define DECISIONTREE_GRAPHGENERATOR_HPP

#include <decision_tree/node.h>
#include <memory>
#include <filesystem>
#include <fstream>

namespace decision_tree::generate {

void init(const std::unique_ptr<Node> &root, const VecS &labels, const std::filesystem::path &filepath);

void traverse_generate(const std::unique_ptr<Node> &node, const VecS &labels, std::ofstream &file);

} // namespace decision_tree::generate

namespace decision_tree::graph_element {

std::string label(const std::string &label);

std::string box(const std::string &label, size_t hash);

std::string node(size_t hash);

std::string result(const std::unordered_map<std::string, int> &data, bool b);

} // namespace decision_tree::graph_element

#endif //DECISIONTREE_GRAPHGENERATOR_HPP
