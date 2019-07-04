#include "../lib/include/DecisionTree.hpp"

int main() {
  Dataset d{};
  d.train.filename = "../data/san_fran_vs_nyc.csv";
  d.test.filename = "../data/san_fran_vs_nyc_test.csv";

  DecisionTree dt(d);
  dt.test();
  dt.generateGraph("../../graph.dot");
  return 0;
}
