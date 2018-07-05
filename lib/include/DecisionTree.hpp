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
  DecisionTree(Dataset& d);

  void print() const;
  void test() const;
  void generateGraph(const string filepath) const;

  inline Data trainingData() { return dr.trainingData(); }
  inline Data testingData() { return dr.testingData(); }
  inline shared_ptr<Node> root_() { return make_shared<Node>(root); }

 private:
  DataReader dr;
  Node buildTree(const Data& rows);
  void print(shared_ptr<Node> root, string spacing="") const;

  Node root;
};

#endif //DEC__ISIONTREE_DECISIONTREE_HPP
