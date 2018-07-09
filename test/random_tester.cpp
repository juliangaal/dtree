#include "../lib/include/DecisionTree.hpp"

int main() {
  Dataset d;
  d.train.filename = "../data/iris.csv";
  d.test.filename = "../data/iris_test.csv";

  DecisionTree dt(d);
  dt.print();
  dt.test();
  dt.generateGraph("../../graph.dot");
  return 0;
}