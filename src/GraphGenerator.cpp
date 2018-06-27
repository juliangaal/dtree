//
// Created by Julian on 25.06.18.
//

#include <iostream>
#include <string>
#include <vector>
#include "GraphGenerator.hpp"
#include "Helper.hpp"

using std::string;
using std::vector;

GraphGenerator::GraphGenerator(const Node &root, const vector<string> labels, const string filepath) :
  labels(labels) {
  generate(make_shared<Node>(root), filepath);
}

void GraphGenerator::generate(shared_ptr<Node> root, const string& filepath) {
  ofstream myfile;
  myfile.open(filepath);

  if (!myfile.is_open()) {
    std::cerr << "Couldn't open " << filepath << ". Can't create Graphviz dot file.\n";
    return;
  }

  myfile << "digraph {\n";
  traverseTree(root, myfile);
  myfile << "}";
  myfile.close();
}

void GraphGenerator::traverseTree(shared_ptr<Node> node, ofstream &file) {
  static const string spacing = "   ";
  static const string connector = " -> ";
  if (node == nullptr)
    return;

  if (bool is_leaf = node->leaf_ != nullptr; is_leaf) {
    return;
  }

  file << spacing << this->node(node->question_.toString(labels)) << connector;

  if (bool is_leaf = node->true_branch_->leaf_ != nullptr; is_leaf) {
    file << result(node->true_branch_->leaf_->predictions_) << label("True");
  } else {
    file << this->node(node->true_branch_->question_.toString(labels)) << label("True");
  }

  file << spacing << this->node(node->question_.toString(labels)) << connector;

  if (bool is_leaf = node->false_branch_->leaf_ != nullptr; is_leaf) {
    file << result(node->false_branch_->leaf_->predictions_) << label("False");
  } else {
    file << this->node(node->false_branch_->question_.toString(labels)) << label("False");
  }

  traverseTree(node->true_branch_, file);
  traverseTree(node->false_branch_, file);
}

string GraphGenerator::label(const string &label) const {
  return "[label=\"" + label + "\"];\n";
}

string GraphGenerator::node(const string& question) const {
  return "\"" + question + "\"";
}

string GraphGenerator::result(unordered_map<string, int> data) const {
  string result = "\"";
  double sum = Helper::tree::mapValueSum(data);
  size_t map_size = data.size();
  size_t counter = 1;

  for (const auto& [k, v]: data) {
    result += k + ": " + std::to_string(v / sum * 100) + "% ";
    if (counter++ < map_size)
      result += "\\n ";
  }
  return result += "\"";
}
