//
// Created by Julian on 24.06.18.
//

#include <decision_tree/decision_tree.h>
#include <fmt/format.h>

using namespace decision_tree;
using std::string;

DecisionTree::DecisionTree(const TrainingSet &trainset, const TestingSet &testset)
        : dr(trainset, testset), root_(build_tree(dr.training_data())) {}

std::unique_ptr<Node> DecisionTree::build_tree(const Data &rows) {
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
    print_node(root_);
}

void DecisionTree::print_node(const std::unique_ptr<Node> &root, string spacing) const {
    if (root->predicts()) {
        fmt::print("{}{}", spacing, "Predict:");
        help::print::print_map(root->predictions().value());
        return;
    }

    fmt::print("{}{}\n", spacing, root->question().value().toString(dr.labels()));

    fmt::print("{}--> True:\n", spacing);
    print_node(root->true_branch(), spacing + "   ");

    fmt::print("{}--> False:\n", spacing);
    print_node(root->false_branch(), spacing + "   ");
}

void DecisionTree::generate_graph(const string filepath) const {
    generate::init(root_, dr.labels(), filepath);
}

void DecisionTree::test() const {
    validation::validate(dr.testing_data(), dr.labels(), root_);
}
