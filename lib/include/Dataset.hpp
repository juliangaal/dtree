//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_DATASET_HPP
#define DEC__ISIONTREE_DATASET_HPP

#include <string>

struct Train {
  std::string filename;
};

struct Test {
  std::string filename;
};

struct Dataset {
  Train train;
  Test test;
  std::string result_label;
};

#endif //DEC__ISIONTREE_DATASET_HPP
