//
// Created by Julian on 03.07.18.
//
#include <DecisionTree/DecisionTree.hpp>

int main(void) {
  Dataset d;
  d.train.filename = "data/san_fran_vs_nyc.csv";
  d.test.filename = "data/san_fran_vs_nyc_test.csv";

  DecisionTree dt(d);
  return 0;
}
