//
// Created by Julian on 24.06.18.
//

#ifndef DECISIONTREE_CALCULATIONS_H
#define DECISIONTREE_CALCULATIONS_H

#include <decision_tree/question.h>
#include <decision_tree/help.h>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_map>

namespace decision_tree::calculations {

std::tuple<const Data, const Data> partition(const Data &data, const Question &q);

const double gini(const Data &data);

const double info_gain(const Data &left, const Data &right, double current_uncertainty);

std::tuple<const double, const Question> find_best_split(const Data &rows);

const VecS unique_values(const decision_tree::Data &data, const size_t column);

const ClassCounter class_counts(const Data &data);

} // namespace Calculations

#endif //DECISIONTREE_CALCULATIONS_H
