//
// Created by Julian on 25.06.18.
//

#include <iostream>
#include <string>
#include <vector>
#include "GraphElements.hpp"
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

//  file << spacing << GraphElement::node(node->question_.toString(labels))
  file << spacing << GraphElement::box(node->question_.toString(labels)) << connector;

  if (bool is_leaf = node->true_branch_->leaf_ != nullptr; is_leaf) {
    file << GraphElement::result(node->true_branch_->leaf_->predictions_, true);
  } else {
    file << GraphElement::node(node->true_branch_->question_.toString(labels)) << GraphElement::label("True");
  }

  file << spacing << GraphElement::node(node->question_.toString(labels)) << connector;

  if (bool is_leaf = node->false_branch_->leaf_ != nullptr; is_leaf) {
    file << GraphElement::result(node->false_branch_->leaf_->predictions_, false);
  } else {
    file << GraphElement::node(node->false_branch_->question_.toString(labels)) << GraphElement::label("False");
  }

  traverseTree(node->true_branch_, file);
  traverseTree(node->false_branch_, file);
}
