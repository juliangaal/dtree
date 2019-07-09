//
// Created by Julian on 25.06.18.
//

#include <decision_tree/graph_elements.hpp>
#include <decision_tree/graph_generator.hpp>
#include <decision_tree/helpers.hpp>
#include <queue>
#include <vector>
#include <fmt/format.h>

using namespace decision_tree;
namespace elem = decision_tree::graph_element;

using std::string;
using std::vector;

GraphGenerator::GraphGenerator(const std::unique_ptr<Node> &root, const vector<string>& labels, string filepath) :
        labels_(labels) {
    generate(root, filepath);
}

void GraphGenerator::generate(const std::unique_ptr<Node>& root, const std::string &filepath) {
    std::ofstream myfile;
    myfile.open(filepath);

    if (!myfile.is_open()) {
        fmt::print("Couldn't open {}. Can't create Graphviz dot file.\n", filepath);
        return;
    }

    myfile << "digraph {\n";
    traverseTreeDFS(root, myfile);
    myfile << "}";
    myfile.close();

//    traverseTreeBFS(root, myfile);
}

void GraphGenerator::traverseTreeDFS(const std::unique_ptr<Node>& node, std::ofstream &file) {
    static const string spacing = "   ";
    static const string connector = " -> ";
    if (node == nullptr)
        return;

    if (node->predicts())
        return;

    const auto question = node->question().value().toString(labels_);
    const auto hash = node->hash(labels_);

    file << spacing << elem::box(question, hash);
    file << spacing << elem::node(hash) << connector;

    if (node->trueBranch()->predicts()) {
        file << elem::result(node->trueBranch()->predictions().value(), true);
    } else {
        file << elem::node(node->trueBranch()->hash(labels_)) << elem::label("True");
    }

    file << spacing << elem::node(hash) << connector;

    if (node->falseBranch()->predicts()) {
        file << elem::result(node->falseBranch()->predictions().value(), false);
    } else {
        file << elem::node(node->falseBranch()->hash(labels_)) << elem::label("False");
    }

    traverseTreeDFS(node->trueBranch(), file);
    traverseTreeDFS(node->falseBranch(), file);
}

void GraphGenerator::traverseTreeBFS(const std::unique_ptr<Node>& node, std::ofstream &file, size_t depth) {
    std::queue<std::reference_wrapper<const std::unique_ptr<Node>>> queue;

    if (node == nullptr) {
        fmt::print("{}", "NULL");
        return;
    }

    queue.push(std::cref(node));

    while (!queue.empty()) {
        const auto& front = queue.front().get();
        queue.pop();

        if (!front->predicts()) fmt::print("Node ({}) {}\n", depth, front->question().value().toString(labels_));

        if (front->trueBranch() && !front->trueBranch()->predicts()) {
            fmt::print("  - True -> {}\n", front->trueBranch()->question().value().toString(labels_));
            queue.push(std::cref(front->trueBranch()));
        }

        if (front->falseBranch() && !front->falseBranch()->predicts()) {
            fmt::print("  - False -> {}\n", front->falseBranch()->question().value().toString(labels_));
            queue.push(std::cref(front->falseBranch()));
        }
    }
}

