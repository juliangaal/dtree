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

#include <dtree/decision_tree.h>
#include <fmt/format.h>
#include <filesystem>
#include <tuple>

namespace fs = std::filesystem;
using namespace dtree;
using std::string;

DecisionTree::DecisionTree(const TrainingSet &trainset, const TestingSet &testset)
        : dr{trainset, testset},  size_{}, root_{build_rec(dr.training_data())} {
    fmt::print("> Generated decision tree with {} from {} training data points\n", size_, dr.training_data().size());
}

std::unique_ptr<Node> DecisionTree::build_rec(const Data &rows) {
    ++size_;

    auto[gain, question] = calculations::find_best_split(rows);
    if (gain == 0.0) {
        return std::make_unique<Node>(rows);
    }

    const auto[true_rows, false_rows] = calculations::partition(rows, question);
    auto true_branch = build_rec(true_rows);
    auto false_branch = build_rec(false_rows);

    return std::make_unique<Node>(std::move(true_branch), std::move(false_branch), question);
}

void DecisionTree::print_tree() const {
    std::string spacing{};
    rec_print_node(root_, spacing);
}

void DecisionTree::rec_print_node(const std::unique_ptr<Node> &root, string &spacing) const {
    if (root->predicts()) {
        fmt::print("{}{}", spacing, "Predict:");
        help::print::print_map(root->predictions().value());
        return;
    }

    spacing += "   ";

    fmt::print("{}{}\n", spacing, root->question().value().toString(dr.labels()));

    fmt::print("{}--> True:\n", spacing);
    rec_print_node(root->true_branch(), spacing);

    fmt::print("{}--> False:\n", spacing);
    rec_print_node(root->false_branch(), spacing);
}

void DecisionTree::generate_graph(const string &file) const {
    generate::init(root_, dr.labels(), file);
    fmt::print("> Generated Graphviz file {}\n", file);
}

void DecisionTree::test() const {
    validation::validate(dr.testing_data(), dr.labels(), root_);
}
