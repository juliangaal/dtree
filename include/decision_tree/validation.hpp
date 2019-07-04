//
// Created by Julian on 25.06.18.
//

#ifndef DECISIONTREE_TREETEST_HPP
#define DECISIONTREE_TREETEST_HPP

#include <decision_tree/node.hpp>
#include <decision_tree/helpers.hpp>

namespace decision_tree::validation {

using ClassCounterScaled = std::unordered_map<std::string, std::string>;

ClassCounter testRow(const VecS &row, std::shared_ptr<Node> node);

ClassCounter classify(const VecS &row, std::shared_ptr<Node> node);

void print_prediction(ClassCounter counts);

void validate(const Data &testing_data, const VecS &labels, std::shared_ptr<Node> tree);

} // namespace validation

#endif //DECISIONTREE_TREETEST_HPP
