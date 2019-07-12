/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 *For more information, please refer to <http://unlicense.org>
*/
#include <dtree/calculations.h>
#include <dtree/help.h>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace dtree;

using std::tuple;
using std::string;
using std::unordered_map;

tuple<Data, Data> calculations::partition(const Data &data, const Question &q) {
    Data true_rows;
    Data false_rows;
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
        impurity -= std::pow(prob_of_lbl, 2.0f);
    }

    return impurity;
}

float calculations::info_gain(const Data &left, const Data &right, float current_uncertainty) {
    const float p = static_cast<float>(left.size()) / (left.size() + right.size());
    return current_uncertainty - p * gini(left) - (1 - p) * gini(right);
}

tuple<double, Question> calculations::find_best_split(const Data &rows) {
    float best_gain = 0.0;  // keep track of the best information gain
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

VecS calculations::unique_values(const Data &data, size_t column) {
    VecS unique_vals;

    ClassCounter counter;
    for (const auto &rows: data) {
        const string &decision = rows[column];
        counter[decision] += 0;
    }

    unique_vals.reserve(counter.size());

    std::transform(begin(counter), std::end(counter), std::back_inserter(unique_vals),
                   [](const auto &kv) { return kv.first; });
    return unique_vals;
}

ClassCounter calculations::class_counts(const Data &data) {
    ClassCounter counter;
    counter.reserve(data.size()/3);
    for (const auto &rows: data) {
        const string decision = rows.back();
        counter[decision] += 1;
    }
    return counter;
}
