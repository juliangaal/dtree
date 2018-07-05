#include "../lib/include/DecisionTree.hpp"

int main() {
  Dataset d;
  d.train.filename = "../data/fruit.csv";
  d.test.filename = "../data/fruit_test.csv";

  DecisionTree dt(d);
  dt.print();
  dt.test();
  dt.generateGraph("../../graph.dot");
  return 0;
}