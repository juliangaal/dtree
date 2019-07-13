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
#include <dtree/node.h>
#include <cassert>
#include <tuple>
#include <filesystem>
#include <fstream>
#include <memory>
#include <fmt/format.h>

using namespace dtree;
namespace fs = std::filesystem;

bool lineNumsMatch(const fs::path &file) {
    constexpr long wanted_line_count = 67;

    if (!fs::is_regular_file(file)) {
        fmt::print("File {} doesn't exist\n", file.string());
        return false;
    }

    std::ifstream infile(file);

    // taken from https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
    // new lines will be skipped unless we stop it from happening:
    infile.unsetf(std::ios_base::skipws);

    unsigned long line_count = std::count(
            std::istreambuf_iterator<char>(infile),
            std::istreambuf_iterator<char>(),
            '\n');

    infile.close();
    // ++ because last line in file doesn't break with '\n'
    return ++line_count == wanted_line_count;
}

void testTree(const Data &testing_data, const std::unique_ptr<Node> &tree) {
    {
        ClassCounter prediction;
        prediction.insert({"Apple", 8});
        const auto &test_row = testing_data.at(0);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Apple", 2});
        const auto &test_row = testing_data.at(1);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Grape", 14});
        const auto &test_row = testing_data.at(2);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Grape", 14});
        const auto &test_row = testing_data.at(3);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Apple", 1});
        prediction.insert({"Lemon", 4});
        const auto &test_row = testing_data.at(4);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Lime", 4});
        const auto &test_row = testing_data.at(5);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Pepper", 11});
        const auto &test_row = testing_data.at(6);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Pepper", 11});
        const auto &test_row = testing_data.at(7);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Pepper", 11});
        const auto &test_row = testing_data.at(8);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Radish", 5});
        const auto &test_row = testing_data.at(9);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Grape", 14});
        const auto &test_row = testing_data.at(10);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Pepper", 11});
        const auto &test_row = testing_data.at(11);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Grape", 14});
        const auto &test_row = testing_data.at(12);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Pepper", 11});
        const auto &test_row = testing_data.at(13);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }

    {
        ClassCounter prediction;
        prediction.insert({"Eggplant", 6});
        const auto &test_row = testing_data.at(14);
        const auto &result = validation::testRow(test_row, tree);
        assert(prediction == result);
    }
}

void testGenerator(DecisionTree &dtree, const std::string filename) {
    if (fs::exists(filename))
        std::remove(filename.c_str());

    dtree.generate_graph(filename);

    assert(fs::exists(filename));
    assert(lineNumsMatch(filename));
}

int main() {
    DecisionTree dt(TrainingSet("../test/data/fruit.csv", SkipDescription::NO), TestingSet("../test/data/fruit_test.csv"));
    testTree(dt.testing_data(), dt.root());
    testGenerator(dt, "../graph.dot");

    fmt::print("> Tests successful.\n");
    return EXIT_SUCCESS;
}