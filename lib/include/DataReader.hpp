//
// Created by Julian on 13.06.18.
//

#ifndef TREE_CSVREADER_HPP
#define TREE_CSVREADER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "Dataset.hpp"
#include "Helper.hpp"

using Data = std::vector<std::vector<std::string>>;
using VecS = std::vector<std::string>;
/*
 * A class to read data from a csv file. Based on http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
 */

class DataReader
{
 private:
  bool hasEmptyStrings(const VecS& strings) const;
  bool isCommentLine(const std::string& line) const;

  const std::string result_label;
  const std::string delimeter;
  Data training_data;
  Data testing_data;
  VecS training_labels;
  VecS testing_labels;
  bool missing_labels;

 public:
  DataReader() = delete;
  DataReader(const Dataset& dataset, std::string delm = ",");

  inline const Data& trainingData() const { return training_data; }
  inline const Data& testingData() const { return testing_data; }
  inline const VecS& labels() const { return training_labels; }
  /**
   * Parses through csv file line by line and
   * @return the data in vector of vector of strings
   */
  void processFile(const std::string& strings, Data& data, VecS &labels);
  void swapResultData(VecS &line, const VecS &labels) const;
  void correctLabels();
  void trimWhiteSpaces(VecS &line);
  void correctMissingValues(const Data &data, VecS &vec) const;
};

#endif //TREE_CSVREADER_HPP
