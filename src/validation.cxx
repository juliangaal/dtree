//
// Created by Julian on 25.06.18.
//

#include <decision_tree/validation.h>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <fmt/format.h>

using namespace decision_tree;

ClassCounter validation::classify(const VecS &row, const std::unique_ptr<Node> &node) {
    if (node->predicts()) {
        return node->predictions().value();
    }

    if (node->question().value().match(row))
        return validation::classify(row, node->true_branch());
    else
        return validation::classify(row, node->false_branch());
}

void validation::print_prediction(const ClassCounter &counts) {
    const float total = std::accumulate(counts.begin(), counts.end(), 0, [](auto curr, const auto& entry) { return curr + entry.second; });
    ClassCounterScaled scale;

    for (const auto&[key, val]: counts) {
        scale[key] = val / total * 100.0f;
    }
    help::print::print_map(scale);
}


void validation::validate(const Data &testing_data, const VecS &labels, const std::unique_ptr<Node> &tree) {
    fmt::print("> Test set validation results\n");
    for (const auto &row: testing_data) {
        fmt::print("  - label {:<3} -> {:^10}", row.back(), "prediction: ");
        print_prediction(validation::classify(row, tree));
    }
}

ClassCounter validation::testRow(const VecS &row, const std::unique_ptr<Node> &node) {
    return validation::classify(row, node);
}
