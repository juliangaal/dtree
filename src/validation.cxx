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

#include <dtree/validation.h>
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <fmt/format.h>

using namespace dtree;

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
        scale[key] = val / total * 100.0F;
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
