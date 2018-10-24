//
// Created by Julian on 25.06.18.
//

#include "TreeTest.hpp"

using std::make_shared;
using std::shared_ptr;

TreeTest::TreeTest(const Data& testing_data, const VecS& labels, const Node &root) {
  test(testing_data, labels, make_shared<Node>(root));
}

const ClassCounter TreeTest::classify(const VecS& row, shared_ptr<Node> node) const {
  if (bool is_leaf = node->leaf() != nullptr; is_leaf) {
    const auto &leaf = node->leaf();
    return leaf->predictions();
  }

  if (node->question().match(row))
    return classify(row, node->trueBranch());
  else
    return classify(row, node->falseBranch());
}

void TreeTest::print_leaf(ClassCounter counts) const {
  const float total = static_cast<float>(Helper::tree::mapValueSum(counts)); //[](const size_t previous, const auto& p) { return previous+p.second; });
  ClassCounterScaled scale;

  for (const auto& [key, val]: counts)
  scale[key] = std::to_string(val / total * 100) + "%";

  Helper::print::print_map(scale);
}

const ClassCounter TreeTest::testRow(const VecS& row, shared_ptr<Node> node) const {
  return classify(row, node);
}

void TreeTest::test(const Data& testing_data, const VecS& labels, shared_ptr<Node> tree) const {
  for (const auto& row: testing_data) {
    static size_t last = row.size()-1;
    std::cout << "Actual: " << labels[last] << " - " << row[last] << "\tPrediction: "; print_leaf(classify(row, tree));
  }
}
