//
// Created by Julian on 25.06.18.
//

#include <iostream>
#include <vector>
#include "GraphElements.hpp"
#include "GraphGenerator.hpp"
#include "Helper.hpp"

using std::string;
using std::vector;

GraphGenerator::GraphGenerator(const Node &root, const vector<string> labels, const string filepath) :
  labels_(labels) {
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

  if (bool is_leaf = node->leaf() != nullptr; is_leaf) {
    return;
  }

  file << spacing << GraphElement::box(node->question().toString(labels_)) << connector;

  if (bool is_leaf = node->trueBranch()->leaf() != nullptr; is_leaf) {
    file << GraphElement::result(node->trueBranch()->leaf()->predictions(), true);
  } else {
    file << GraphElement::node(node->trueBranch()->question().toString(labels_)) << GraphElement::label("True");
  }

  file << spacing << GraphElement::node(node->question().toString(labels_)) << connector;

  if (bool is_leaf = node->falseBranch()->leaf() != nullptr; is_leaf) {
    file << GraphElement::result(node->falseBranch()->leaf()->predictions(), false);
  } else {
    file << GraphElement::node(node->falseBranch()->question().toString(labels_)) << GraphElement::label("False");
  }

  traverseTree(node->trueBranch(), file);
  traverseTree(node->falseBranch(), file);
}
