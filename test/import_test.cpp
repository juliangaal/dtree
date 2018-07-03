//
// Created by Julian on 03.07.18.
// This exists fir travis only
//
#include <DecisionTree/DecisionTree.hpp>

int main(void) {
  Dataset d;
  d.train.filename = "../data/play_tennis.csv";
  d.test.filename = "../data/play_tennis_test.csv";

  DecisionTree dt(d);
  return 0;
}
