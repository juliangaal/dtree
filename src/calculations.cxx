//
// Created by Julian on 24.06.18.
//
#include <decision_tree/calculations.h>
#include <decision_tree/help.h>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace decision_tree;

using std::tuple;
using std::string;
using std::unordered_map;

tuple<const Data, const Data> calculations::partition(const Data &data, const Question &q) {
    Data true_rows;
    Data false_rows;

    for (const auto &row: data) {
        if (q.match(row))
            true_rows.push_back(row);
        else
            false_rows.push_back(row);
    }
    return {true_rows, false_rows};
}

const double calculations::gini(const Data &data) {
    const auto &counts = class_counts(data);
    double impurity = 1.0;

    for (const auto&[decision, freq]: counts) {
        double prob_of_lbl = freq / static_cast<double>(data.size());
        impurity -= std::pow(prob_of_lbl, 2);
    }

    return impurity;
}

const double calculations::info_gain(const Data &left, const Data &right, double current_uncertainty) {
    const auto &p = static_cast<double>(left.size()) / (left.size() + right.size());
    return current_uncertainty - p * gini(left) - (1 - p) * gini(right);
}

tuple<const double, const Question> calculations::find_best_split(const Data &rows) {
    double best_gain = 0.0;  // keep track of the best information gain
    auto best_question = Question();  //keep train of the feature / value that produced it
    double current_uncertainty = gini(rows);
    size_t n_features = rows[0].size() - 1;  //number of columns

    #pragma omp parallel for num_threads(5)
    for (size_t column = 0; column < n_features; column++) {
        const auto values = unique_values(rows, column);

        for (const auto &val: values) {
            const Question q(column, val);

            const auto&[true_rows, false_rows] = partition(rows, q);

            if (true_rows.empty() || false_rows.empty())
                continue;

            const auto &gain = info_gain(true_rows, false_rows, current_uncertainty);

            #pragma omp critical
            {
                if (gain >= best_gain) {
                    best_gain = gain;
                    best_question = q;
                }
            }
        }
    }
    return {best_gain, best_question};
}

const VecS calculations::unique_values(const Data &data, const size_t column) {
    VecS unique_vals;

    ClassCounter counter;
    for (const auto &rows: data) {
        const string &decision = rows[column];
        counter[decision] += 0;
    }

    std::transform(begin(counter), std::end(counter), std::back_inserter(unique_vals),
                   [](const auto &kv) { return kv.first; });
    return unique_vals;
}

const ClassCounter calculations::class_counts(const Data &data) {
    ClassCounter counter;
    for (const auto &rows: data) {
        const string decision = rows.back();
        counter[decision] += 1;
    }
    return counter;
}
