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

using std::tuple;
using std::pair;
using std::forward_as_tuple;
using std::vector;
using std::string;
using std::unordered_map;
using Data = vector<vector<string>>;
using ClassCounter = unordered_map<string, int>;

namespace Calculations {

tuple<const Data, const Data> partition(const Data &data, const Question &q);

const double gini(const Data &data);

const double info_gain(const Data &left, const Data &right, double current_uncertainty);

tuple<const double, const Question> find_best_split(const Data &rows);

const VecS uniqueValues(const Data &data, const size_t column);

const ClassCounter classCounts(const Data &data);

} // namespace Calculations

#endif //DEC__ISIONTREE_CALCULATIONS_HPP
