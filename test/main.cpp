#include "DecisionTree.hpp"

int main() {
  Dataset d;
  d.train.filename = "../test/data/fruit.csv";
  d.test.filename = "../test/data/fruit_test.csv";

  DecisionTree dt(d);
  dt.print();
  dt.test();
  dt.generateGraph("../graph.dot", VERBOSE);
  return 0;
}