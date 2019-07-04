//
// Created by Julian on 25.06.18.
//

#include <decision_tree/graph_elements.hpp>
#include <decision_tree/graph_generator.hpp>
#include <decision_tree/helpers.hpp>
#include <iostream>
#include <vector>

using namespace decision_tree;
namespace elem = decision_tree::graph_element;

using std::string;
using std::vector;
using std::make_shared;
using std::shared_ptr;

GraphGenerator::GraphGenerator(const Node &root, const vector<string> labels, const string filepath) :
        labels_(labels) {
    generate(make_shared<Node>(root), filepath);
}

void GraphGenerator::generate(shared_ptr<Node> root, const string &filepath) {
    std::ofstream myfile;
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

void GraphGenerator::traverseTree(shared_ptr<Node> node, std::ofstream &file) {
    static const string spacing = "   ";
    static const string connector = " -> ";
    if (node == nullptr)
        return;

    if (node->predicts()) {
        return;
    }

    file << spacing << elem::box(node->question().value().toString(labels_)) << connector;

    if (node->trueBranch()->predicts()) {
        file << elem::result(node->trueBranch()->predictions().value(), true);
    } else {
        file << elem::node(node->trueBranch()->question().value().toString(labels_)) << elem::label("True");
    }

    file << spacing << elem::node(node->question().value().toString(labels_)) << connector;

    if (node->falseBranch()->predicts()) {
        file << elem::result(node->falseBranch()->predictions().value(), false);
    } else {
        file << elem::node(node->falseBranch()->question().value().toString(labels_)) << elem::label("False");
    }

    traverseTree(node->trueBranch(), file);
    traverseTree(node->falseBranch(), file);
}
