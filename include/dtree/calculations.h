//
// Created by Julian on 24.06.18.
//

#ifndef DTREE_CALCULATIONS_H
#define DTREE_CALCULATIONS_H

#include <dtree/question.h>
#include <dtree/help.h>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_map>

namespace dtree::calculations {

std::tuple <Data, Data> partition(const Data &data, const Question &q);

float gini(const Data &data);

float info_gain(const Data &left, const Data &right, float current_uncertainty);

std::tuple<double, Question> find_best_split(const Data &rows);

VecS unique_values(const dtree::Data &data, size_t column);

ClassCounter class_counts(const Data &data);

} // namespace Calculations

#endif //DTREE_CALCULATIONS_H
