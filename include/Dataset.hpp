//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_DATASET_HPP
#define DEC__ISIONTREE_DATASET_HPP

#include <string>

using std::string;

struct Train {
  string filename;
};

struct Test {
  string filename;
};

struct Dataset {
  Train train;
  Test test;
};

#endif //DEC__ISIONTREE_DATASET_HPP
