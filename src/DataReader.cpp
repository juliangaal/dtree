//
// Created by Julian on 13.06.18.
//
#include <thread>
#include "DataReader.hpp"

DataReader::DataReader(const Dataset& dataset, string delim) : delimeter(move(delim)), labels({}) {
  std::thread readTestingData([this,&dataset]() { return processFile(dataset.train.filename, training_data); });
  std::thread readTrainingData([this,&dataset]() { return processFile(dataset.test.filename, testing_data); });
  readTrainingData.join();
  readTestingData.join();

  if (training_data.empty())
    throw std::runtime_error("Can't open file: " + dataset.train.filename);

  if (testing_data.empty())
    throw std::runtime_error("Can't open file: " + dataset.test.filename);

  if (labels.empty())
    throw std::runtime_error("Labels include empty strings");
}

void DataReader::processFile(const string& filename, Data& data) {
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
      if (hasEmptyStrings(vec))
        return;

      labels = move(vec);
    } else {
      data.emplace_back(move(vec));
    }

    ++line_counter;
  }
  file.close();
}

bool DataReader::hasEmptyStrings(const vector<string> &strings) const {
  return std::any_of(strings.begin(), strings.end(), [](const auto& v) { return v.empty(); } );
}

bool DataReader::isCommentLine(const string &line) const {
  if (auto n = line.find("#"); n != std::string::npos)
    return true;

  return false;
}
