//
// Created by Julian on 24.06.18.
//

#include "DecisionTree.hpp"

DecisionTree::DecisionTree(const Dataset& d) : dr(d), root_(Node()) {
  root_ = buildTree(dr.trainingData());
}

const Node DecisionTree::buildTree(const Data& rows) {
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
  print(make_shared<Node>(root_));
}

void DecisionTree::print(const shared_ptr<Node> root, string spacing) const {
  if (bool is_leaf = root->leaf() != nullptr; is_leaf) {
    const auto &leaf = root->leaf();
    std::cout << spacing + "Predict: "; Helper::print::print_map(leaf->predictions());
    return;
  }
  std::cout << spacing << root->question().toString(dr.labels()) << "\n";

  std::cout << spacing << "--> True: " << "\n";
  print(root->trueBranch(), spacing + "   ");

  std::cout << spacing << "--> False: " << "\n";
  print(root->falseBranch(), spacing + "   ");
}

void DecisionTree::generateGraph(const string filepath) const {
  GraphGenerator g(root_, dr.labels(), filepath);
}

void DecisionTree::test() const {
  TreeTest t(dr.testingData(), dr.labels(), root_);
}
