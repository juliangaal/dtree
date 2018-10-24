//
// Created by Julian on 26.06.18.
//

#include "../include/Tests.hpp"
#include <cassert>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <fstream>
#include <memory>

Tests::Tests() {
  Dataset d;
  d.train.filename = "../data/fruit.csv";
  d.test.filename = "../data/fruit_test.csv";

  DecisionTree dt(d);
  testTree(dt.testingData(), dt.root());
  testGenerator(dt);
}

void Tests::testTree(const Data& testing_data, std::shared_ptr<Node> tree) const {
  TreeTest tree_test;
  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Apple", 8));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(0);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Apple", 2));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(1);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);

  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Grape", 14));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(2);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Grape", 14));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(3);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    {
      auto[_, success] = prediction.insert(std::pair<std::string, int>("Apple", 1));
      if (!success)
        std::cerr << "Can't build test example";
    }
    {
      auto[_, success] = prediction.insert(std::pair<std::string, int>("Lemon", 4));
      if (!success)
        std::cerr << "Can't build test example";
    }
    const auto& test_row = testing_data.at(4);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Lime", 4));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(5);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Pepper", 11));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(6);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Pepper", 11));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(7);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Pepper", 11));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(8);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Radish", 5));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(9);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Grape", 14));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(10);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Pepper", 11));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(11);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Grape", 14));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(12);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Pepper", 11));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(13);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    ClassCounter prediction;
    auto [_, success] = prediction.insert(std::pair<std::string, int>("Eggplant", 6));
    if (!success)
      std::cerr << "Can't build test example";

    const auto& test_row = testing_data.at(14);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

}

void Tests::testGenerator(DecisionTree& dtree, const std::string filename) const {
  if (fileExists(filename))
    std::remove(filename.c_str());

  dtree.generateGraph(filename);

  assert(fileExists(filename));
  assert(lineNumsMatch(filename));
}

bool Tests::fileExists(const std::string &filename) const {
  std::ifstream infile(filename);
  bool fileExists = infile.good();
  infile.close();
  return fileExists;
}

bool Tests::lineNumsMatch(const std::string& filename) const {
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
