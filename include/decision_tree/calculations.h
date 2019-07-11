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

std::tuple <Data, Data> partition(const Data &data, const Question &q);

float gini(const Data &data);

float info_gain(const Data &left, const Data &right, float current_uncertainty);

std::tuple<float, Question> find_best_split(const Data &rows);

VecS unique_values(const decision_tree::Data &data, const size_t column);

ClassCounter class_counts(const Data &data);

} // namespace Calculations

#endif //DECISIONTREE_CALCULATIONS_H
