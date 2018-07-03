//
// Created by Julian on 26.06.18.
//

#include "../include/Tests.hpp"
#include <cassert>
#include <algorithm>
#include <iterator>

Tests::Tests() {
  Dataset d;
  d.train.filename = "../data/fruit.csv";
  d.test.filename = "../data/fruit_test.csv";

  DecisionTree dt(d);
  testTree(dt.testingData(), dt.root_());
  testGenerator(dt);
}

void Tests::testTree(const Data& testing_data, shared_ptr<Node> tree) const {
  TreeTest tree_test;
  {
    string predict = "Apple";
    ClassCounter prediction;
    prediction["Apple"] = 8;

    const auto& test_row = testing_data.at(0);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Apple";
    ClassCounter prediction;
    prediction["Apple"] = 2;

    const auto& test_row = testing_data.at(1);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);

  }

  {
    string predict = "Grape";
    ClassCounter prediction;
    prediction["Grape"] = 14;

    const auto& test_row = testing_data.at(2);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Grape";
    ClassCounter prediction;
    prediction["Grape"] = 14;

    const auto& test_row = testing_data.at(3);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Lemon";
    ClassCounter prediction;
    prediction["Apple"] = 1;
    prediction["Lemon"] = 4;

    const auto& test_row = testing_data.at(4);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Lime";
    ClassCounter prediction;
    prediction["Lime"] = 4;

    const auto& test_row = testing_data.at(5);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Pepper";
    ClassCounter prediction;
    prediction["Pepper"] = 11;

    const auto& test_row = testing_data.at(6);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Pepper";
    ClassCounter prediction;
    prediction["Pepper"] = 11;

    const auto& test_row = testing_data.at(7);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Pepper";
    ClassCounter prediction;
    prediction["Pepper"] = 11;

    const auto& test_row = testing_data.at(8);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Radish";
    ClassCounter prediction;
    prediction["Radish"] = 5;

    const auto& test_row = testing_data.at(9);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Grape";
    ClassCounter prediction;
    prediction["Grape"] = 14;

    const auto& test_row = testing_data.at(10);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Pepper";
    ClassCounter prediction;
    prediction["Pepper"] = 11;

    const auto& test_row = testing_data.at(11);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Grape";
    ClassCounter prediction;
    prediction["Grape"] = 14;

    const auto& test_row = testing_data.at(12);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Apple";
    ClassCounter prediction;
    prediction["Pepper"] = 11;

    const auto& test_row = testing_data.at(13);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

  {
    string predict = "Eggplant";
    ClassCounter prediction;
    prediction["Eggplant"] = 6;

    const auto& test_row = testing_data.at(14);
    const auto& result = tree_test.testRow(test_row, tree);

    assert(prediction == result);
  }

}

void Tests::testGenerator(DecisionTree& dtree, const string filename) const {
  if (fileExists(filename))
    std::remove(filename.c_str());

  dtree.generateGraph(filename);

  assert(fileExists(filename));
  assert(lineNumsMatch(filename));
}

bool Tests::fileExists(const string &filename) const {
  ifstream infile(filename);
  bool fileExists = infile.good();
  infile.close();
  return fileExists;
}

bool Tests::lineNumsMatch(const string& filename) const {
  constexpr long wanted_line_count = 67;
  ifstream infile(filename);
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
