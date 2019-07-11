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

tuple<Data, Data> calculations::partition(const Data &data, const Question &q) {
    Data true_rows{};
    Data false_rows{};
    true_rows.reserve(data.size()/2);
    false_rows.reserve(data.size()/2);

    for (const auto &row: data) {
        if (q.match(row))
            true_rows.push_back(row);
        else
            false_rows.push_back(row);
    }

    return {true_rows, false_rows};
}

float calculations::gini(const Data &data) {
    const auto &counts = class_counts(data);
    float impurity = 1.0f;

    for (const auto&[decision, freq]: counts) {
        double prob_of_lbl = freq / static_cast<float>(data.size());
        impurity -= std::pow(prob_of_lbl, 2.f);
    }

    return impurity;
}

float calculations::info_gain(const Data &left, const Data &right, float current_uncertainty) {
    const auto p = static_cast<float>(left.size()) / (left.size() + right.size());
    return current_uncertainty - p * gini(left) - (1 - p) * gini(right);
}

tuple<float, Question> calculations::find_best_split(const Data &rows) {
    float best_gain = 0.0f;  // keep track of the best information gain
    auto best_question = Question();  //keep train of the feature / value that produced it
    const float current_uncertainty = gini(rows);
    size_t n_features = rows.back().size() - 1;  //number of columns

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

VecS calculations::unique_values(const Data &data, const size_t column) {
    VecS unique_vals;

    ClassCounter counter;
    for (const auto &rows: data) {
        const string &decision = rows.at(column);
        counter.insert({decision, 0});
    }

    unique_vals.reserve(counter.size());

    std::transform(begin(counter), std::end(counter), std::back_inserter(unique_vals),
                   [](const auto &kv) { return kv.first; });
    return unique_vals;
}

ClassCounter calculations::class_counts(const Data &data) {
    ClassCounter counter;
    counter.reserve(data.size()/4);

    for (const auto& row: data) {
        const string decision = row.back();
        counter[decision] += 1;
    }

    return counter;
}
