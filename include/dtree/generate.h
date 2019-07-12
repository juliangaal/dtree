//
// Created by Julian on 25.06.18.
//

#ifndef DTREE_GRAPHGENERATOR_HPP
#define DTREE_GRAPHGENERATOR_HPP

#include <dtree/node.h>
#include <memory>
#include <filesystem>
#include <fstream>

namespace dtree::generate {

void init(const std::unique_ptr<Node> &root, const VecS &labels, const std::filesystem::path &filepath);

void traverse_generate(const std::unique_ptr<Node> &node, const VecS &labels, std::ofstream &file);

} // namespace dtree::generate

namespace dtree::graph_element {

std::string label(const std::string &label);

std::string box(const std::string &label, size_t hash);

std::string node(size_t hash);

std::string result(const std::unordered_map<std::string, int> &data, bool b);

} // namespace dtree::graph_element

#endif //DTREE_GRAPHGENERATOR_HPP
