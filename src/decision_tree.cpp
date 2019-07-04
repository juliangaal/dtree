//
// Created by Julian on 24.06.18.
//

#include <decision_tree/decision_tree.hpp>

using namespace decision_tree;
using std::string;

DecisionTree::DecisionTree(const Dataset &d) : dr(d), root_(buildTree(dr.trainingData())) {}

const Node DecisionTree::buildTree(const Data &rows) {
    auto[gain, question] = calculations::find_best_split(rows);
    if (gain == 0.0) {
        return Node(rows);
    }

    const auto[true_rows, false_rows] = calculations::partition(rows, question);
    auto true_branch = buildTree(true_rows);
    auto false_branch = buildTree(false_rows);

    return Node(true_branch, false_branch, question);
}

void DecisionTree::print() const {
    print(std::make_shared<Node>(root_));
}

void DecisionTree::print(const std::shared_ptr<Node> root, string spacing) const {
    if (root->predicts()) {
        std::cout << spacing + "Predict: ";
        helpers::print::print_map(root->predictions().value());
        return;
    }

    std::cout << spacing << root->question().value().toString(dr.labels()) << "\n";

    std::cout << spacing << "--> True: " << "\n";
    print(root->trueBranch(), spacing + "   ");

    std::cout << spacing << "--> False: " << "\n";
    print(root->falseBranch(), spacing + "   ");
}

void DecisionTree::generateGraph(const string filepath) const {
    GraphGenerator g(root_, dr.labels(), filepath);
}

void DecisionTree::test() const {
    validation::validate(dr.testingData(), dr.labels(), std::make_shared<Node>(root_));
}
