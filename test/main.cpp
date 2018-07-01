#include "DecisionTree.hpp"

int main() {
  Dataset d;
  d.train.filename = "../test/data/iris.csv";
  d.test.filename = "../test/data/iris_test.csv";

  DecisionTree dt(d);
  dt.print();
  dt.test();
  dt.generateGraph("../graph.dot");
  return 0;
}