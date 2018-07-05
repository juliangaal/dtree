//
// Created by Julian on 24.06.18.
//

#include "DecisionTree.hpp"

DecisionTree::DecisionTree(Dataset& d) : dr(d), root(Node()) {
  root = buildTree(dr.trainingData());
}

Node DecisionTree::buildTree(const Data& rows) {
  auto [gain, question] = Calculations::find_best_split(rows);
  if (gain == 0.0) {
    return Node(Leaf(Calculations::classCounts(rows)));
  }

  const auto [true_rows, false_rows] = Calculations::partition(rows, question);
  auto true_branch = buildTree(true_rows);
  auto false_branch = buildTree(false_rows);

  return Node(true_branch, false_branch, question);
}

void DecisionTree::print() const {
  print(make_shared<Node>(root));
}

void DecisionTree::print(shared_ptr<Node> root, string spacing) const {
  if (bool is_leaf = root->leaf_ != nullptr; is_leaf) {
    const auto &leaf = root->leaf_;
    std::cout << spacing + "Predict: "; Helper::print::print_map(leaf->predictions_);
    return;
  }
  std::cout << spacing << root->question_.toString(dr.labels_()) << "\n";

  std::cout << spacing << "--> True: " << "\n";
  print(root->true_branch_, spacing + "   ");

  std::cout << spacing << "--> False: " << "\n";
  print(root->false_branch_, spacing + "   ");
}

void DecisionTree::generateGraph(const string filepath) const {
  GraphGenerator g(root, dr.labels_(), filepath);
}

void DecisionTree::test() const {
  TreeTest t(dr.testingData(), dr.labels_(), root);
}
