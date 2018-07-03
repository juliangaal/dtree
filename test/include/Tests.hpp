//
// Created by Julian on 26.06.18.
//

#ifndef DEC_ISIONTREE_TEST_HPP
#define DEC_ISIONTREE_TEST_HPP

#include <DecisionTree/DecisionTree.hpp>
#include <fstream>
#include <algorithm>

using std::ifstream;

class Tests {
 public:
  Tests();
  ~Tests() = default;

 private:
  void testTree(const Data& testing_data, shared_ptr<Node> tree) const;
  void testGenerator(DecisionTree& dtree, const string filename="test_graph.dot") const;
  bool fileExists(const string& filename) const;
  bool lineNumsMatch(const string& filename) const;
};

#endif //DEC_ISIONTREE_TEST_HPP
