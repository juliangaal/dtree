//
// Created by Julian on 25.06.18.
//

#include <decision_tree/validation.hpp>
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
        return validation::classify(row, node->trueBranch());
    else
        return validation::classify(row, node->falseBranch());
}

void validation::print_prediction(const ClassCounter &counts) {
    const float total = static_cast<float>(helpers::tree::mapValueSum(
            counts)); //[](const size_t previous, const auto& p) { return previous+p.second; });
    ClassCounterScaled scale;

    for (const auto&[key, val]: counts) {
        scale[key] = val / total * 100.0f;
    }
    helpers::print::print_map(scale);
}


void validation::validate(const Data &testing_data, const VecS &labels, const std::unique_ptr<Node> &tree) {
    for (const auto &row: testing_data) {
        fmt::print("> {:<10} -> {:^10}", "label " + row.back(), "prediction: ");
        print_prediction(validation::classify(row, tree));
    }
}

ClassCounter validation::testRow(const VecS &row, const std::unique_ptr<Node> &node) {
    return validation::classify(row, node);
}
