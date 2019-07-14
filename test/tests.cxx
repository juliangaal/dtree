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
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <dtree/decision_tree.h>
#include <dtree/calculations.h>
#include <dtree/help.h>
#include <dtree/node.h>
#include <tuple>
#include <filesystem>
#include <fstream>
#include <fmt/format.h>

using namespace dtree;
namespace fs = std::filesystem;

TEST_CASE("Integration Tests") {
    DecisionTree dt(TrainingSet("../test/data/fruit.csv", SkipDescription::NO),
                    TestingSet("../test/data/fruit_test.csv"), ASYNC);
    const auto& tree = dt.root();
    const auto& testing_data = dt.testing_data();

    SECTION("Test Tree predictions") {
        {
            ClassCounter prediction;
            prediction.insert({"Apple", 8});
            const auto &test_row = testing_data.at(0);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Apple", 2});
            const auto &test_row = testing_data.at(1);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Grape", 14});
            const auto &test_row = testing_data.at(2);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Grape", 14});
            const auto &test_row = testing_data.at(3);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Apple", 1});
            prediction.insert({"Lemon", 4});
            const auto &test_row = testing_data.at(4);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Lime", 4});
            const auto &test_row = testing_data.at(5);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Pepper", 11});
            const auto &test_row = testing_data.at(6);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Pepper", 11});
            const auto &test_row = testing_data.at(7);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Pepper", 11});
            const auto &test_row = testing_data.at(8);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Radish", 5});
            const auto &test_row = testing_data.at(9);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Grape", 14});
            const auto &test_row = testing_data.at(10);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Pepper", 11});
            const auto &test_row = testing_data.at(11);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Grape", 14});
            const auto &test_row = testing_data.at(12);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Pepper", 11});
            const auto &test_row = testing_data.at(13);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }

        {
            ClassCounter prediction;
            prediction.insert({"Eggplant", 6});
            const auto &test_row = testing_data.at(14);
            const auto &result = validation::testRow(test_row, tree);
            REQUIRE(prediction == result);
        }
    }

    SECTION("Test generator") {
        constexpr long wanted_line_count = 67;
        const fs::path file = "../graph.dot";

        if (fs::exists(file))
            std::remove(file.c_str());

        dt.generate_graph(file);

        REQUIRE(fs::exists(file));
        REQUIRE(fs::is_regular_file(file));

        // taken from https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
        // new lines will be skipped unless we stop it from happening:
        std::ifstream infile(file);
        infile.unsetf(std::ios_base::skipws);

        unsigned long line_count = std::count(
                std::istreambuf_iterator<char>(infile),
                std::istreambuf_iterator<char>(),
                '\n');
        // ++ because last line in file doesn't break with '\n'
        REQUIRE(++line_count == wanted_line_count);
        infile.close();
    }
}

TEST_CASE("Test calculations::class_counts") {
    Data data{
            {"foo", "bar", "class1"},
            {"bar", "foo", "class1"},
            {"foo", "bar", "class2"},
            {"bar", "foo", "class2"},
            {"foo", "bar", "class3"},
            {"bar", "foo", "class3"},
    };

    auto counts = calculations::class_counts(data);
    REQUIRE(counts.at("class1") == 2);
    REQUIRE(counts.at("class2") == 2);
    REQUIRE(counts.at("class3") == 2);
}

TEST_CASE("Test calculations::unique_values") {
    Data data{
            {"foo", "bar", "class1"},
            {"bar", "foo", "class1"},
            {"foobar", "bar", "class2"},
            {"bar", "foo", "class2"},
            {"foo", "bar", "class3"},
            {"barfoo", "foo", "class3"},
    };

    auto uniq_vals = calculations::unique_values(data, 0);
    // this is an unordered_map, can't just compare because order isn't guaranteed
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "foo") != uniq_vals.end());
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "bar") != uniq_vals.end());
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "foobar") != uniq_vals.end());
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "barfoo") != uniq_vals.end());
    REQUIRE(uniq_vals.size() == 4);

    uniq_vals = calculations::unique_values(data, 1);
    // this is an unordered_map, can't just compare because order isn't guaranteed
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "foo") != uniq_vals.end());
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "bar") != uniq_vals.end());
    REQUIRE(uniq_vals.size() == 2);

    uniq_vals = calculations::unique_values(data, 2);
    // this is an unordered_map, can't just compare because order isn't guaranteed
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "class1") != uniq_vals.end());
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "class2") != uniq_vals.end());
    REQUIRE(std::find(uniq_vals.begin(), uniq_vals.end(), "class3") != uniq_vals.end());
    REQUIRE(uniq_vals.size() == 3);
}

TEST_CASE("Test calculations::gini") {
    {
        Data data{
                {"foo",    "bar", "class1"},
                {"bar",    "foo", "class1"},
                {"foobar", "bar", "class2"},
                {"bar",    "foo", "class2"},
                {"foo",    "bar", "class3"},
                {"barfoo", "foo", "class3"},
        };
        REQUIRE(calculations::gini(data) == Approx(0.66667f));
    }

    {
        Data data{{"foo",    "bar", "class1"}};
        REQUIRE(calculations::gini(data) == Approx(0.0f));
    }

    {
        Data data{
                {"foo",    "bar", "class1"},
                {"bar",    "foo", "class1"},
                {"foobar", "bar", "class1"},
                {"bar",    "foo", "class3"},
                {"foo",    "bar", "class3"},
                {"barfoo", "foo", "class3"},
        };
        REQUIRE(calculations::gini(data) == Approx(0.5f));
    }

    {
        Data data{
                {"foo",    "bar", "class1"},
                {"bar",    "foo", "class1"},
                {"foobar", "bar", "class3"},
                {"bar",    "foo", "class3"},
                {"foo",    "bar", "class3"},
                {"barfoo", "foo", "class3"},
        };
        REQUIRE(calculations::gini(data) == Approx(0.44444f));
    }
}

TEST_CASE("Test calculations::partition") {
    {
        Data data{
                {"0.9", "class1"},
                {"0.8", "class1"},
                {"0.7", "class2"},
                {"0.6", "class2"},
                {"0.5", "class3"},
                {"0.4", "class3"},
        };

        {
            auto[calc_matches, calc_non_matches] = calculations::partition(data, Question(0, "0.7"));
            Data true_matches{
                    {"0.9", "class1"},
                    {"0.8", "class1"},
                    {"0.7", "class2"},
            };
            Data false_matches{
                    {"0.6", "class2"},
                    {"0.5", "class3"},
                    {"0.4", "class3"},
            };

            REQUIRE(calc_matches == true_matches);
            REQUIRE(calc_non_matches == false_matches);
        }

        {
            auto[calc_matches, calc_non_matches] = calculations::partition(data, Question(1, "0.7"));

            REQUIRE(calc_matches == Data{});
            REQUIRE(calc_non_matches == data);
        }

        {
            auto[calc_matches, calc_non_matches] = calculations::partition(data, Question(1, "class1"));
            Data true_matches{
                    {"0.9", "class1"},
                    {"0.8", "class1"},
            };
            Data false_matches{
                    {"0.7", "class2"},
                    {"0.6", "class2"},
                    {"0.5", "class3"},
                    {"0.4", "class3"},
            };

            REQUIRE(calc_matches == true_matches);
            REQUIRE(calc_non_matches == false_matches);
        }
    }
}
