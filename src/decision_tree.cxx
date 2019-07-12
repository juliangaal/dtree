//
// Created by Julian on 24.06.18.
//

#include <decision_tree/decision_tree.h>
#include <fmt/format.h>
#include <filesystem>
#include <tuple>

namespace fs = std::filesystem;
using namespace decision_tree;
using std::string;

DecisionTree::DecisionTree(const TrainingSet &trainset, const TestingSet &testset)
        : dr{trainset, testset},  size_{}, root_{build_tree(dr.training_data())} {
    fmt::print("> Generated decision tree with {} from {} training data points\n", size_, dr.training_data().size());
}

std::unique_ptr<Node> DecisionTree::build_tree(const Data &rows) {
    ++size_;

    auto[gain, question] = calculations::find_best_split(rows);
    if (gain == 0.0) {
        return std::make_unique<Node>(rows);
    }

    const auto[true_rows, false_rows] = calculations::partition(rows, question);
    auto true_branch = build_tree(true_rows);
    auto false_branch = build_tree(false_rows);

    return std::make_unique<Node>(std::move(true_branch), std::move(false_branch), question);
}

void DecisionTree::print_tree() const {
    std::string spacing{};
    rec_print_node(root_, spacing);
}

void DecisionTree::rec_print_node(const std::unique_ptr<Node> &root, string &spacing) const {
    if (root->predicts()) {
        fmt::print("{}{}", spacing, "Predict:");
        help::print::print_map(root->predictions().value());
        return;
    }

    spacing += "   ";

    fmt::print("{}{}\n", spacing, root->question().value().toString(dr.labels()));

    fmt::print("{}--> True:\n", spacing);
    rec_print_node(root->true_branch(), spacing);

    fmt::print("{}--> False:\n", spacing);
    rec_print_node(root->false_branch(), spacing);
}

void DecisionTree::generate_graph(const fs::path &file) const {
    generate::init(root_, dr.labels(), file);
    fmt::print("> Generated Graphviz file {}\n", file.string());
}

void DecisionTree::test() const {
    validation::validate(dr.testing_data(), dr.labels(), root_);
}
