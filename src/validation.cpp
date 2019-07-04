//
// Created by Julian on 25.06.18.
//

#include <decision_tree/validation.hpp>

using namespace decision_tree;
using std::make_shared;
using std::shared_ptr;

ClassCounter validation::classify(const VecS &row, shared_ptr<Node> node) {
    if (node->predicts()) {
        return node->predictions().value();
    }

    if (node->question().value().match(row))
        return validation::classify(row, node->trueBranch());
    else
        return validation::classify(row, node->falseBranch());
}

void validation::print_prediction(ClassCounter counts) {
    const float total = static_cast<float>(helpers::tree::mapValueSum(
            counts)); //[](const size_t previous, const auto& p) { return previous+p.second; });
    ClassCounterScaled scale;

    for (const auto&[key, val]: counts) {
        scale[key] = std::to_string(val / total * 100) + "%";
    }
    helpers::print::print_map(scale);
}


void validation::validate(const Data &testing_data, const VecS &labels, shared_ptr<Node> tree) {
    for (const auto &row: testing_data) {
        static size_t last = row.size() - 1;
        std::cout << "Actual: " << labels[last] << " - " << row[last] << "\tPrediction: ";
        print_prediction(validation::classify(row, tree));
    }
}

ClassCounter validation::testRow(const VecS &row, std::shared_ptr<Node> node) {
    return validation::classify(row, node);
}
