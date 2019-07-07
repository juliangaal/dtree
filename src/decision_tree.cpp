//
// Created by Julian on 24.06.18.
//

#include <decision_tree/decision_tree.hpp>

using namespace decision_tree;
using std::string;

DecisionTree::DecisionTree(const TrainingSet &trainset, const TestingSet &testset)
        : dr(trainset, testset), root_(buildTree(dr.trainingData())) {}

std::unique_ptr<Node> DecisionTree::buildTree(const Data &rows) {
    auto[gain, question] = calculations::find_best_split(rows);
    if (gain == 0.0) {
        return std::make_unique<Node>(rows);
    }

    const auto[true_rows, false_rows] = calculations::partition(rows, question);
    auto true_branch = buildTree(true_rows);
    auto false_branch = buildTree(false_rows);

    return std::make_unique<Node>(std::move(true_branch), std::move(false_branch), question);
}

void DecisionTree::print_tree() const {
    print_node(root_);
}

void DecisionTree::print_node(const std::unique_ptr<Node> &root, string spacing) const {
    if (root->predicts()) {
        std::cout << spacing + "Predict: ";
        helpers::print::print_map(root->predictions().value());
        return;
    }

    std::cout << spacing << root->question().value().toString(dr.labels()) << "\n";

    std::cout << spacing << "--> True: " << "\n";
    print_node(root->trueBranch(), spacing + "   ");

    std::cout << spacing << "--> False: " << "\n";
    print_node(root->falseBranch(), spacing + "   ");
}

void DecisionTree::generateGraph(const string filepath) const {
    GraphGenerator g(root_, dr.labels(), filepath);
}

void DecisionTree::test() const {
    validation::validate(dr.testingData(), dr.labels(), root_);
}
