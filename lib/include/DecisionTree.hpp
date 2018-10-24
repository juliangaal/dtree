//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_DECISIONTREE_HPP
#define DEC__ISIONTREE_DECISIONTREE_HPP

#include "Dataset.hpp"
#include "Node.hpp"
#include "Calculations.hpp"
#include "DataReader.hpp"
#include "GraphGenerator.hpp"
#include "TreeTest.hpp"

class DecisionTree {
 public:
  DecisionTree() = delete;
  explicit DecisionTree(const Dataset& d);

  void print() const;
  void test() const;
  void generateGraph(const std::string filepath) const;

  inline Data testingData() { return dr.testingData(); }
  inline std::shared_ptr<Node> root() { return std::make_shared<Node>(root_); }

 private:
  DataReader dr;
  const Node buildTree(const Data& rows);
  void print(const std::shared_ptr<Node> root, std::string spacing="") const;

  Node root_;
};

#endif //DEC__ISIONTREE_DECISIONTREE_HPP
