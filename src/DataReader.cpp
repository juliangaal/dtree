//
// Created by Julian on 13.06.18.
//
#include <thread>
#include <ogr_feature.h>
#include "DataReader.hpp"

DataReader::DataReader(const Dataset& dataset, string delim) :
    result_label(dataset.result_label),
    delimeter(move(delim)),
    training_labels({}),
    testing_labels({}),
    missing_labels(false) {

  std::thread readTestingData([this,&dataset]() {
    return processFile(dataset.train.filename, training_data, training_labels);
  });

  std::thread readTrainingData([this,&dataset]() {
    return processFile(dataset.test.filename, testing_data, testing_labels);
  });

  readTrainingData.join();
  readTestingData.join();

  if (!result_label.empty())
    correctLabels();

  if (missing_labels)
    throw std::runtime_error("Check your labels: Are some missing? Training labels == testing labels?");

  if (training_data.empty())
    throw std::runtime_error("Can't open file: " + dataset.train.filename);

  if (testing_data.empty())
    throw std::runtime_error("Can't open file: " + dataset.test.filename);

}

void DataReader::processFile(const string& filename, Data& data, VecS &labels) {
  ifstream file(filename);
  if (!file)
    return;
//  Data data;
  string line;
  int line_counter = 1;
  static constexpr int first_line = 1;

  while (getline(file, line)) {
    vector<string> vec;

    if (isCommentLine(line))
      continue;

    split(vec, line, boost::is_any_of(delimeter));

    if (line_counter == first_line) {
      if (hasEmptyStrings(vec)) {
        missing_labels = true;
        return;
      }

      labels = move(vec);
    } else {
      if (hasEmptyStrings(vec))
        correctMissingValues(data, vec);

      if (result_label.empty()) {
        data.emplace_back(move(vec));
      } else {
        swapResultData(vec, labels);
        data.emplace_back(move(vec));
      }
    }

    ++line_counter;
  }

  file.close();
}

bool DataReader::hasEmptyStrings(const vector<string> &strings) const {
  return std::any_of(begin(strings), end(strings), [](const auto& v) { return v.empty(); } );
}

bool DataReader::isCommentLine(const string &line) const {
  if (auto n = line.find("#"); n != std::string::npos)
    return true;

  return false;
}

void DataReader::swapResultData(VecS &line, const VecS &labels) {
  static const auto result = std::find(begin(labels), end(labels), result_label);
  if (result != end(labels)) {
    static const auto result_index = std::distance(begin(labels), result);
    std::iter_swap(begin(line)+result_index, end(line)-1);
  }
}

void DataReader::correctLabels() {
  if (training_labels != testing_labels) {
    missing_labels = true;
    return;
  }

  const auto result = std::find(begin(training_labels), end(training_labels), result_label);
  if (result != end(training_labels))
    std::iter_swap(result, end(training_labels)-1);
}

void DataReader::correctMissingValues(const Data& data, VecS &vec) {
  const auto& last_line = *(end(data)-1);
  vec.clear();
  // TODO: replace with stl::copy_if version
  std::copy(begin(last_line), end(last_line), std::back_inserter(vec));
}
