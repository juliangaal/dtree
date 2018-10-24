//
// Created by Julian on 26.06.18.
//

#ifndef DEC_ISIONTREE_TEST_HPP
#define DEC_ISIONTREE_TEST_HPP

#include <DecisionTree/DecisionTree.hpp>
#include <memory>

class Tests {
 public:
  Tests();
  ~Tests() = default;

 private:
  void testTree(const Data& testing_data, std::shared_ptr<Node> tree) const;
  void testGenerator(DecisionTree& dtree, const std::string filename="test_graph.dot") const;
  bool fileExists(const std::string& filename) const;
  bool lineNumsMatch(const std::string& filename) const;
};

#endif //DEC_ISIONTREE_TEST_HPP
