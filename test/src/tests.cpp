//
// Created by Julian on 26.06.18.
//

#include <decision_tree/validation.hpp>
#include <decision_tree/decision_tree.hpp>
#include <decision_tree/node.hpp>
#include <cassert>
#include <tuple>
#include <fstream>
#include <memory>

using namespace decision_tree;

bool fileExists(const std::string &filename) {
    std::ifstream infile(filename);
    bool fileExists = infile.good();
    infile.close();
    return fileExists;
}

bool lineNumsMatch(const std::string &filename) {
    constexpr long wanted_line_count = 67;
    std::ifstream infile(filename);
    if (!infile.good()) {
        std::cout << "File " << filename << " doesn't exist\n";
        return false;
    }

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
    if (fileExists(filename))
        std::remove(filename.c_str());

    dtree.generateGraph(filename);

    assert(fileExists(filename));
    assert(lineNumsMatch(filename));
}

int main(void) {
    DecisionTree dt(TrainingSet("../test/data/fruit.csv", SkipDescription::NO), TestingSet("../test/data/fruit_test.csv"));
    testTree(dt.testingData(), dt.root());
    testGenerator(dt, "../graph.dot");

    std::cout << "Tests successful." << std::endl;
    return EXIT_SUCCESS;
}