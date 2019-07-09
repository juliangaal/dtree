//
// Created by Julian on 25.06.18.
//

#ifndef DECISIONTREE_TREETEST_HPP
#define DECISIONTREE_TREETEST_HPP

#include <decision_tree/node.h>
#include <decision_tree/help.h>

namespace decision_tree::validation {

using ClassCounterScaled = std::unordered_map<std::string, float>;

ClassCounter testRow(const VecS &row, const std::unique_ptr<Node> &node);

ClassCounter classify(const VecS &row, const std::unique_ptr<Node> &node);

void print_prediction(const ClassCounter &counts);

void validate(const Data &testing_data, const VecS &labels, const std::unique_ptr<Node> &tree);

} // namespace validation

#endif //DECISIONTREE_TREETEST_HPP
