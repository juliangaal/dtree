//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_DATASET_HPP
#define DECISIONTREE_DATASET_HPP

#include <string>

namespace decision_tree {

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

} // namespace decision_tree

#endif //DECISIONTREE_DATASET_HPP
