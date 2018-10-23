//
// Created by Julian on 24.06.18.
//

#ifndef DEC__ISIONTREE_CALCULATIONS_HPP
#define DEC__ISIONTREE_CALCULATIONS_HPP

#include <tuple>
#include <vector>
#include <string>
#include <unordered_map>
#include "Question.hpp"

using Data = std::vector<std::vector<std::string>>;
using ClassCounter = std::unordered_map<std::string, int>;

namespace Calculations {

std::tuple<const Data, const Data> partition(const Data &data, const Question &q);

const double gini(const Data &data);

const double info_gain(const Data &left, const Data &right, double current_uncertainty);

std::tuple<const double, const Question> find_best_split(const Data &rows);

const VecS uniqueValues(const Data &data, const size_t column);

const ClassCounter classCounts(const Data &data);

} // namespace Calculations

#endif //DEC__ISIONTREE_CALCULATIONS_HPP
