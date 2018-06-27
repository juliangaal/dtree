//
// Created by Julian on 25.06.18.
//

#ifndef DEC__ISIONTREE_TREETEST_HPP
#define DEC__ISIONTREE_TREETEST_HPP

#include "Node.hpp"
#include "Helper.hpp"

using ClassCounterScaled = unordered_map<string, string>;

class TreeTest {
 public:
  TreeTest() = default;
  TreeTest(const Data& testing_data, const VecS& labels, const Node &root);
  ~TreeTest() = default;

  ClassCounter testRow(const VecS& row, shared_ptr<Node> node);

 private:

  const shared_ptr<Node> root_node;

  ClassCounter classify(const VecS& row, shared_ptr<Node> node);

  void print_leaf(ClassCounter counts);

  void test(const Data& testing_data, const VecS& labels, shared_ptr<Node> tree);
};

#endif //DEC__ISIONTREE_TREETEST_HPP
